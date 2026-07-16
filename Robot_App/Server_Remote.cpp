#pragma execution_character_set("utf-8")
#include "Server_Remote.h"

/*************************************************************************************************************************************************
**Function:构造函数
*************************************************************************************************************************************************/
c_Server_Remote::c_Server_Remote(QObject *parent) : c_Object(parent)
{
}

c_Server_Remote::~c_Server_Remote()
{
    emit Status(QString::number(m_Port) + "->服务：父类正常析构");
    if (m_Robot_Server_Thread && m_Robot_Server_Thread->isRunning()) {
        m_Robot_Server_Thread->requestInterruption();
        m_Robot_Server_Thread->quit();
        m_Robot_Server_Thread->wait();
    }
}

/*************************************************************************************************************************************************
**Function:初始化 - 创建TCP服务器线程，绑定信号槽，启动监听
*************************************************************************************************************************************************/
void c_Server_Remote::Init()
{
    m_Robot_Server = new c_Robot_Server;
    m_Robot_Server_Thread = new QThread;
    m_Robot_Server->moveToThread(m_Robot_Server_Thread);

    QObject::connect(m_Robot_Server_Thread, &QThread::started,
        m_Robot_Server, &c_Robot_Server::Init);
    QObject::connect(m_Robot_Server_Thread, &QThread::finished,
        m_Robot_Server, &c_Robot_Server::deleteLater);

    // 底层状态日志
    QObject::connect(m_Robot_Server, &c_Robot_Server::Status,
        this, [=](int state) {
        emit Status(QString::number(m_Port) + "->服务：错误码 " + QString::number(state));
    });

    // 跨线程连接与写入
    QObject::connect(this, &c_Server_Remote::Connect_Device,
        m_Robot_Server, &c_Robot_Server::Connect_Device);
    QObject::connect(this, &c_Server_Remote::Write_Json,
        m_Robot_Server, &c_Robot_Server::Write_Json);

    // 读就绪 (TCP 数据到达)
    QObject::connect(m_Robot_Server, &c_Robot_Server::Read_Done,
        this, &c_Server_Remote::Read_Done);

    // 断线自动重连
    QObject::connect(m_Robot_Server, &c_Robot_Server::Connect_Loop,
        this, [=]() {
        auto &cfg = c_Variable::getInstance().g_Communicate_DB;
        QString ip = cfg.value("Server_IP").toString("0.0.0.0");
        int port = cfg.value("Server_Port").toInt(520);
        QTimer::singleShot(6000, this, [=]() { Connect(ip, port); });
    });

    // ---- 追踪 g_Server 状态 ----
    QObject::connect(m_Robot_Server, &c_Robot_Server::Listen_Done, this, [=]() {
        c_Variable::getInstance().g_Server.Tran_Listen = true;
    });
    QObject::connect(m_Robot_Server, &c_Robot_Server::Connect_Done, this, [=]() {
        auto &s = c_Variable::getInstance().g_Server;
        s.Tran_Connected = true;
        s.num++;
    });
    QObject::connect(m_Robot_Server, &c_Robot_Server::Disconnect_Done, this, [=]() {
        auto &s = c_Variable::getInstance().g_Server;
        s.Tran_Connected = false;
        s.num = 0;
        s.Tran_Listen = false;
    });

    m_Robot_Server_Thread->start();

    // 从配置读取监听地址 → 自动启动服务
    auto &cfg = c_Variable::getInstance().g_Communicate_DB;
    QString ip = cfg.value("Server_IP").toString("0.0.0.0");
    int port = cfg.value("Server_Port").toInt(520);
    Connect(ip, port);
    m_Port = port;
}

/*************************************************************************************************************************************************
**Function:连接工作站服务器
*************************************************************************************************************************************************/
void c_Server_Remote::Connect(QString ip, int port)
{
    emit Connect_Device(ip, port);
}

/*************************************************************************************************************************************************
**Function:TCP数据入口 - 粘包安全解析：累积缓冲 → 按 {} 提取完整JSON
*************************************************************************************************************************************************/
void c_Server_Remote::Read_Done(QByteArray data)
{
    if (data.isEmpty()) return;
    m_RecvBuffer.append(data);

    int braceDepth = 0;
    int start = -1;
    int consumed = 0;

    for (int i = 0; i < m_RecvBuffer.size(); ++i) {
        char c = m_RecvBuffer[i];
        if (c == '{') {
            if (braceDepth == 0) start = i;
            braceDepth++;
        }
        else if (c == '}') {
            braceDepth--;
            if (braceDepth == 0 && start >= 0) {
                QByteArray piece = m_RecvBuffer.mid(start, i - start + 1);
                QJsonDocument doc = QJsonDocument::fromJson(piece);
                if (!doc.isNull() && doc.isObject())
                    Process_Command(doc.object());
                consumed = i + 1;
                start = -1;
            }
        }
    }
    m_RecvBuffer = m_RecvBuffer.mid(consumed);
}

/*************************************************************************************************************************************************
**Function:JSON命令路由分发 - 提取Cmd_Name，分发到对应处理函数
*************************************************************************************************************************************************/
void c_Server_Remote::Process_Command(const QJsonObject &json)
{
    // 提取校验值，所有回包需原样返回
    m_LastChecksum = json.value("Checksum").toString();

    // 兼容两个字段名
    QString cmd = json.value("Cmd_Name").toString();
    if (cmd.isEmpty()) cmd = json.value("command").toString();
    if (cmd.isEmpty()) {
        emit Status(QString::number(m_Port) + "->服务：缺少命令字段");
        return;
    }

    emit Status(QString::number(m_Port) + "->服务：收到 " + cmd);

    if (cmd == "START_INSPECTION") {
        Parse_Start_Inspection(json);
        emit Start_Cmd(json);
        return;
    }
    if (cmd == "Read_Ready") {
        if (!json.value("Value").toBool()) return;
        QJsonObject status = Build_System_Status();
        Write_Json_With_Checksum(status);
        return;
    }

    /* ---- 以下控制命令需状态校验 ---- */
    struct ControlMap {
        const char *name;
        int  allowedMask;
        void (c_Server_Remote::*signal)();
    };
    static const ControlMap table[] = {
        { "Cancel_Task",    SM_READY | SM_COLLECTING | SM_PAUSED | SM_ERROR, &c_Server_Remote::Cancel_Task_Cmd },
        { "Pause",          SM_COLLECTING,                                   &c_Server_Remote::Pause_Task_Cmd },
        { "Resume",         SM_PAUSED,                                       &c_Server_Remote::Resume_Task_Cmd },
        { "Emergency_Stop", SM_ANY,                                          &c_Server_Remote::Emergency_Stop_Cmd },
        { "Return_Home",    SM_IDLE | SM_READY | SM_COMPLETED | SM_ERROR,    &c_Server_Remote::Return_Home_Cmd },
    };
    for (const auto &entry : table) {
        if (cmd == entry.name) {
            if (!Check_State(cmd, entry.allowedMask)) return;
            (this->*(entry.signal))();
            Reply_Ok(cmd);
            return;
        }
    }

    emit Status(QString::number(m_Port) + "->服务：未知命令 " + cmd);
}

/*************************************************************************************************************************************************
**Function:合成系统全局状态 - 采集Magic/CGXi/Scan/Task数据
*************************************************************************************************************************************************/
QJsonObject c_Server_Remote::Build_System_Status()
{
    QJsonObject root;
    auto &all = c_Variable::getInstance();

    root["status"]    = "OK";
    root["timestamp"] = QDateTime::currentDateTime().toString("yyyyMMddHHmmss");

    // 2. 任务进度
    QJsonObject task;
    auto &work = all.g_Work_DB;
    task["taskId"]          = work.taskId;
    task["workState"]       = work.workState;
    task["currentWheelset"] = work.currentWheelset;
    task["currentPos"]      = work.currentPos;
    task["totalImages"]     = work.totalImages;
    task["wheelsetCount"]   = work.wheelsetCount;
    root["task"] = task;

    // 3. AMR 底盘
    QJsonObject chassis;
    auto &m = all.g_Magic;
    chassis["connected"]     = m.is_connected;
    chassis["localized"]     = m.ReadData.localized;
    chassis["battery"]       = m.ReadData.battery;
    chassis["chargeStatus"]  = m.ReadData.chargeStatus;
    chassis["emergencyStop"] = m.ReadData.emergencyStop;
    chassis["workingMode"]   = m.ReadData.workingMode;
    chassis["errorCode"]     = m.ReadData.errorCode;
    QJsonObject pos;
    pos["x"]     = m.ReadData.worldX;
    pos["y"]     = m.ReadData.worldY;
    pos["angle"] = m.ReadData.angle;
    chassis["position"] = pos;
    root["chassis"] = chassis;

    // 4. 机械臂
    QJsonObject arm;
    auto &c = all.g_CGXi;
    arm["connected"]           = c.Connected;
    arm["mode"]                = c.data.robot_mode;
    arm["programStatus"]       = c.data.program_status;
    arm["moving"]              = (c.data.robot_moving != 0);
    arm["errorCode"]           = c.data.last_error_code;
    arm["currentProgramIndex"] = c.data.current_program_index;
    arm["speedRatio"]          = c.data.speed_ratio;
    arm["powered"]             = (c.data.robot_power_on_indicator != 0);
    QJsonObject tcp;
    tcp["x"] = c.data.tcp_actual_position[0];
    tcp["y"] = c.data.tcp_actual_position[1];
    tcp["z"] = c.data.tcp_actual_position[2];
    tcp["rx"] = c.data.tcp_actual_position[3];
    tcp["ry"] = c.data.tcp_actual_position[4];
    tcp["rz"] = c.data.tcp_actual_position[5];
    arm["tcpPose"] = tcp;
    root["arm"] = arm;

    // 5. 相机
    QJsonObject camera;
    auto &scan = all.g_Prec_Scan_120;
    camera["remoteConnected"]  = scan.Remote_Connected;
    camera["monitorConnected"] = scan.Monitor_Connected;
    camera["tranConnected"]    = scan.Tran_Connected;
    camera["tranListen"]       = scan.Tran_Listen;
    root["camera"] = camera;

    // 6. WEB 服务自身
    QJsonObject svr;
    auto &s = all.g_Server;
    svr["clientConnected"] = s.Tran_Connected;
    svr["listening"]       = s.Tran_Listen;
    svr["clientCount"]     = s.num;
    root["server"] = svr;

    // 7. 最近报警
    QJsonArray warns;
    int n = qMin(5, all.g_Worry_List.size());
    for (int i = 0; i < n; ++i)
        warns.append(all.g_Worry_List[i].toString());
    root["recentAlarms"] = warns;

    return root;
}

/*************************************************************************************************************************************************
**Function:解析START_INSPECTION指令 → 填充g_Work_DB
*************************************************************************************************************************************************/
void c_Server_Remote::Parse_Start_Inspection(const QJsonObject &json)
{
    auto &w = c_Variable::getInstance().g_Work_DB;

    w.taskId      = json.value("taskId").toString();
    w.axleType    = json.value("axleType").toString();
    w.wheelsetNo  = json.value("wheelsetNo").toString();
    w.axleNo      = json.value("axleNo").toString();
    w.sendUnit    = json.value("sendUnit").toString();
    w.startTime   = json.value("startTime").toString();
    w.repairLevel = json.value("repairLevel").toString();
    w.wheelsetCount   = json.value("wheelsetCount").toInt(0);
    w.wheelsetPositions = json.value("wheelsetPositions").toArray();

    w.currentWheelset = 0;
    w.currentPos = 0;
    w.currentPoint = 0;
    w.workState = 1;
    w.errorCode = 0;
    w.totalImages = 0;

    emit Status(QString::number(m_Port) + "->服务：任务已解析 " + w.taskId);
}

/*************************************************************************************************************************************************
**Function:状态校验 - 位掩码匹配，失败时自动回复Error JSON
*************************************************************************************************************************************************/
bool c_Server_Remote::Check_State(const QString &cmd, int allowedMask)
{
    int st = c_Variable::getInstance().g_Work_DB.workState;
    if ((1 << st) & allowedMask) return true;

    static const char *name[] = { "空闲", "就绪", "采集中", "暂停", "完成", "错误" };
    QString cur = (st >= 0 && st < 6) ? name[st] : QString::number(st);
    Reply_Error(cmd, QString("状态[%1]不允许%2").arg(cur, cmd));
    return false;
}

/*************************************************************************************************************************************************
**Function:写入JSON并附加校验码
*************************************************************************************************************************************************/
void c_Server_Remote::Write_Json_With_Checksum(QJsonObject &obj)
{
    if (!m_LastChecksum.isEmpty())
        obj["Checksum"] = m_LastChecksum;
    emit Write_Json(obj);
}

/*************************************************************************************************************************************************
**Function:回复错误JSON
*************************************************************************************************************************************************/
void c_Server_Remote::Reply_Error(const QString &cmd, const QString &reason)
{
    QJsonObject rsp;
    rsp["Cmd_Name"] = cmd;
    rsp["Result"]   = "Error";
    rsp["Reason"]   = reason;
    rsp["taskId"]   = c_Variable::getInstance().g_Work_DB.taskId;
    Write_Json_With_Checksum(rsp);
    emit Status(QString::number(m_Port) + "->服务：" + reason);
}

/*************************************************************************************************************************************************
**Function:回复成功JSON
*************************************************************************************************************************************************/
void c_Server_Remote::Reply_Ok(const QString &cmd)
{
    QJsonObject rsp;
    rsp["Cmd_Name"] = cmd;
    rsp["Result"]   = "Executing";
    rsp["taskId"]   = c_Variable::getInstance().g_Work_DB.taskId;
    Write_Json_With_Checksum(rsp);
    emit Status(QString::number(m_Port) + "->服务：" + cmd + " 已执行");
}

/*************************************************************************************************************************************************
**Function:回传ACCEPTED状态至工作站
*************************************************************************************************************************************************/
void c_Server_Remote::Send_Accepted()
{
    QJsonObject rsp;
    rsp["status"] = "ACCEPTED";
    rsp["taskId"] = c_Variable::getInstance().g_Work_DB.taskId;
    Write_Json_With_Checksum(rsp);
}

/*************************************************************************************************************************************************
**Function:回传READY状态至工作站
*************************************************************************************************************************************************/
void c_Server_Remote::Send_Ready()
{
    QJsonObject rsp;
    rsp["status"] = "READY";
    rsp["taskId"] = c_Variable::getInstance().g_Work_DB.taskId;
    Write_Json_With_Checksum(rsp);
}

/*************************************************************************************************************************************************
**Function:回传COMPLETED状态至工作站（含图片总数）
*************************************************************************************************************************************************/
void c_Server_Remote::Send_Completed(int totalImages)
{
    QJsonObject rsp;
    rsp["status"]      = "COMPLETED";
    rsp["taskId"]      = c_Variable::getInstance().g_Work_DB.taskId;
    rsp["totalImages"] = totalImages;
    Write_Json_With_Checksum(rsp);
}

/*************************************************************************************************************************************************
**Function:回传ERROR状态至工作站（含错误码和描述）
*************************************************************************************************************************************************/
void c_Server_Remote::Send_Error(int errorCode, QString desc)
{
    QJsonObject rsp;
    rsp["status"]    = "ERROR";
    rsp["taskId"]    = c_Variable::getInstance().g_Work_DB.taskId;
    rsp["errorCode"] = errorCode;
    rsp["description"] = desc;
    Write_Json_With_Checksum(rsp);
}
