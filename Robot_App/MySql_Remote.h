#pragma once
#include <QMutex>
#include "Variable.h"

class c_Sql_Remote : public c_Object
{
	Q_OBJECT
public:
	explicit c_Sql_Remote(QObject *parent = nullptr);
	virtual ~c_Sql_Remote();

signals:
	void Connect_Done();

public slots:
	void init();
	void connectMysql();
	void updateActualReturnTime();
	void On_Photo_Completed(QString fname);

private:
	MYSQL *m_conn = nullptr;
	QMutex *m_Mutex = nullptr;
	QList<QString> m_imagePathList;
	bool m_updatingReturnTime = false;

	void flushCollectTime();
	void flushPendingImages();
};
