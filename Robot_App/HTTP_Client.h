#pragma once
#include "Variable.h"
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QJsonObject>
#include <QTimer>
#include <QVariant>
#include <QList>

class c_HTTP_Client : public QObject
{
	Q_OBJECT
public:
	explicit c_HTTP_Client(QObject *parent = nullptr);
	virtual ~c_HTTP_Client();

	// 响应数据类型（JSON或二进制）
	enum ResponseType { Response_JSON, Response_Raw };

	public slots:
	void Init(); // 子线程初始化
	void Connect_Device(QString ip, quint16 port, QString url);
	void Disconnect_Device();
	void Set_Token(QString token);

	void Send_GET_Request(QString api, QJsonObject params, QJsonObject headers);
	void Send_POST_Request(QString api, QJsonObject body, QJsonObject headers);
	void Send_PUT_Request(QString api, QJsonObject body, QJsonObject headers);
	void Send_DELETE_Request(QString api, QJsonObject params, QJsonObject headers);

	// 发送请求并期望二进制响应（用于图片/文件下载）
	void Send_GET_Raw(QString api, QJsonObject params, QJsonObject headers);

signals:
	void Connect_Done(QString url);
	void Disconnect_Done();
	void Set_Token_Done(QString token);
	void Response_Done(QString api, QJsonObject body);
	void Response_Raw_Done(QString api, QByteArray data);  // 二进制响应
	void Response_Error(QString api, QString error_msg);
	void Status(QString val);
	private slots:
	void Read_Ready(QNetworkReply *reply);

private:
	QNetworkAccessManager *m_Manager;
	QString m_BaseUrl;
	QString m_Token;

	// 进行中的请求列表（用于断开时取消）
	QList<QNetworkReply*> m_PendingReplies;

	// 构建通用请求头（Authorization + 自定义头 + Content-Type）
	QNetworkRequest Prepare_Request(const QUrl &url, const QJsonObject &headers, const char *contentType = nullptr);

	// 超时设置
	void Setup_Timeout(QNetworkReply *reply, int ms = 5000);

	// 发送HTTP请求（内部统一入口）
	QNetworkReply *Send_Request(const QString &api, const QString &httpMethod,
		const QByteArray &body, const QJsonObject &params,
		const QJsonObject &headers, ResponseType respType);
};
