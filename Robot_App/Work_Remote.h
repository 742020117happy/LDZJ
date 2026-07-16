#pragma once
#include "Variable.h"

class c_Work_Remote : public c_Object
{
    Q_OBJECT
public:
    explicit c_Work_Remote(QObject *parent = nullptr);
    ~c_Work_Remote();

    bool m_Running = false;
    bool m_Paused = false;
    bool m_CancelRequested = false;

public slots:
    void Init();
    void Start_Inspection();
    void Pause_Inspection();
    void Resume_Inspection();
    void Cancel_Inspection();
    void Emergency_Stop();
    void Return_Home();

signals:
    void Signal_Magic_Navigate(QString pointName);
    void Signal_Magic_Charge();
    void Signal_CGXi_SetProgram(int index);
    void Signal_CGXi_Start();
    void Signal_CGXi_Stop();
    void Signal_Camera_Write(QString ip, int port, QString value);
    void Signal_CGXi_Write(QString value);
    void Signal_Server_Accepted();
    void Signal_Server_Ready();
    void Signal_Server_Completed(int totalImages);
    void Signal_Server_Error(int errorCode, QString desc);
    void Step_Done();
    void Step_Failed(QString reason);
    void Work_Log(QString msg);
    void Work_State_Changed(int state, QString desc);

private:
    void Run_Inspection();
    void Do_NavigateToPosition(QString pointName);
    void Do_NavigateToCharge();
    void Do_SetCGXiProgram(int index);
    void Do_StartCGXi();
    void Do_WaitCGXiStart();
    void Do_SendCameraStart();
    void Do_SendCameraPhoto(QString gain, QString prog, QString part1, QString part2, QString point);
    void Do_WaitCameraComplete();
    void Do_SendCGXiComplete();
    void Do_SendCameraFinish();
    void Do_SendServerAccepted();
    void Do_SendServerReady();
    void Do_SendServerCompleted(int totalImages);

    QTimer *m_WorkflowTimer = nullptr;
    int m_WorkflowStep = 0;
    QString m_CurrentTaskId;
    QString m_CurrentIP;
    int m_CurrentPort = 0;
};

// c_Sql_Remote is defined in MySql_Remote.h
