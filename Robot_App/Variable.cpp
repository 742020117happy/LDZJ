#pragma execution_character_set("utf-8")
#include "Variable.h"
/*************************************************************************************************************************************************
**Function:构造函数
*************************************************************************************************************************************************/
c_Object::c_Object(QObject *parent) : QObject(parent)
{

}
/*************************************************************************************************************************************************
**Function:析构函数
*************************************************************************************************************************************************/
c_Object::~c_Object()
{
	qDebug() << "~c_Object()";
}
/*************************************************************************************************************************************************
**Function:通讯错误信息
*************************************************************************************************************************************************/
QString c_Object::TCP_Status(int State)
{
	switch (State)
	{
	case 0:return "连接被对等方拒绝（或超时）";
	case 1:return "远程主机关闭了连接。请注意，客户端套接字（即此套接字）将在发送远程关闭通知后关闭";
	case 2:return "找不到主机地址";
	case 3:return "套接字操作失败，因为应用程序缺少所需的权限";
	case 4:return "本地系统资源不足（例如，套接字过多）";
	case 5:return "套接字操作超时";
	case 6:return "数据报大于操作系统的限制（可低至8192字节）";
	case 7:return "网络发生错误（例如，网络电缆意外插拔）";
	case 8:return "为QAbstractSocket:：bind（）指定的地址已在使用中，并被设置为独占";
	case 9:return "为QAbstractSocket:：bind（）指定的地址不属于主机";
	case 10:return "本地操作系统不支持请求的套接字操作（例如，缺少IPv6支持）";
	case 11:return "仅由QAbstractSocketEngine使用，上次尝试的操作尚未完成（仍在后台进行）";
	case 12:return "套接字正在使用代理，代理需要身份验证";
	case 13:return "SSL/TLS握手失败，因此连接已关闭（仅在QSslSocket中使用）";
	case 14:return "无法联系代理服务器，因为与该服务器的连接被拒绝";
	case 15:return "与代理服务器的连接意外关闭（在与最终对等方建立连接之前）";
	case 16:return "与代理服务器的连接超时，或者代理服务器在身份验证阶段停止响应。";
	case 17:return "找不到使用setProxy（）设置的代理地址（或应用程序代理）";
	case 18:return "与代理服务器的连接协商失败，因为无法理解来自代理服务器的响应";
	case 19:return "当套接字处于不允许的状态时，尝试了一个操作";
	case 20:return "正在使用的SSL库报告了一个内部错误。这可能是由于库的安装错误或配置错误造成的";
	case 21:return "提供了无效数据（证书、密钥、密码等），其使用导致SSL库中出现错误";
	case 22:return "发生临时错误（例如，操作将被阻塞，套接字为非阻塞）";
	case 23:return "套接字未连接";
	case 24:return "套接字正在执行主机名查找";
	case 25:return "套接字已开始建立连接";
	case 26:return "建立了一个连接";
	case 27:return "套接字绑定到一个地址和端口";
	case 28:return "套接字即将关闭（数据可能仍在等待写入）";
	case 29:return "套接字监听状态（仅供内部使用）";
	case -1:return "发生了一个无法识别的错误";
	default:return "无状态";
	}
}
// 将Modbus设备状态码(0-11)转换为中文描述
QString c_Object::Modbus_Status(int State)
{
	switch (State)
	{
	case 0:return "已连接";
	case 1:return "读取操作期间发生错误";
	case 2:return "写入操作期间发生错误";
	case 3:return "尝试打开后端时出错";
	case 4:return "尝试设置配置参数时出错";
	case 5:return "I/O期间发生超时。I/O操作未在给定的时间范围内完成";
	case 6:return "发生Modbus特定协议错误";
	case 7:return "由于设备断开连接，回复被中止";
	case 8:return "发生未知错误";
	case 9:return "设备已断开连接";
	case 10:return "正在连接设备";
	case 11:return "设备正在关闭";
	default:return "无状态";
	}
}
// 将CGXi机器人错误码(0-27)转换为中文描述
QString c_Object::CGXi_Status(int State)
{
	switch (State)
	{
	case 0:  return "正常";
	case 1:  return "一般错误";
	case 2:  return "通讯连接重复建立";
	case 3:  return "操作超时，无返回值";
	case 4:  return "返回结果无效";
	case 5:  return "输入数值越界";
	case 6:  return "内部互斥锁错误";
	case 7:  return "参数无效";
	case 8:  return "无对应数值";
	case 9:  return "未找到指定索引号TCP偏移量";
	case 10: return "未创建相关句柄";
	case 11: return "重复建立相同的句柄";
	case 12: return "重命名失败";
	case 13: return "删除唯一的TCP或者负载失败";
	case 14: return "同时设置位寄存器输入与输出失败";
	case 15: return "ID重复";
	case 16: return "文件加密错误";
	case 17: return "当前状态不能执行该操作";
	case 18: return "移动阻塞运动状态错误";
	case 19: return "力控SDK参数设置错误";
	case 20: return "力控SDK无效的指令";
	case 21: return "力控SDK自由驱动模式下参数失效被屏蔽";
	case 22: return "已在力控模式下禁止再打开力控";
	case 23: return "机器人运动或力控模式下禁止下发配置";
	case 24: return "机器人使能之前不能打开传感器";
	case 25: return "力控传感器型号选择错误";
	case 26: return "未设置系统输出，禁止启用自复位";
	case 27: return "模拟量输入类型错误";
	default:return QString("未知错误码/状态: %1").arg(State);
	}

}
// 将CGXi机器人模式码(6-110)转换为中文描述
QString c_Object::CGXi_Mode(int State)
{
	switch (State)
	{
	case 6:  return "控制器启动完成，本体未上电";
	case 7:  return "本体上电中";
	case 8:  return "本体上电完成";
	case 9:  return "反向驱动状态";
	case 10:  return "本体使能中";
	case 11:  return "本体使能完成";
	case 12:  return "本体断使能中";
	case 100:  return "点动运动中";
	case 101:  return "拖动示教模式";
	case 102:  return "力控测试模式";
	case 103:  return "程序停止";
	case 104:  return "程序暂停";
	case 105: return "程序停止中";
	case 106: return "程序暂停中";
	case 107: return "程序运行，运动停止";
	case 108: return "程序运行，运动减速中";
	case 109: return "程序运行，机械臂指令运动中";
	case 110: return "程序运行，机械臂进入到可交融区域";
	default:return QString("未知模式码: %1").arg(State);
	}
}
// 将CGXi关节模式码(1-12)转换为中文描述
QString c_Object::CGXi_Joint_Mode(int State)
{
	switch (State)
	{
	case 1:  return "断电";
	case 2:  return "关节上电启动";
	case 3:  return "关节上电启动完成，空闲状态";
	case 4:  return "反向驱动状态";
	case 5:  return "关节使能中";
	case 7:  return "关节位置模式静止";
	case 8:  return "关节位置模式运动";
	case 9:  return "关节转矩模式静止";
	case 10:  return "关节转矩模式运动";
	case 11:  return "关节报警";
	case 12:  return "关节断电中";
	default:return QString("未知模式码: %1").arg(State);
	}
}
/*************************************************************************************************************************************************
**Function:非阻塞延时
*************************************************************************************************************************************************/
bool c_Object::msleep(const int mSec)
{
	QEventLoop loop;
	QTimer::singleShot(mSec, &loop, &QEventLoop::quit);
	loop.exec();
	return true;
}
/*************************************************************************************************************************************************
**Function:高低位转浮点型
*************************************************************************************************************************************************/
void c_Object::BitToFloat(float& floatValue, quint16 first16Bits, quint16 second16Bits)
{
	dataConverter unionConverter;
	unionConverter.Word.high16Bits = second16Bits;
	unionConverter.Word.low16Bits = first16Bits;
	// 返回浮点数
	floatValue = unionConverter.floatValue;
}
/*************************************************************************************************************************************************
**Function:高低位转浮点型
*************************************************************************************************************************************************/
void c_Object::FloatToBit(float floatValue, quint16& first16Bits, quint16& second16Bits)
{
	// 使用联合来存储浮点数和其对应的32位整数表示
	dataConverter unionConverter;
	unionConverter.floatValue = floatValue;
	// 提取两个16位值的位信息
	second16Bits = unionConverter.Word.high16Bits;
	first16Bits = unionConverter.Word.low16Bits;
}
/*************************************************************************************************************************************************
**Function:高低位转浮点型
*************************************************************************************************************************************************/
void c_Object::IntToBit(quint32 intValue, quint16& high16Bits, quint16& low16Bits) {
	// 使用位操作将32位整数拆分为两个16位整数
	dataConverter unionConverter;
	unionConverter.DWord = intValue;
	// 提取两个16位值的位信息
	high16Bits = unionConverter.Word.high16Bits;
	low16Bits = unionConverter.Word.low16Bits;
}
// 将两个16位值组合为32位整数(通过union转换)
void c_Object::BitToInt(quint32& intValue, quint16 high16Bits, quint16 low16Bits)
{
	// 使用位操作将32位整数拆分为两个16位整数
	dataConverter unionConverter;
	unionConverter.Word.high16Bits = high16Bits;
	unionConverter.Word.low16Bits = low16Bits;
	intValue = unionConverter.DWord;
}

// Windows/Linux下Ping目标IP一次，检查TTL判断连通性
bool c_Object::QtPing(const QString ip)
{
#ifdef Q_OS_WIN
	QString cmdstr = QString("ping -n 1 -l 1 %1").arg(ip);
#else
	QString cmdstr = QString("ping -s 1 -c 1 %1").arg(ip);
#endif

	QProcess cmd;
	cmd.start(cmdstr);
	cmd.waitForReadyRead(3000);
	cmd.waitForFinished(3000);

	QString res = QString::fromLocal8Bit(cmd.readAll());
	emit Status(res);

	if (res.indexOf("TTL") == -1) {
		return false;
	}
	else {
		return true;
	}
}

/*************************************************************************************************************************************************
**Function:构造函数
*************************************************************************************************************************************************/
QReadWriteLock c_Variable::g_lock;
QScopedPointer<c_Variable> c_Variable::g_instance;

QJsonObject c_Variable::g_Communicate_DB;
QJsonArray c_Variable::g_Worry_List;
QJsonArray c_Variable::g_Work_List;
s_Scan_DB c_Variable::g_Prec_Scan_120;
s_Scan_DB c_Variable::g_Server;
s_Work_DB c_Variable::g_Work_DB;
s_Work_Info c_Variable::g_Work;
s_Magic_DB c_Variable::g_Magic;
s_CGXi_DB c_Variable::g_CGXi;

// 单例构造（私有，仅通过getInstance访问）
c_Variable::c_Variable(QObject * parent) : QObject(parent)
{
	
}

// 单例析构
c_Variable::~c_Variable()
{
	qDebug() << "~c_Variable()";
}

// 双重检查锁定的线程安全单例工厂
c_Variable& c_Variable::getInstance()
{
	if (g_instance.isNull()) {
		g_lock.lockForWrite();
		if (g_instance.isNull()) {
			g_instance.reset(new c_Variable());
		}
		g_lock.unlock();
	}
	return *g_instance.data();
}

