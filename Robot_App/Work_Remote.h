#pragma once
#include "Variable.h"


class c_Work_Remote : public c_Object
{
	Q_OBJECT
public:
	explicit c_Work_Remote(QObject *parent = nullptr);
	virtual ~c_Work_Remote();

public slots:
	void Init();
	void Start_Cmd(QJsonObject object);
	void System_Sleep();

signals:
	void System_Scan_Done();
	void Write_Json(QJsonObject json);
	void Set_Navigate(QString point);
	void Reset_Navigate();
	void Set_Navigate_Done();
	void Reset_Navigate_Done();
	void Set_Charge();
	void Set_Charge_Done();
	void Set_CGXi_Program(int index);
	void Reset_CGXi_Program();
	void Set_CGXi_Program_Done();
	void Reset_CGXi_Program_Done();
	void Set_CGXi_Start();
	void Reset_CGXi_Start();
	void Set_CGXi_Start_Done();
	void Reset_CGXi_Start_Done();
	void Set_CGXi_Complete();
	void Set_CGXi_Complete_Done();
	void State_CGXi_Finish();
	void write_Camera_Start(QString cmd);
	void write_Camera_Gain(QString cmd);
	void write_Camera_Photo(QString cmd);
	void write_Camera_Finish();
	void State_Camera_Photo();
	void State_Camera_Error();
	void Set_Server_Accepted();
	void Set_Server_Accepted_Done();
	void Set_Server_Ready();
	void Set_Server_Ready_Done();
	void Set_Server_Completed(int totalImages);
	void Set_Server_Completed_Done();
	void Set_Server_Error(int errorCode, QString desc);
	void Set_Server_Error_Done();

private:
	QJsonObject m_Work_Program;
	QJsonObject m_Current_Work;
	int m_System_Sleep_Num = 0;
	QString m_Checksum;
	QString m_CurrentIP;
	int m_CurrentPort = 8001;
	int m_LastGain = -1;

private slots:
	void is_Short_Short();
	void is_Null_Short();
	void is_Short_Null();
	void Load_Program(int id);
	void Wait_Navigate(QString point);
	void Wait_Charge();
	void Wait_CGXi_Program(int index);
	void Wait_CGXi_Start();
	void Wait_CGXi_Stop();
	void Wait_CGXi_Complete();
	void Wait_CGXi_Finish();
	void Wait_Camera_Start(QString cmd);
	void Wait_Camera_Photo(QString gain, QString prog, QString part1, QString part2, QString point);
	void Wait_Camera_Finish();
	void Wait_Server_Accepted();
	void Wait_Server_Ready();
	void Wait_Server_Completed(int totalImages);
	void Wait_Server_Error(int errorCode, QString desc);
};
