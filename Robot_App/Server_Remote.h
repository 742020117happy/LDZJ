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
    explicit c_Server_Remote(QObject *parent = nullptr);	// 构造函数
    virtual ~c_Server_Remote();								// 析构函数

    c_Robot_Server *m_Robot_Server = nullptr;		// TCP服务器对象
    QThread *m_Robot_Server_Thread = nullptr;		// TCP服务器工作线程
    int m_Port = 0;									// 监听端口

public slots:
    void Connect(QString ip, int port);				// 连接工作站服务器
    void Init();									// 初始化：创建服务器，绑定信号槽，启动监听
    void Read_Done(QByteArray buffer);				// TCP数据到达（粘包处理）

    /* ---------- 向工作站回传任务状态 ---------- */
    void Send_Accepted();							// 回传ACCEPTED状态
    void Send_Ready();								// 回传READY状态
    void Send_Completed(int totalImages);			// 回传COMPLETED（含图片总数）
    void Send_Error(int errorCode, QString desc);	// 回传ERROR（含错误码和描述）

signals:
    void Connect_Device(QString ip, int port);		// 跨线程：连接设备
    void Write_Json(QJsonObject cmd);				// 跨线程：写入JSON命令

    void Start_Cmd(QJsonObject cmd);				// START_INSPECTION指令
    void Cancel_Task_Cmd();							// 取消任务
    void Pause_Task_Cmd();							// 暂停
    void Resume_Task_Cmd();							// 暂停复位
    void Emergency_Stop_Cmd();						// 软急停
    void Return_Home_Cmd();							// 一键回原点

private:
    void Process_Command(const QJsonObject &json);			// JSON命令路由分发
    void Parse_Start_Inspection(const QJsonObject &json);	// 解析START_INSPECTION指令
    QJsonObject Build_System_Status();						// 合成系统全局状态
    bool Check_State(const QString &cmd, int allowedMask);	// 状态校验（位掩码）
    void Reply_Error(const QString &cmd, const QString &reason);	// 回复错误JSON
    void Reply_Ok(const QString &cmd);							// 回复成功JSON
    void Write_Json_With_Checksum(QJsonObject &obj);			// 写入JSON并附加校验码

    /* TCP 粘包缓冲 */
    QByteArray m_RecvBuffer;	// TCP接收缓冲区（粘包处理）
    QString m_LastChecksum;		// 最近一次命令校验码

    /* 状态码掩码 */
    enum StateMask {
        SM_IDLE       = 1 << 0,	// 空闲
        SM_READY      = 1 << 1,	// 就绪
        SM_COLLECTING = 1 << 2,	// 采集中
        SM_PAUSED     = 1 << 3,	// 暂停
        SM_COMPLETED  = 1 << 4,	// 完成
        SM_ERROR      = 1 << 5,	// 错误
        SM_ANY        = 0x3F,	// 任意状态
    };
};
