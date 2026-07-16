#pragma execution_character_set("utf-8")
#include "CGXi_Remote.h"
#include <cstring>

/*************************************************************************************************************************************************
**Function:构造函数 - 注册ModBus数据结构元类型以供跨线程信号槽传递
*************************************************************************************************************************************************/
c_CGXi_Remote::c_CGXi_Remote(QObject *parent) : c_Object(parent) {
	qRegisterMetaType<s_ModBus_DB>("s_ModBus_DB");
}

/*************************************************************************************************************************************************
**Function:析构函数 - 请求中断并等待ModBus工作线程退出
*************************************************************************************************************************************************/
c_CGXi_Remote::~c_CGXi_Remote() {
	if (m_ModeBusTCP_Thread && m_ModeBusTCP_Thread->isRunning()) {
		m_ModeBusTCP_Thread->requestInterruption();
		m_ModeBusTCP_Thread->quit();
		m_ModeBusTCP_Thread->wait(5000);
	}
}

/*************************************************************************************************************************************************
**Function:初始化 - 创建ModBus客户端，移至工作线程，绑定信号槽，启动连接
*************************************************************************************************************************************************/
void c_CGXi_Remote::Init() {
	m_ModeBusTCP = new c_ModeBusTCP_Client;
	m_ModeBusTCP_Thread = new QThread;
	m_ModeBusTCP->moveToThread(m_ModeBusTCP_Thread);

	QObject::connect(m_ModeBusTCP_Thread, &QThread::started, m_ModeBusTCP, &c_ModeBusTCP_Client::Init);
	QObject::connect(m_ModeBusTCP_Thread, &QThread::finished, m_ModeBusTCP, &c_ModeBusTCP_Client::deleteLater);
	QObject::connect(this, &c_CGXi_Remote::Connect_Device, m_ModeBusTCP, &c_ModeBusTCP_Client::Connect_Device);
	QObject::connect(this, &c_CGXi_Remote::Disconnect_Device, m_ModeBusTCP, &c_ModeBusTCP_Client::Disconnect_Device);
	QObject::connect(m_ModeBusTCP, &c_ModeBusTCP_Client::Connect_Loop, this, &c_CGXi_Remote::Connect_Loop);

	QObject::connect(this, &c_CGXi_Remote::Write_Coils, m_ModeBusTCP, &c_ModeBusTCP_Client::Write_Coils);

	QObject::connect(this, &c_CGXi_Remote::Read_HoldingRegisters, m_ModeBusTCP, &c_ModeBusTCP_Client::Read_HoldingRegisters);
	QObject::connect(this, &c_CGXi_Remote::Write_HoldingRegisters, m_ModeBusTCP, &c_ModeBusTCP_Client::Write_HoldingRegisters);

	QObject::connect(m_ModeBusTCP, &c_ModeBusTCP_Client::Write_Coils_Done, this, &c_CGXi_Remote::Write_Coils_Done);

	QObject::connect(m_ModeBusTCP, &c_ModeBusTCP_Client::Read_HoldingRegisters_Done, this, &c_CGXi_Remote::Read_HoldingRegisters_Done);
	QObject::connect(m_ModeBusTCP, &c_ModeBusTCP_Client::Write_HoldingRegisters_Done, this, &c_CGXi_Remote::Write_HoldingRegisters_Done);
	QObject::connect(m_ModeBusTCP, &c_ModeBusTCP_Client::Write_HoldingRegisters_Error, this, &c_CGXi_Remote::Write_HoldingRegisters_Done);
	QObject::connect(m_ModeBusTCP, &c_ModeBusTCP_Client::Read_HoldingRegisters_Error, this, &c_CGXi_Remote::Read_HoldingRegisters_Done);
	QObject::connect(m_ModeBusTCP, &c_ModeBusTCP_Client::Connect_Done, this, &c_CGXi_Remote::Connect_Done);
	QObject::connect(m_ModeBusTCP, &c_ModeBusTCP_Client::Disconnect_Done, this, &c_CGXi_Remote::Disconnect_Done);
	QObject::connect(m_ModeBusTCP, &c_ModeBusTCP_Client::Status, this, [=](int state) {emit Status("CGXi遥控： " + Modbus_Status(state)); });

	m_ModeBusTCP_Thread->start();
	QTimer::singleShot(1500, this, &c_CGXi_Remote::Connect);
}

// ================= 连接管理 =================
/*************************************************************************************************************************************************
**Function:连接CGXi机械臂 - 从全局配置读取IP/端口并发起ModBus TCP连接
*************************************************************************************************************************************************/
void c_CGXi_Remote::Connect() {
	QString ip = c_Variable::getInstance().g_Communicate_DB.value("CGXi_Ip").toString();
	int port = c_Variable::getInstance().g_Communicate_DB.value("CGXi_Port").toInt();
	emit Status("CGXi遥控：" + ip + "：" + QString::number(port));
	emit Connect_Device(ip, port);
}

/*************************************************************************************************************************************************
**Function:连接循环 - 未连接时每3秒重试一次
*************************************************************************************************************************************************/
void c_CGXi_Remote::Connect_Loop() {
	if (c_Variable::getInstance().g_CGXi.Connected) return;
	QTimer::singleShot(3000, this, &c_CGXi_Remote::Connect);
}

/*************************************************************************************************************************************************
**Function:连接完成回调 - 标记已连接，启动1000个寄存器分批读取
*************************************************************************************************************************************************/
void c_CGXi_Remote::Connect_Done() {
	m_Time.start();
	c_Variable::getInstance().g_CGXi.Connected = true;
	emit Read_HoldingRegisters(0, 124);
}

/*************************************************************************************************************************************************
**Function:断开完成回调 - 清除已连接状态
*************************************************************************************************************************************************/
void c_CGXi_Remote::Disconnect_Done() {
	c_Variable::getInstance().g_CGXi.Connected = false;
}

// ================= 状态机流转 =================
/*************************************************************************************************************************************************
**Function:保持寄存器读取完成 - 分批读取1000个寄存器，处理写队列，继续下一批
*************************************************************************************************************************************************/
void c_CGXi_Remote::Read_HoldingRegisters_Done(s_ModBus_DB data) {
	c_Variable::getInstance().g_CGXi.Ready = !c_Variable::getInstance().g_CGXi.Ready;

	int Read_HoldingRegisters_Addr = m_Read_HoldingRegisters_Count * 124;
	int Read_HoldingRegisters_Size = m_HoldingRegisters_Size - Read_HoldingRegisters_Addr;

	if (Read_HoldingRegisters_Size >= 124) { emit Read_HoldingRegisters(Read_HoldingRegisters_Addr, 124); m_Read_HoldingRegisters_Count += 1; return; }
	if (Read_HoldingRegisters_Size > 0) { emit Read_HoldingRegisters(Read_HoldingRegisters_Addr, Read_HoldingRegisters_Size); m_Read_HoldingRegisters_Count += 1; return; }

	//直到 Read_HoldingRegisters_Size < 0 才会执行到这里，即1000个寄存器完全读取完成
	//所有1000个寄存器读完再一次性赋值，无需担心分段问题
	std::memcpy(c_Variable::getInstance().g_CGXi.read_HoldingRegisters, data.read_HoldingRegisters, sizeof(data.read_HoldingRegisters));

	if (m_FPS == 100) { c_Variable::getInstance().g_CGXi.FPS = 100000 / m_Time.restart(); m_FPS = 0; }
	m_FPS += 1;
	
	// 尝试执行写入动作 (读写互斥)
	if (Write_Coils_Action()) return;
	if (Write_HoldingRegisters_Action()) return;

	//继续读保持寄存器
	m_Read_HoldingRegisters_Count = 0;
	emit Read_HoldingRegisters(0, 124);
}
/*************************************************************************************************************************************************
**Function:保持寄存器写入完成 - 读回验证，恢复读取循环
*************************************************************************************************************************************************/
void c_CGXi_Remote::Write_HoldingRegisters_Done() {
	c_Variable::getInstance().g_CGXi.Ready = !c_Variable::getInstance().g_CGXi.Ready;

	Read_HoldingRegisters_Action();

	//继续读保持寄存器
	int Read_HoldingRegisters_Addr = m_Read_HoldingRegisters_Count * 124;
	int Read_HoldingRegisters_Size = m_HoldingRegisters_Size - Read_HoldingRegisters_Addr;
	if (Read_HoldingRegisters_Size >= 124) { emit Read_HoldingRegisters(Read_HoldingRegisters_Addr, 124); m_Read_HoldingRegisters_Count += 1; return; }
	if (Read_HoldingRegisters_Size > 0) { emit Read_HoldingRegisters(Read_HoldingRegisters_Addr, Read_HoldingRegisters_Size); m_Read_HoldingRegisters_Count += 1; return; }
	//直到 Read_HoldingRegisters_Size < 0 才会执行到这里
	m_Read_HoldingRegisters_Count = 0;
	emit Read_HoldingRegisters(0, 124);
}
/*************************************************************************************************************************************************
**Function:线圈写入完成回调 - 恢复保持寄存器读取循环
*************************************************************************************************************************************************/
void c_CGXi_Remote::Write_Coils_Done()
{
	c_Variable::getInstance().g_CGXi.Ready = !c_Variable::getInstance().g_CGXi.Ready;

	emit Status("CGXi遥控：线圈操作完成 ");

	//继续读保持寄存器
	int Read_HoldingRegisters_Addr = m_Read_HoldingRegisters_Count * 124;
	int Read_HoldingRegisters_Size = m_HoldingRegisters_Size - Read_HoldingRegisters_Addr;
	if (Read_HoldingRegisters_Size >= 124) { emit Read_HoldingRegisters(Read_HoldingRegisters_Addr, 124); m_Read_HoldingRegisters_Count += 1; return; }
	if (Read_HoldingRegisters_Size > 0) { emit Read_HoldingRegisters(Read_HoldingRegisters_Addr, Read_HoldingRegisters_Size); m_Read_HoldingRegisters_Count += 1; return; }
	//直到 Read_HoldingRegisters_Size < 0 才会执行到这里
	m_Read_HoldingRegisters_Count = 0;
	emit Read_HoldingRegisters(0, 124);
}
/*************************************************************************************************************************************************
**Function:执行保持寄存器写入 - 遍历写请求队列，找到第一个待写入寄存器并分派
*************************************************************************************************************************************************/
bool c_CGXi_Remote::Write_HoldingRegisters_Action() {
	for (int i = 0; i < m_HoldingRegisters_Size; i++) {
		if (m_Set_HoldingRegisters[i]) {
			s_ModBus_DB syncData;
			std::memcpy(syncData.write_HoldingRegisters, c_Variable::getInstance().g_CGXi.write_HoldingRegisters, sizeof(syncData.write_HoldingRegisters));
			switch (i)
			{
			case 15:
				//15: 可配置数字输出
				emit Write_HoldingRegisters(i, 1, syncData);
				break;
			case 27:
				//27: 工具端标准数字输出
				emit Write_HoldingRegisters(i, 1, syncData);
				break;
			case 63:
				// 63: 清除错误
				emit Write_HoldingRegisters(i, 1, syncData);
				break;
			case 64:
				// 64: 清除警告
				emit Write_HoldingRegisters(i, 1, syncData);
				break;
			case 88:
				//88: 目标程序索引
				emit Write_HoldingRegisters(i, 1, syncData);
				break;
			case 89:
				//89: 目标程序操作
				emit Write_HoldingRegisters(i, 1, syncData);
				break;
			case 700:
				// 700-711: TCP法兰偏移
				emit Write_HoldingRegisters(i, 12, syncData);
				break;
			case 720:
				// 720-727: 负载mass和质心
				emit Write_HoldingRegisters(i, 8, syncData);
				break;
			case 730:
				// 730-731: 运动速度比例 (float)
				emit Write_HoldingRegisters(i, 2, syncData);
				break;
			case 800:
				// 800: 点动类型
				emit Write_HoldingRegisters(i, 1, syncData);
				break;
			case 801:
				// 801-802: 点动速度比例
				emit Write_HoldingRegisters(i, 2, syncData);
				break;
			case 803:
				// 803: 点动坐标系
				emit Write_HoldingRegisters(i, 1, syncData);
				break;
			case 810:
				// 810 - 821 : 点动目标位置
				emit Write_HoldingRegisters(i, 12, syncData);
				break;
			default:
				emit Status("CGXi遥控：写寄存器 " + QString::number(i) + "无权限");
				return false;
			}
			emit Status("CGXi遥控：写寄存器 " + QString::number(i));
			return true;
		}
	}
	return false;
}
/*************************************************************************************************************************************************
**Function:读回验证 - 输出写入前后寄存器值对比日志
*************************************************************************************************************************************************/
void c_CGXi_Remote::Read_HoldingRegisters_Action() {
	for (int i = 0; i < m_HoldingRegisters_Size; i++) {
		if (m_Set_HoldingRegisters[i]) {
			m_Set_HoldingRegisters[i] = false;

			QString inout;

			switch (i)
			{
			case 15:
				//15: 可配置数字输出
				inout = QString("输入<data>：[%1]；输出<Transfer>：[%2]")
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.configurable_digital_output, 2).rightJustified(16, '0'))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.configurable_digital_output, 2).rightJustified(16, '0'));
				emit Status("CGXi遥控：写寄存器完成 " + QString::number(i) + "可配置数字输出->" + inout);
				break;
			case 27:
				//27: 工具端标准数字输出
				inout = QString("输入<data>：[%1]；输出<Transfer>：[%2]")
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.tool_standard_digital_output, 2).rightJustified(16, '0'))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.tool_standard_digital_output, 2).rightJustified(16, '0'));
				emit Status("CGXi遥控：写寄存器完成 " + QString::number(i) + "工具端数字输出->" + inout);
				break;
			case 63:
				// 63: 清除错误
				inout = QString("输入<data>：[%1]；输出<Transfer>：[%2]")
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.clear_robot_error, 2).rightJustified(16, '0'))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.clear_robot_error, 2).rightJustified(16, '0'));
				emit Status("CGXi遥控：写寄存器完成 " + QString::number(i) + "清除错误->" + inout);
				break;
			case 64:
				// 64: 清除警告
				inout = QString("输入<data>：[%1]；输出<Transfer>：[%2]")
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.clear_robot_warning, 2).rightJustified(16, '0'))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.clear_robot_warning, 2).rightJustified(16, '0'));
				emit Status("CGXi遥控：写寄存器完成 " + QString::number(i) + "清除警告->" + inout);
				break;
			case 88:
				//88: 目标程序索引
				inout = QString("输入<data>：[%1]；输出<Transfer>：[%2]")
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.target_program_index))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.target_program_index));
				emit Status("CGXi遥控：写寄存器完成 " + QString::number(i) + "目标程序索引->" + inout);
				break;
			case 89:
				//89: 目标程序操作
				inout = QString("输入<data>：[%1]；输出<Transfer>：[%2]")
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.target_program_operation))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.target_program_operation));
				emit Status("CGXi遥控：写寄存器完成 " + QString::number(i) + "目标程序操作->" + inout);
				break;
			case 700:
				// 700-711: TCP法兰偏移
				inout = QString("输入<data>：[%1,%2,%3,%4,%5,%6]； 输出<Transfer>：[%7,%8,%9,%10,%11,%12]")
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.tcp_flange_offset[0]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.tcp_flange_offset[1]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.tcp_flange_offset[2]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.tcp_flange_offset[3]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.tcp_flange_offset[4]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.tcp_flange_offset[5]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.tcp_flange_offset[0]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.tcp_flange_offset[1]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.tcp_flange_offset[2]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.tcp_flange_offset[3]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.tcp_flange_offset[4]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.tcp_flange_offset[5]));
				emit Status("CGXi遥控：写寄存器完成 " + QString::number(i) + "TCP法兰偏移->" + inout);
				break;
			case 720:
				// 720-727: 负载mass和质心
				inout = QString("输入<data>：[%1,%2,%3,%4]；输出<Transfer>：[%5,%6,%7,%8]")
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.payload_mass_and_cog[0]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.payload_mass_and_cog[1]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.payload_mass_and_cog[2]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.payload_mass_and_cog[3]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.payload_mass_and_cog[0]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.payload_mass_and_cog[1]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.payload_mass_and_cog[2]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.payload_mass_and_cog[3]));
				emit Status("CGXi遥控：写寄存器完成 " + QString::number(i) + "负载mass和质心->" + inout);
				break;
			case 730:
				// 730-731: 运动速度比例
				inout = QString("输入<data>：[%1]；输出<Transfer>：[%2]")
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.speed_ratio))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.speed_ratio));
				emit Status("CGXi遥控：写寄存器完成 " + QString::number(i) + "速度比例->" + inout);
				break;
			case 800:
				// 800: 点动类型
				inout = QString("输入<data>：[%1]；输出<Transfer>：[%2]")
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.jog_type))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.jog_type));
				emit Status("CGXi遥控：写寄存器完成 " + QString::number(i) + "点动类型->" + inout);
				break;
			case 801:
				// 801-802: 点动速度比例
				inout = QString("输入<data>：[%1]；输出<Transfer>：[%2]")
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.jog_speed_ratio))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.jog_speed_ratio));
				emit Status("CGXi遥控：写寄存器完成 " + QString::number(i) + "点动速度比例->" + inout);
				break;
			case 803:
				// 803: 点动坐标系
				inout = QString("输入<data>：[%1]；输出<Transfer>：[%2]")
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.jog_coordinate_system))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.jog_coordinate_system));
				emit Status("CGXi遥控：写寄存器完成 " + QString::number(i) + "点动坐标系->" + inout);
				break;
			case 810:
				// 810 - 821 : 点动目标位置
				inout = QString("输入<data>：[%1,%2,%3,%4,%5,%6]；输出<Transfer>：[%7,%8,%9,%10,%11,%12]")
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.jog_target_position[0]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.jog_target_position[1]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.jog_target_position[2]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.jog_target_position[3]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.jog_target_position[4]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.data.jog_target_position[5]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.jog_target_position[0]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.jog_target_position[1]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.jog_target_position[2]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.jog_target_position[3]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.jog_target_position[4]))
					.arg(QString::number(c_Variable::getInstance().g_CGXi.Transfer.jog_target_position[5]));
				emit Status("CGXi遥控：写寄存器完成 " + QString::number(i) + "点动目标位置->" + inout);
				break;
			default:
				m_Set_HoldingRegisters[i] = false;
				emit Status("CGXi遥控：写寄存器 " + QString::number(i) + "异常操作");
			}
		}
	}
}
/*************************************************************************************************************************************************
**Function:执行线圈写入 - 遍历Set/Reset请求队列，分派第一个待操作线圈
*************************************************************************************************************************************************/
bool c_CGXi_Remote::Write_Coils_Action()
{
	for (int i = 0; i < m_Coils_Size; i++) {
		if (m_Set_Coils[i]) {
			m_Set_Coils[i] = false;
			s_ModBus_DB syncData;
			syncData.write_Coils[1000 + i] = 1;
			emit Write_Coils(1000 + i, 1, syncData);
			emit Status("CGXi遥控：线圈置位 " + QString::number(i));
			return true;
		}

		if (m_Reset_Coils[i]) {
			m_Reset_Coils[i] = false;
			s_ModBus_DB syncData;
			syncData.write_Coils[1000 + i] = 0;
			emit Write_Coils(1000 + i, 1, syncData);
			emit Status("CGXi遥控：线圈复位 " + QString::number(i));
			return true;
		}
	}
	return false;
}
/*************************************************************************************************************************************************
**Function:线圈置位/复位触发接口 - 对应线圈地址1000-1007
*************************************************************************************************************************************************/
// ================= 寄存器写入触发接口实现 =================
// ========== 线圈置位/复位触发接口 ========== (对应资料线圈地址1000-1007通用BOOL寄存器)
void c_CGXi_Remote::Set_Coils_1000() { m_Set_Coils[0] = true; }
void c_CGXi_Remote::Set_Coils_1001() { m_Set_Coils[1] = true; }
void c_CGXi_Remote::Set_Coils_1002() { m_Set_Coils[2] = true; }
void c_CGXi_Remote::Set_Coils_1003() { m_Set_Coils[3] = true; }
void c_CGXi_Remote::Set_Coils_1004() { m_Set_Coils[4] = true; }
void c_CGXi_Remote::Set_Coils_1005() { m_Set_Coils[5] = true; }
void c_CGXi_Remote::Set_Coils_1006() { m_Set_Coils[6] = true; }
void c_CGXi_Remote::Set_Coils_1007() { m_Set_Coils[7] = true; }

void c_CGXi_Remote::Reset_Coils_1000() { m_Reset_Coils[0] = true; }
void c_CGXi_Remote::Reset_Coils_1001() { m_Reset_Coils[1] = true; }
void c_CGXi_Remote::Reset_Coils_1002() { m_Reset_Coils[2] = true; }
void c_CGXi_Remote::Reset_Coils_1003() { m_Reset_Coils[3] = true; }
void c_CGXi_Remote::Reset_Coils_1004() { m_Reset_Coils[4] = true; }
void c_CGXi_Remote::Reset_Coils_1005() { m_Reset_Coils[5] = true; }
void c_CGXi_Remote::Reset_Coils_1006() { m_Reset_Coils[6] = true; }
void c_CGXi_Remote::Reset_Coils_1007() { m_Reset_Coils[7] = true; }

/*************************************************************************************************************************************************
**Function:保持寄存器写入触发接口 - 将对应寄存器标记为待写入
*************************************************************************************************************************************************/
// ========== 保持寄存器写入触发接口 ========== 将对应寄存器标记为待写入
void c_CGXi_Remote::Set_HoldingRegisters_15() { m_Set_HoldingRegisters[15] = true; }  // 15: 可配置数字输出
void c_CGXi_Remote::Set_HoldingRegisters_27() { m_Set_HoldingRegisters[27] = true; }  // 工具端标准数字输出
void c_CGXi_Remote::Set_HoldingRegisters_63() { m_Set_HoldingRegisters[63] = true; }  // 清除机器人错误(脉冲)
void c_CGXi_Remote::Set_HoldingRegisters_64() { m_Set_HoldingRegisters[64] = true; }  // 清除机器人警告(脉冲)
void c_CGXi_Remote::Set_HoldingRegisters_88() { m_Set_HoldingRegisters[88] = true; }  // 目标程序索引
void c_CGXi_Remote::Set_HoldingRegisters_89() { m_Set_HoldingRegisters[89] = true; } // 目标程序操作 (1-启动 2-暂停 3-停止)
void c_CGXi_Remote::Set_HoldingRegisters_700() { m_Set_HoldingRegisters[700] = true; } // tcp相对法兰偏移 (700-711)
void c_CGXi_Remote::Set_HoldingRegisters_720() { m_Set_HoldingRegisters[720] = true; } // 负载mass和质心 (720-727)
void c_CGXi_Remote::Set_HoldingRegisters_730() { m_Set_HoldingRegisters[730] = true; } // 运动速度比例 (730-731)
void c_CGXi_Remote::Set_HoldingRegisters_800() { 
	m_Set_HoldingRegisters[800] = true; // 点动类型 (同时触发运动)
	m_Set_HoldingRegisters[801] = true; // 点动速度比例 (级联写入,下周期处理)
	m_Set_HoldingRegisters[803] = true; // 点动坐标系
	m_Set_HoldingRegisters[810] = true; // 点动目标位置
}
void c_CGXi_Remote::Set_HoldingRegisters_801() { m_Set_HoldingRegisters[801] = true; } // 点动速度比例 (801-802)
void c_CGXi_Remote::Set_HoldingRegisters_803() { m_Set_HoldingRegisters[803] = true; } // 点动坐标系
void c_CGXi_Remote::Set_HoldingRegisters_810() { m_Set_HoldingRegisters[810] = true; } // 点动目标位置 (810-821，底层自动打包12个寄存器)