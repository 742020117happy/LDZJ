#pragma once
#include <QMap>
#include <QDir>
#include <QFile>
#include <QTimer>
#include <QWidget>
#include <QObject>
#include <QThread>
#include <QVector>
#include <QImage>
#include <QColor>
#include <QPainter>
#include <QVariant>
#include <QDateTime>
#include <QKeyEvent>
#include <QJsonValue>
#include <QByteArray>
#include <QJsonArray>
#include <QStringList>
#include <QEventLoop>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QMainWindow>
#include <QJsonObject>
#include <QMessageBox>
#include <QPainterPath>
#include <QHostAddress>
#include <QApplication>
#include <QJsonDocument>
#include <QAbstractSocket>
#include <QModbusDataUnit>
#include <QModbusTcpClient>
#include <QNetworkInterface>
#include <QtNetwork>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QScopedPointer>
#include <QMetaType>
#include <QSharedMemory>
#include <QProcess>
#include <QMutex>
#include <QReadWriteLock>
#include <QSocketNotifier>
#include <QTextStream>
#include <QIODevice>

#include <mysql.h>

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <SDKDDKVer.h>
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include <io.h>
#include <process.h>

#include "robotapi.h"     // 包含 CGXi SDK 接口
#include "basestruct.h"   // 包含 CGXi SDK 数据结构

#pragma pack(push, 1) 
struct s_CGXi_Date {
	// ================= 0-99: 基础与IO状态 =================
	char version[6];                      // 0-2: 控制器版本 (3 reg)
	quint16 reserved1[7];                 // 3-9: 保留 (7 reg)

	quint16 standard_digital_input;       // 10: 标准数字输入
	quint16 standard_digital_output;      // 11: 标准数字输出
	quint16 standard_digital_output_set_mask;    // 12: 标准DO置1掩码
	quint16 standard_digital_output_clear_mask;  // 13: 标准DO置0掩码
	quint16 configurable_digital_input;   // 14: 可配置数字输入
	quint16 configurable_digital_output;  // 15: 可配置数字输出
	quint16 configurable_digital_output_set_mask;   // 16: 可配置DO置1掩码
	quint16 configurable_digital_output_clear_mask; // 17: 可配置DO置0掩码

	quint16 analog_input_0;               // 18: 模拟量输入0
	quint16 analog_input_0_type;          // 19: 模拟量输入0类型
	quint16 analog_input_1;               // 20: 模拟量输入1
	quint16 analog_input_1_type;          // 21: 模拟量输入1类型
	quint16 analog_input_2;               // 22: 模拟量输入2
	quint16 analog_input_2_type;          // 23: 模拟量输入2类型
	quint16 analog_output_0;              // 24: 模拟量输出0
	quint16 analog_output_0_type;         // 25: 模拟量输出0类型
	quint16 tool_standard_digital_input;  // 26: 工具端标准数字输入
	quint16 tool_standard_digital_output; // 27: 工具端标准数字输出
	quint16 reserved2[2];                 // 28-29: 保留

										  // ================= 30-99: 编码器、RTC与系统状态 =================
	qint64 encoder_0_count;               // 30-33: 编码器0计数值 (4 reg)
	qint64 encoder_1_count;               // 34-37: 编码器1计数值 (4 reg)
	quint16 reserved3[12];                // 38-49: 保留

	quint16 rtc_second;                   // 50: RTC秒
	quint16 rtc_minute;                   // 51: RTC分
	quint16 rtc_hour;                     // 52: RTC时
	quint16 rtc_day;                      // 53: RTC日
	quint16 rtc_month;                    // 54: RTC月
	quint16 rtc_year;                     // 55: RTC年
	quint16 rtc_week;                     // 56: RTC周
	quint16 reserved4[3];                 // 57-59: 保留

	quint16 robot_mode;                   // 60: 机械臂模式
	quint16 program_status;               // 61: 程序状态
	quint16 robot_power_on_indicator;     // 62: 上电指示
	quint16 clear_robot_error;            // 63: 清除错误
	quint16 clear_robot_warning;          // 64: 清除警告
	quint16 robot_error_indicator;        // 65: 错误指示
	quint16 robot_warning_indicator;      // 66: 警告指示
	quint16 robot_moving;                 // 67: 运动中
	quint16 robot_drag_teaching;          // 68: 拖动示教中
	quint16 power_button_pressed;         // 69: 电源按钮按下
	quint16 reserved5[10];                // 70-79: 保留

	quint16 last_error_code;              // 80: 最近错误码
	quint16 reserved6[4];                 // 81-84: 保留
	quint16 last_warning_code;            // 85: 最近警告码
	quint16 manual_auto_indicator;        // 86: 手自动指示
	qint16 current_program_index;         // 87: 当前程序索引
	qint16 target_program_index;          // 88: 目标程序索引
	quint16 target_program_operation;     // 89: 目标程序操作
	quint16 reserved7[10];                // 90-99: 保留

										  // ================= 100-199: 通讯参数 =================
	quint16 controller_ip[4];             // 100-103: IP地址
	quint16 controller_mask[4];           // 104-107: 子网掩码
	quint16 reserved8[92];                // 108-199: 保留

										  // ================= 200-499: 关节信息 =================
	quint16 joint_mode[6];                // 200-205: 关节1-6模式
	quint16 reserved10[4];                // 206-209: 保留
	qint16 joint_temperature[6];          // 210-215: 关节1-6温度
	quint16 reserved11[4];                // 216-219: 保留

										  // 【核心映射】文档明确“低16位在前，高16位在后”，完美契合小端CPU的float内存布局
	float joint_actual_position[6];       // 220-231: 关节实际位置
	quint16 reserved12[8];                // 232-239: 保留
	float joint_target_position[6];       // 240-251: 关节目标位置
	quint16 reserved13[8];                // 252-259: 保留
	float joint_actual_speed[6];          // 260-271: 关节实际速度
	quint16 reserved14[8];                // 272-279: 保留
	float joint_target_speed[6];          // 280-291: 关节目标速度
	quint16 reserved15[8];                // 292-299: 保留
	float joint_actual_acceleration[6];   // 300-311: 关节实际加速度
	quint16 reserved16[8];                // 312-319: 保留
	float joint_target_acceleration[6];   // 320-331: 关节目标加速度
	quint16 reserved17[8];                // 332-339: 保留
	float joint_actual_torque[6];         // 340-351: 关节实际转矩
	quint16 reserved18[8];                // 352-359: 保留
	float joint_target_torque[6];         // 360-371: 关节目标转矩
	quint16 reserved19[128];              // 372-499: 保留

										  // ================= 500-799: TCP信息 =================
	float tcp_actual_position[6];         // 500-511: TCP实际位置
	quint16 reserved20[8];                // 512-519: 保留
	float tcp_target_position[6];         // 520-531: TCP目标位置
	quint16 reserved21[8];                // 532-539: 保留
	float tcp_actual_speed[6];            // 540-551: TCP实际速度
	quint16 reserved22[8];                // 552-559: 保留
	float tcp_target_speed[6];            // 560-571: TCP目标速度
	quint16 reserved23[8];                // 572-579: 保留
	float tcp_actual_force[6];            // 580-591: TCP实际力
	quint16 reserved24[8];                // 592-599: 保留
	float tcp_target_force[6];            // 600-611: TCP目标力
	quint16 reserved25[88];               // 612-699: 保留

	float tcp_flange_offset[6];           // 700-711: TCP法兰偏移
	quint16 reserved26[8];                // 712-719: 保留
	float payload_mass_and_cog[4];        // 720-727: 负载mass和质心
	quint16 reserved27[2];                // 728-729: 保留
	float speed_ratio;                    // 730-731: 运动速度比例 
	quint16 reserved28[68];               // 732-799: 保留

										  // ================= 800-999: 运动控制 =================
	quint16 jog_type;                     // 800: 点动类型
	float jog_speed_ratio;                // 801-802: 点动速度比例
	quint16 jog_coordinate_system;        // 803: 点动坐标系
	quint16 reserved29[6];                // 804-809: 保留
	float jog_target_position[6];         // 810-821: 点动目标位置
	quint16 reserved30[28];               // 822-849: 保留

	quint32 total_motion_time;            // 850-851: 运动总时间
	quint32 last_motion_time;             // 852-853: 最近一次运动时间
	float total_power;                    // 854-855: 本体总功率
	float total_energy;                   // 856-857: 本体总功耗
	float mechanical_power;               // 858-859: 机械功率
	float mechanical_energy;              // 860-861: 机械功耗
	float momentum;                       // 862-863: 动量
	quint16 reserved31[136];              // 864-999: 保留
};
#pragma pack(pop) // 恢复默认对齐

struct s_CGXi_DB {
	// 注意：g_CGXi 由Modbus线程写入(memcpy)，主线程只读(CGXi_Scan)。
	// 1000寄存器经单次memcpy整体更新，主线程可能读到半次更新的数据。
	// 用于UI刷新可接受，如需严格一致性改用双缓冲或读写锁。
	bool Connected = false;
	bool Ready = false;
	int FPS = 0;

	// 使用匿名联合体，数组和结构体共享内存
	union {
		quint16 read_HoldingRegisters[1000]; // 原有数组，保持兼容
		s_CGXi_Date data;                    // 解析后的结构体
	};

	union {
		quint16 write_HoldingRegisters[1000]; // 原有数组，保持兼容
		s_CGXi_Date Transfer;                    // 解析后的结构体
	};
};
struct s_Scan_DB {
	bool Remote_Connected = false; // 精扫发送状态
	bool Monitor_Connected = false; // 精扫接收状态
	bool Tran_Connected = false; // 精扫转发状态
	bool Tran_Listen = false;//精扫监听
	int num = 0;
};
// ==================== 轮对质检工作状态 ====================
struct s_Work_DB {
	// ===== WEB 下发的巡检任务数组 (2026-07-16 协商版) =====
	QJsonArray tasks;              // 完整 tasks[] 数组 (每元素含独立 taskId/wheelsetNo/axleNo/wheelsetPosition)
	int     taskCount = 0;         // 任务总数 (tasks.length)

	// ===== 当前执行任务的数据 (从 tasks[currentTaskIndex] 载入) =====
	QString taskId;                // 当前任务标识
	QString carType;               // 车型 (CR400BF, 2026-10-24 新增, 轨迹表查表键)
	QString wheelsetKind;          // 轮对类型 (GBD动车/T3C拖车, 2026-10-24 新增)
	QString mapPointName;          // 巡检地图名称 (2026-10-24 新增, wait_SwitchMap 参数)
	QStringList positions;         // 完整巡检点位序列 (2026-10-24 新增: P0充电/P001初始/P1~P6工位)
	QString axleType;              // 轴型 (RD3A/RD4)
	QString wheelsetNo;            // 轮对号
	QString axleNo;                // 车轴号
	QString sendUnit;              // 送轮单位
	QString startTime;             // 开始时间 (yyyymmddHHMM)
	QString repairLevel;           // 修程 (三级修)

	// ===== 当前执行进度 =====
	int currentTaskIndex = 0;      // 当前任务索引 (0-based, 对应 tasks[])
	int currentPos = 0;            // 当前工位索引 (0-based)
	int currentPoint = 0;          // 当前采集点序号

	// ===== 当前CGXi传来的采集参数 =====
	int currentGain = 0;
	int currentProg = 0;
	QString currentPart1;
	QString currentPart2;
	QString currentPointStr;

	// ===== 总体状态 =====
	int workState = 0;             // 0:空闲 1:就绪 2:采集中 3:暂停 4:完成 5:错误
	int errorCode = 0;
	int totalImages = 0;
};
// ==================== WEB 任务基本信息 ====================
struct s_Work_Info {
	bool Connected = false;       // 任务是否激活
};
// ==================== Magic 写入数据（UI→底盘） ====================
struct Magic_WriteData {
	// ---------- 连接认证 ----------
	QString ip = "192.168.1.102";	// 2026-10-24 T60：出厂默认 IP（实际以 Communicate_DB Magic_IP 为准）
	quint16 port = 8888;
	QString userCode = "admin";
	QString password = "admin123";

	// ---------- 定点导航 ----------
	double fixedNavX = 0;
	double fixedNavY = 0;
	double fixedNavAngle = 0;

	// ---------- 系统配置 ----------
	double maxSpeedGoal = 0.5;      // 自由导航最大速度 (m/s)
	double maxSpeedGraph = 0.2;     // 手绘路径最大速度
	double maxSpeedRecord = 0.5;    // 录制路径最大速度
	bool avoidGraph = true;         // 手绘路径避障
	bool avoidRecord = true;        // 录制路径避障
	bool lidarVoid = true;          // 窄道启用雷达

									// ---------- 任务参数 ----------
	int loopCount = 1;
	bool loopEnable = false;
	int taskTypeIndex = 0;          // 0:导航点, 1:手绘路径, 2:录制路径, 3:路径组合
	QString taskName;               // 当前选中的任务名称

									// ---------- 移动控制 ----------
	double linearSpeed = 0.2;
	double angularSpeed = 0.0;
	int moveMode = 1;               // 1:定距离, 2:定角度
	double moveTarget = 1.0;

	// ---------- 充电 ----------
	QString chargePointName = "charge_point";

	// ---------- 地图操作 ----------
	QString newMapName;             // 新建/重命名地图名称
	QString selectedMapName;        // 当前选中地图名称（下拉框）

									// ---------- 创建导航点 ----------
	QString newPointName;
	int newPointType = 2;           // 0:初始, 1:充电, 2:导航
	bool markCurrentPos = true;
};
// ==================== Magic 读取数据（底盘→UI） ====================
struct Magic_ReadData {
	// ---------- 实时位姿 ----------
	double worldX = 0.0;
	double worldY = 0.0;
	double angle = 0.0;
	int gridX = 0;
	int gridY = 0;
	bool localized = false;

	// ---------- 实时速度 ----------
	double currentLinearSpeed = 0.0;
	double currentAngularSpeed = 0.0;

	// ---------- 硬件状态 ----------
	int battery = 0;
	int chargeStatus = 0;          // 0:未充电, 1:充电中, 2:前往, 3:失败, 4:成功
	bool charging = false;
	int antiCollision = 0;         // 0:无, 1:前, 2:后, 3:前后
	bool emergencyStop = false;
	int workingMode = 1;           // 1:空闲, 2:建图, 3:导航启动, 4:执行中
	int errorCode = 0;

	// ---------- 传感器 ----------
	bool lidarOnline = false;
	bool imuOnline = false;
	bool odomOnline = false;
	bool cameraOnline = false;

	// ---------- IMU数据 ----------
	double imuAngVelX = 0.0;
	double imuAngVelY = 0.0;
	double imuAngVelZ = 0.0;
	double imuLinAccX = 0.0;
	double imuLinAccY = 0.0;
	double imuLinAccZ = 0.0;

	// ---------- 里程计速度 ----------
	double odomLinearX = 0.0;
	double odomLinearY = 0.0;
	double odomLinearZ = 0.0;
	double odomAngularX = 0.0;
	double odomAngularY = 0.0;
	double odomAngularZ = 0.0;

	// ---------- 超声波 ----------
	double ultrasonicFL = 0;
	double ultrasonicFR = 0;
	double ultrasonicRL = 0;
	double ultrasonicRR = 0;
	double ultrasonicLF = 0;
	double ultrasonicLR = 0;
	double ultrasonicRF = 0;
	double ultrasonicRR2 = 0;

	// ---------- GPS ----------
	double gpsLatitude = 0.0;
	double gpsLongitude = 0.0;
	double gpsAltitude = 0.0;

	// ---------- 系统版本/MAC ----------
	QString chassisVersion;
	QString navigationVersion;
	QString sysMac;
	QString sysTitle;

	// ---------- 地图数据 ----------
	QString currentMap;
	QStringList mapList;
	bool mapLoaded = false;
	QImage mapImage;
	double resolution = 0.05;
	double originX = 0.0;
	double originY = 0.0;
	int gridWidth = 0;
	int gridHeight = 0;
	bool mapping = false;

	// ---------- 列表数据 ----------
	QList<QJsonObject> navPoints;
	QList<QJsonObject> graphPaths;
	QList<QJsonObject> recordPaths;
	QList<QJsonObject> taskQueues;

	// ---------- 任务状态 ----------
	int taskStatus = 0;            // 0:空闲, 1:运行, 2:暂停
	double taskProgress = 0.0;
	int taskLoopCount = 0;
	int taskLoopTimes = 0;
	int taskRemainSec = 0;

	// ---------- 相机图像 ----------
	QImage frontCameraImage;      // 前相机彩色图像
	QImage rearCameraImage;       // 后相机彩色图像
	QImage frontDepthImage;       // 前相机深度图像
	QImage rearDepthImage;        // 后相机深度图像
	int frontFrameSeq = 0;        // 2026-10-25 HH2：前相机帧序号（帧率统计）
	int rearFrameSeq  = 0;        // 2026-10-25 HH2：后相机帧序号（帧率统计）

	// ---------- 雷达与路径 ----------
	QVector<QPointF> laserScanPoints;    // 2D激光扫描点（世界坐标）
	QVector<QPointF> laserGridPoints;    // 2D激光栅格化点
	QVector<QPointF> localPlanPath;      // 局部规划路径（世界坐标）
	QVector<QPointF> localGridPlanPath;  // 全局规划路径（栅格坐标）
};
// ==================== 全局 Magic 数据库 ====================
// 注意：g_Magic 由HTTP线程写入(On_Response_Done 整函数持 QWriteLocker)，主线程只读。
// 2026-10-25 QQ2：读侧已全量持 QReadLocker 快照（Widget 3 lambda/状态机合并快照/按钮 T98/
// 视图 T52/Server Build_System_Status 合并快照/Work MM1）——原"无锁设计"注释作废。
struct s_Magic_DB {
	bool is_connected = false;
	QString token = "";
	bool Ready = false;            // 心跳翻转
	QString refreshToken = "";     // 刷新Token（用于Token自动续期）

	Magic_WriteData WriteData;
	Magic_ReadData  ReadData;
};

struct s_IO_DB {
	bool Connected = false;
	bool Ready = false;
	int FPS = 0;
	quint16 Coils[1000] = {0};                 // 数据缓存区间
	quint16 DiscreteInputs[1000] = {0};         // 数据缓存区间
	quint16 InputRegisters[1000] = {0};         // 数据缓存区间
	quint16 read_HoldingRegisters[1000] = {0};  // 数据缓存区间
	quint16 write_HoldingRegisters[1000] = {0}; // 数据缓存区间
};

// ==================== 报警码定义（2026-10-25 EE5：报警码-语音-三色灯映射） ====================
// 级别 2（红）：A01-A06；级别 1（黄）：A11-A21；事件播报：E01-E09
// 完整映射表见 轮对质检/报警码-语音-三色灯映射表.md
namespace AlarmCode {
	static const char *A01_ESTOP        = "A01";	// 急停 → PA020
	static const char *A02_DISCONNECT   = "A02";	// 通信断连 → PA007
	static const char *A03_ROBOT_ERROR  = "A03";	// 机械臂错误 → PA003
	static const char *A04_TASK_FAILED  = "A04";	// 任务失败 → PA003
	static const char *A05_CAMERA_FAULT = "A05";	// 精扫相机故障 → PA021
	static const char *A11_LOW_BATTERY  = "A11";	// 电量低 → PA004
	static const char *A12_LOST_LOCAL   = "A12";	// 定位丢失 → PA022
	static const char *A13_CHARGE_FAULT = "A13";	// 充电故障 → PA008（设备录音）
	static const char *A14_OBSTACLE     = "A14";	// 障碍物 → PA002
	static const char *A15_CHASSIS_WARN = "A15";	// 底盘警告 → PA009
	static const char *A16_PAUSED       = "A16";	// 暂停 → PA005
	static const char *A17_INSPECTING   = "A17";	// 巡检运行中 → PA001
	static const char *A18_ARM_MOVING   = "A18";	// 机械臂运行中 → PA006
}

struct s_Voice_DB {
	bool is_connected = false;     // Modbus RTU 连接状态
	bool Ready = false;            // 在线标志（最近一次命令收到合法应答）
	int Volume = 10;               // 当前音量 0-28（5低/10中/20高）
	int PlayIndex = 0;             // 正在播放的音频索引（0=空闲/停止）
	int PlayCount = 0;             // 累计播报次数（UI 显示）
	int DeviceStatus = 0;          // 设备状态 0-空闲 1-播放中 2-错误
	int ServerAddress = 1;         // Modbus 从站地址
	QString ComPort = "COM1";      // 串口号
	int BaudRate = 9600;           // 波特率
};


class c_Object : public QObject
{
	Q_OBJECT
public:
	explicit c_Object(QObject *parent = nullptr);
	virtual ~c_Object();
	// 使用联合以便在 float quint16 和 quint32 之间进行类型转换
	union dataConverter {
		float floatValue;     // 浮点数
		quint32 DWord;
		struct {
			quint16 low16Bits;
			quint16 high16Bits;
		}Word;
	};

signals:
	void Status(QString state);

	public slots:
	void BitToFloat(float& floatValue, quint16 first16Bits, quint16 second16Bits);
	void FloatToBit(float floatValue, quint16& first16Bits, quint16& second16Bits);
	void IntToBit(quint32 intValue, quint16& high16Bits, quint16& low16Bits);
	void BitToInt(quint32& intValue, quint16 high16Bits, quint16 low16Bits);
	QString TCP_Status(int State);
	QString Modbus_Status(int State);
	QString CGXi_Status(int State);
	QString CGXi_Mode(int State);
	QString CGXi_Joint_Mode(int State);
	bool QtPing(const QString ip);
	bool msleep(const int mSec);
};
// 2026-10-24 重构 T31：统一软件操作日志中心——聚合所有模块操作记录到单一按天文件，线程安全
// 2026-10-25 日志体系完善（L 系列）：新增等级/事件/格式/脱敏/限流（只记录不控制，兼容旧接口）
class c_Log {
public:
	// 等级枚举：LV_ 前缀避免与 Windows.h 宏（ERROR/DEBUG 等）冲突；文本名见 Level_Name
	enum Level { LV_DEBUG = 0, LV_INFO, LV_WARN, LV_ERROR, LV_FATAL };

	// 写一条操作日志（新格式：[时间][等级][模块][事件] 键值对；Append 模式，按天滚动，写失败静默）
	static void Write(Level lv, const QString &module, const QString &event, const QString &msg);
	// 旧接口兼容：等价 Write(INFO, 模块名映射新标识, "General", msg)
	static void Write(const QString &module, const QString &msg);
	// 便捷接口
	static void Debug(const QString &module, const QString &event, const QString &msg);
	static void Info (const QString &module, const QString &event, const QString &msg);
	static void Warn (const QString &module, const QString &event, const QString &msg);
	static void Error(const QString &module, const QString &event, const QString &msg);
	static void Fatal(const QString &module, const QString &event, const QString &msg);
	// 等级名与阈值
	static const char *Level_Name(Level lv);
	static void Set_Log_Level(Level lv);		/* 文件日志过滤阈值（默认 DEBUG 全量） */
	// 敏感信息脱敏：<=8 字符全掩 ********；>8 字符 前4+****
	static QString Mask(const QString &secret);
	// 高频限流：同一 key 每 perMs 毫秒最多放行一次（线程安全）
	static bool Rate_Limit(const QString &key, int perMs = 1000);
private:
	static QString Module_Alias(const QString &module);	/* 旧中文模块名 → 新标识 */
	static QMutex s_Mutex;
	static Level s_MinLevel;									/* 文件过滤阈值 */
	static QHash<QString, qint64> s_RateMap;					/* 限流时间戳表 */
	// 2026-10-24 T80：日志总量治理——>500MB 自动清理至 100MB（旧→新删除，保留当天）
	static qint64 s_LastCheckMs;									/* 检查节流时间戳 */
	static const qint64 CHECK_INTERVAL_MS = 60000;					/* 每 60s 检查一次 */
	static const qint64 MAX_TOTAL_BYTES = 500LL * 1024 * 1024;		/* 总量阈值 500MB */
	static const qint64 KEEP_BYTES = 100LL * 1024 * 1024;			/* 清理目标 100MB */
	static void Cleanup_If_Needed();								/* 调用方须持有 s_Mutex */
};
class c_Variable : public QObject
{
	Q_OBJECT
public:
	static c_Variable& getInstance();
	//成员变量
	static QJsonObject g_Communicate_DB;
	static QJsonArray g_Worry_List;
	static QJsonArray g_Work_List;
	static s_Scan_DB g_Prec_Scan_120;
	static s_Scan_DB g_Server;
	static s_Work_DB g_Work_DB;
	static s_Work_Info g_Work;
	static s_Magic_DB g_Magic;
	static s_IO_DB g_IO;
	static s_Voice_DB g_Voice;
	static s_CGXi_DB g_CGXi;
	static QReadWriteLock g_lock;       // 跨线程数据保护（主线程读/工作线程写）
private:
	explicit c_Variable(QObject * parent = nullptr);
	virtual ~c_Variable();

	// 禁止复制
	c_Variable(const c_Variable &other) = delete;
	c_Variable& operator=(const c_Variable &other) = delete;

	static QScopedPointer<c_Variable> g_instance;
	friend struct QScopedPointerDeleter<c_Variable>;
};


