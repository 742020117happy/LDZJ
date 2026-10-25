#pragma execution_character_set("utf-8") 
#include "Robot_App_Widget.h"
#include <QScreen>	// 2026-10-24 T71 修复：QScreen 前向声明不完整，需完整类型（primaryScreen()->geometry()）
#include <QSharedMemory>	// 2026-10-24 T81：单实例守卫
#include <QSystemSemaphore>	// 2026-10-24 T81：单实例检查防并发竞争
#include <QMessageBox>	// 2026-10-24 T81：多开弹窗提醒

int main(int argc, char *argv[])
{
	// 2026-10-24 重构 T22：高分屏适配（须在 QApplication 构造前设置）
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
	QApplication Application(argc, argv);

	// 2026-10-25 日志体系完善（L 系列）：程序启动
	c_Log::Info("APP", "Start", "launch highdpi=true");

	// 2026-10-24 T81：单实例守卫——已运行时误触多开仅弹窗提醒并退出新实例
	// （信号量串行化检查消除双实例同时启动的竞争；Windows 下崩溃后共享内存由系统自动回收）
	QSystemSemaphore instSem("RobotApp_SingleInstance_Sem", 1, QSystemSemaphore::Open);
	instSem.acquire();
	QSharedMemory instMem("RobotApp_SingleInstance_Mem");
	bool alreadyRunning = instMem.attach();
	if (!alreadyRunning) { instMem.create(1); }
	instSem.release();
	if (alreadyRunning) {
		// 2026-10-25 L：多开被拦截（仅日志记录，不改变弹窗行为）
		c_Log::Warn("APP", "SingleInstance", "already_running=true ignored");
		QMessageBox::warning(nullptr, "提示",
			"智能底部巡检机器人控制平台已在运行，请勿重复打开！");
		return 0;
	}

	// 2026-10-24 T71：多分辨率适配（720p/1080p/2K/4K）——按主屏逻辑高度设置基准字号
	// QSS 已去除全局固定字号，基准字号由应用字体决定（pt 值随 HighDPI 缩放）
	{
		QScreen *scr = QGuiApplication::primaryScreen();
		int h = scr ? scr->geometry().height() : 1080;
		int basePt = 9;
		if (h <= 800) { basePt = 8; }          // 720p
		else if (h <= 1100) { basePt = 9; }     // 1080p
		else if (h <= 1500) { basePt = 10; }    // 2K
		else { basePt = 11; }                   // 4K
		QFont baseFont("微软雅黑", basePt);
		Application.setFont(baseFont);
		// 2026-10-25 L：多分辨率适配结果
		c_Log::Info("APP", "Font", QString("screen_height=%1 base_pt=%2").arg(h).arg(basePt));
	}

	c_Robot_App_Widget w;
	int ret = Application.exec();
	// 2026-10-25 L：程序退出
	c_Log::Info("APP", "Exit", QString("code=%1").arg(ret));
	return ret;
}
