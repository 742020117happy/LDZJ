#pragma once
#include <QMutex>
#include "Variable.h"

class c_Sql_Remote : public c_Object
{
	Q_OBJECT
public:
	explicit c_Sql_Remote(QObject *parent = nullptr);	// 构造函数
	virtual ~c_Sql_Remote();							// 析构函数

signals:
	void Connect_Done();	// MySQL连接完成信号

public slots:
	void init();						// 初始化MySQL
	void connectMysql();				// 连接MySQL服务器
	void updateActualReturnTime();		// 更新实际返回时间
	void On_Photo_Completed(QString fname);	// 照片采集完成回调

private:
	MYSQL *m_conn = nullptr;			// MySQL连接句柄
	QMutex *m_Mutex = nullptr;			// 互斥锁
	QList<QString> m_imagePathList;		// 待写入图片路径队列
	bool m_updatingReturnTime = false;	// 是否正在更新返回时间

	void flushCollectTime();		// 刷新采集时间（写入数据库）
	void flushPendingImages();		// 刷新待处理图片队列
};
