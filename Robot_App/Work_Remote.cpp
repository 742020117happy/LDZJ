#pragma execution_character_set("utf-8")
#include "Work_Remote.h"
#include "MySql_Remote.h"

// ====================================================================
//  c_Work_Remote — 轮对质检工作流业务逻辑
//  通过 QEventLoop 事件等待实现非阻塞步进控制
//  运行在独立 QThread 中，通过信号槽与各远程模块通信
// ====================================================================

c_Work_Remote::c_Work_Remote(QObject *parent) : c_Object(parent)
{
}

c_Work_Remote::~c_Work_Remote()
{
    m_Running = false;
}

void c_Work_Remote::Init()
{
    auto &cfg = c_Variable::getInstance().g_Communicate_DB;
    m_CurrentIP = cfg.value("Camera_IP").toString("192.168.6.35");
    m_CurrentPort = cfg.value("Camera_Port").toInt(8001);
    emit Work_Log("Work_Remote 初始化完成");
}

// ====================================================================
//  流程控制入口
// ====================================================================
void c_Work_Remote::Start_Inspection()
{
    if (m_Running) {
        emit Work_Log("工作流已在运行中，忽略重复开始");
        return;
    }
    m_Running = true;
    m_Paused = false;
    m_CancelRequested = false;

    auto &work = c_Variable::getInstance().g_Work_DB;
    m_CurrentTaskId = work.taskId;
    work.workState = 1;
    work.currentWheelset = 0;
    work.currentPos = 0;
    emit Work_State_Changed(1, "就绪");
    emit Work_Log("任务开始: " + m_CurrentTaskId);

    QTimer::singleShot(0, this, &c_Work_Remote::Run_Inspection);
}

void c_Work_Remote::Pause_Inspection()
{
    m_Paused = true;
    c_Variable::getInstance().g_Work_DB.workState = 3;
    emit Work_State_Changed(3, "暂停");
    emit Work_Log("工作流已暂停");
}

void c_Work_Remote::Resume_Inspection()
{
    m_Paused = false;
    c_Variable::getInstance().g_Work_DB.workState = 2;
    emit Work_State_Changed(2, "采集中");
    emit Work_Log("工作流已恢复");
}

void c_Work_Remote::Cancel_Inspection()
{
    m_CancelRequested = true;
    m_Running = false;
    m_Paused = false;
    c_Variable::getInstance().g_Work_DB.workState = 4;
    emit Signal_CGXi_Stop();
    emit Work_State_Changed(4, "已取消");
    emit Work_Log("工作流已取消");
}

void c_Work_Remote::Emergency_Stop()
{
    m_Running = false;
    m_Paused = false;
    m_CancelRequested = true;
    c_Variable::getInstance().g_Work_DB.workState = 5;
    emit Signal_CGXi_Stop();
    emit Work_State_Changed(5, "急停");
    emit Work_Log("紧急停止");
}

void c_Work_Remote::Return_Home()
{
    Do_NavigateToCharge();
}

// ====================================================================
//  主工作流 — QEventLoop 步进控制
// ====================================================================
void c_Work_Remote::Run_Inspection()
{
    auto &work = c_Variable::getInstance().g_Work_DB;

    // 1. 应答 ACCEPTED
    Do_SendServerAccepted();

    // 2. 加载配置文件查找 axleType + repairLevel 对应的工位计划
    QJsonObject plan;
    {
        QFile file(QDir::currentPath() + "/Work_DB/InspectionPlan.json");
        if (file.open(QIODevice::ReadOnly)) {
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
            if (doc.isObject()) plan = doc.object();
            file.close();
        }
    }

    QString axleType = work.axleType;
    QString repairLevel = work.repairLevel;
    QJsonArray positions;

    if (!plan.isEmpty() && plan.contains(axleType)) {
        QJsonObject typeObj = plan[axleType].toObject();
        if (typeObj.contains(repairLevel)) {
            QJsonObject levelObj = typeObj[repairLevel].toObject();
            positions = levelObj["positions"].toArray();
            emit Work_Log("加载工位计划: " + axleType + "/" + repairLevel);
        }
    }

    // 如果配置文件没有，使用 wheelsetPositions 从 WEB 指令
    if (positions.isEmpty()) {
        positions = work.wheelsetPositions;
        emit Work_Log("使用 WEB 下发的工位列表");
    }

    if (positions.isEmpty()) {
        emit Step_Failed("无工位配置");
        return;
    }

    // 3. 轮对循环
    for (int wi = 0; wi < work.wheelsetCount && m_Running && !m_CancelRequested; wi++) {
        work.currentWheelset = wi;
        emit Work_State_Changed(2, "轮对 " + QString::number(wi + 1) + "/" + QString::number(work.wheelsetCount));

        // 3a. 导航到轮对位置
        QString wsPointName;
        if (wi < work.wheelsetPositions.size()) {
            wsPointName = work.wheelsetPositions[wi].toObject()["mapPointName"].toString();
        }
        if (!wsPointName.isEmpty()) {
            Do_NavigateToPosition(wsPointName);
            if (m_CancelRequested) break;
        }

        // 4. 工位循环
        for (int pi = 0; pi < positions.size() && m_Running && !m_CancelRequested; pi++) {
            work.currentPos = pi;
            emit Work_Log("工位 " + QString::number(pi + 1) + "/" + QString::number(positions.size()));

            QJsonObject posObj = positions[pi].toObject();

            // 4a. 导航到工位
            QString posPointName = posObj["point"].toString();
            if (!posPointName.isEmpty()) {
                Do_NavigateToPosition(posPointName);
                if (m_CancelRequested) break;
            }

            // 4b. 设置 CGXi 程序索引
            int progIndex = posObj["prog"].toInt();
            Do_SetCGXiProgram(progIndex);
            if (m_CancelRequested) break;

            // 4c. 启动 CGXi
            Do_StartCGXi();
            if (m_CancelRequested) break;

            // 4d. 等待 CGXi 发送 START&! （由 Lczh_Remote 处理）
            //     等待 workState 变为 2（采集中）或回到 0（空闲/完成）
            {
                QEventLoop loop;
                QTimer pollTimer;
                pollTimer.setInterval(100);
                int timeoutCount = 0;
                connect(&pollTimer, &QTimer::timeout, [&]() {
                    if (m_CancelRequested || !m_Running) { loop.quit(); return; }
                    int st = c_Variable::getInstance().g_Work_DB.workState;
                    if (st == 2 || st == 4 || st == 0) { loop.quit(); return; }
                    timeoutCount++;
                    if (timeoutCount > 3000) { loop.quit(); emit Step_Failed("等待 CGXi START 超时"); }
                });
                pollTimer.start();
                loop.exec();
                pollTimer.stop();
            }
            if (m_CancelRequested) break;

            // 4e. 发送相机 START (由 Lczh_Remote 处理，等待 workState 回到非采集中)
            {
                QEventLoop loop;
                QTimer pollTimer;
                pollTimer.setInterval(100);
                connect(&pollTimer, &QTimer::timeout, [&]() {
                    if (m_CancelRequested || !m_Running) { loop.quit(); return; }
                    int st = c_Variable::getInstance().g_Work_DB.workState;
                    if (st == 4 || st == 0) { loop.quit(); return; }
                });
                pollTimer.start();
                loop.exec();
                pollTimer.stop();
            }

            // 4f. 暂停检测
            if (m_Paused) {
                QEventLoop pauseLoop;
                QTimer pauseTimer;
                pauseTimer.setInterval(200);
                connect(&pauseTimer, &QTimer::timeout, [&]() {
                    if (!m_Paused || m_CancelRequested) pauseLoop.quit();
                });
                pauseTimer.start();
                pauseLoop.exec();
                pauseTimer.stop();
            }
        }

        if (m_CancelRequested) break;
    }

    // 5. 全部完成
    if (!m_CancelRequested && m_Running) {
        Do_NavigateToCharge();
        Do_SendServerCompleted(c_Variable::getInstance().g_Work_DB.totalImages);
        work.workState = 4;
        emit Work_State_Changed(4, "完成");
        emit Work_Log("任务全部完成");
    }

    m_Running = false;
}

// ====================================================================
//  步骤函数 — 每个步骤使用 QEventLoop 等待完成
// ====================================================================
void c_Work_Remote::Do_NavigateToPosition(QString pointName)
{
    if (pointName.isEmpty()) return;
    emit Work_Log("导航到: " + pointName);
    emit Signal_Magic_Navigate(pointName);

    QEventLoop loop;
    QTimer pollTimer;
    pollTimer.setInterval(200);
    int timeout = 0;
    connect(&pollTimer, &QTimer::timeout, [&]() {
        if (m_CancelRequested || !m_Running) { loop.quit(); return; }
        int st = c_Variable::getInstance().g_Magic.ReadData.taskStatus;
        if (st == 0) { loop.quit(); return; }
        timeout++;
        if (timeout > 1500) { loop.quit(); emit Step_Failed("导航超时: " + pointName); }
    });
    pollTimer.start();
    loop.exec();
    pollTimer.stop();
}

void c_Work_Remote::Do_NavigateToCharge()
{
    emit Work_Log("返回充电位");
    emit Signal_Magic_Charge();

    QEventLoop loop;
    QTimer pollTimer;
    pollTimer.setInterval(200);
    int timeout = 0;
    connect(&pollTimer, &QTimer::timeout, [&]() {
        if (m_CancelRequested) { loop.quit(); return; }
        int st = c_Variable::getInstance().g_Magic.ReadData.taskStatus;
        if (st == 0) { loop.quit(); return; }
        timeout++;
        if (timeout > 1500) { loop.quit(); emit Work_Log("返回充电位超时"); }
    });
    pollTimer.start();
    loop.exec();
    pollTimer.stop();
}

void c_Work_Remote::Do_SetCGXiProgram(int index)
{
    emit Work_Log("设置 CGXi 程序: " + QString::number(index));
    emit Signal_CGXi_SetProgram(index);

    QEventLoop loop;
    QTimer::singleShot(200, &loop, &QEventLoop::quit);
    loop.exec();
}

void c_Work_Remote::Do_StartCGXi()
{
    emit Work_Log("启动 CGXi 程序");
    emit Signal_CGXi_Start();

    QEventLoop loop;
    QTimer::singleShot(200, &loop, &QEventLoop::quit);
    loop.exec();
}

void c_Work_Remote::Do_SendServerAccepted()
{
    emit Work_Log("发送 ACCEPTED");
    emit Signal_Server_Accepted();

    QEventLoop loop;
    QTimer::singleShot(100, &loop, &QEventLoop::quit);
    loop.exec();
}

void c_Work_Remote::Do_SendServerCompleted(int totalImages)
{
    emit Work_Log("发送 COMPLETED, 图像数: " + QString::number(totalImages));
    emit Signal_Server_Completed(totalImages);

    QEventLoop loop;
    QTimer::singleShot(100, &loop, &QEventLoop::quit);
    loop.exec();
}


