#pragma once
#include "Variable.h"
#include "Robot_Server.h"

/******************************************************************************
 *  工作站通信借口 —
 *  接收 WEB 端巡检任务指令 (TCP JSON) 及控制命令 (取消/暂停/复位/急停/回原点)，
 *  并响应 Read_Ready 定时轮询，合成系统全局状态。
 *
 *  协议详见: 轮对质检机器人-图像采集上传协议.md §二
 *
 *  线程模型:
 *    - m_Robot_Server 运行在 m_Robot_Server_Thread 子线程
 *    - 信号槽跨线程自动排队 (Qt::QueuedConnection)
 *    - g_Server 在主线程更新 (lambda 以 this 为 context)
 ******************************************************************************/
class c_Server_Remote : public c_Object
{
    Q_OBJECT
public:
    explicit c_Server_Remote(QObject *parent = nullptr);
    virtual ~c_Server_Remote();

    c_Robot_Server *m_Robot_Server = nullptr;
    QThread *m_Robot_Server_Thread = nullptr;
    int m_Port = 0;

public slots:
    void Connect(QString ip, int port);
    void Init();
    void Read_Done(QByteArray buffer);

    /* ---------- 向工作站回传任务状态 ---------- */
    void Send_Accepted();
    void Send_Ready();
    void Send_Completed(int totalImages);
    void Send_Error(int errorCode, QString desc);

signals:
    void Connect_Device(QString ip, int port);
    void Write_Json(QJsonObject cmd);

    void Start_Cmd(QJsonObject cmd);         // START_INSPECTION
    void Cancel_Task_Cmd();                  // 取消任务
    void Pause_Task_Cmd();                   // 暂停
    void Resume_Task_Cmd();                  // 暂停复位
    void Emergency_Stop_Cmd();               // 软急停
    void Return_Home_Cmd();                  // 一键回原点

private:
    void Process_Command(const QJsonObject &json);
    void Parse_Start_Inspection(const QJsonObject &json);
    QJsonObject Build_System_Status();
    bool Check_State(const QString &cmd, int allowedMask);
    void Reply_Error(const QString &cmd, const QString &reason);
    void Reply_Ok(const QString &cmd);
    void Write_Json_With_Checksum(QJsonObject &obj);

    /* TCP 粘包缓冲 */
    QByteArray m_RecvBuffer;
    QString m_LastChecksum;

    /* 状态码掩码 */
    enum StateMask {
        SM_IDLE       = 1 << 0,
        SM_READY      = 1 << 1,
        SM_COLLECTING = 1 << 2,
        SM_PAUSED     = 1 << 3,
        SM_COMPLETED  = 1 << 4,
        SM_ERROR      = 1 << 5,
        SM_ANY        = 0x3F,
    };
};
