#pragma execution_character_set("utf-8") // 解决Windows MSVC下中文字符串乱码
/**
 * @file    HTTP_Client.cpp
 * @brief   Magic底盘HTTP REST API底层通讯客户端
 * @details 基于QNetworkAccessManager封装GET/POST/PUT/DELETE四种HTTP方法。
 *          所有请求统一通过Prepare_Request构建请求头(Authorization+自定义头+Content-Type)。
 *          响应分JSON和二进制两种类型，支持Base64图像、文件下载等非JSON场景。
 *          请求5秒超时，断连时自动取消所有进行中请求。
 */
#include "HTTP_Client.h"
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QVariant>

// ================= 生命周期管理 =================
c_HTTP_Client::c_HTTP_Client(QObject *parent) : QObject(parent) {}

// 析构：断开设备连接，释放网络管理器
c_HTTP_Client::~c_HTTP_Client() {
	c_HTTP_Client::Disconnect_Device();
	if (m_Manager) m_Manager->deleteLater();
}

// 初始化：创建QNetworkAccessManager并绑定finished信号
void c_HTTP_Client::Init() {
	m_Manager = new QNetworkAccessManager;
	m_Token = "";
	QObject::connect(m_Manager, &QNetworkAccessManager::finished, this, &c_HTTP_Client::Read_Ready);
}

// 构建HTTP服务端URL: http://ip:port/url
void c_HTTP_Client::Connect_Device(QString ip, quint16 port, QString url) {
	QString cleanUrl = url.endsWith("/") ? url.chopped(1) : url;
	m_BaseUrl = QString("http://%1:%2/%3").arg(ip).arg(port).arg(cleanUrl);
	emit Connect_Done(m_BaseUrl);
}

// 断开连接：取消所有进行中请求，清空URL和Token
void c_HTTP_Client::Disconnect_Device() {
	// 取消所有进行中的请求，防止断开后仍有回调触发
	for (QNetworkReply *reply : m_PendingReplies) {
		if (reply && reply->isRunning()) {
			reply->abort();
		}
	}
	m_PendingReplies.clear();
	m_BaseUrl = "";
	m_Token = "";
	emit Disconnect_Done();
}

// 存储Bearer认证Token并通知上层
void c_HTTP_Client::Set_Token(QString token) {
	m_Token = token;
	emit Set_Token_Done(m_Token);
}

// ================= 通用请求构建 =================
// 统一构建QNetworkRequest：设置Authorization头、自定义头、压缩支持和Content-Type
QNetworkRequest c_HTTP_Client::Prepare_Request(const QUrl &url, const QJsonObject &headers, const char *contentType) {
	QNetworkRequest request(url);

	// Bearer Token认证
	if (!m_Token.isEmpty()) {
		request.setRawHeader("Authorization", QString("Bearer %1").arg(m_Token).toUtf8());
	}

	// 启用HTTP压缩，减少大响应(图片/激光数据)的网络传输量
	request.setRawHeader("Accept-Encoding", "gzip, deflate");

	// 长连接复用，减少TCP握手开销
	request.setRawHeader("Connection", "keep-alive");

	// 自定义请求头
	for (auto it = headers.begin(); it != headers.end(); ++it) {
		request.setRawHeader(it.key().toUtf8(), it.value().toString().toUtf8());
	}

	// JSON Content-Type
	if (contentType) {
		request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(contentType));
	}

	return request;
}

// 通用超时设置：使用QTimer::singleShot(receiver, lambda)避免每次new QTimer对象
void c_HTTP_Client::Setup_Timeout(QNetworkReply *reply, int ms) {
	QTimer::singleShot(ms, reply, [reply]() {
		if (reply->isRunning()) reply->abort();
	});
}

// ================= 内部统一请求入口 =================
QNetworkReply *c_HTTP_Client::Send_Request(const QString &api, const QString &httpMethod,
	const QByteArray &body, const QJsonObject &params,
	const QJsonObject &headers, ResponseType respType)
{
	if (!m_Manager) {
		emit Response_Error(api, "未连接服务器");
		return nullptr;
	}

	// 拼接完整URL（基础URL + API路径）
	QString fullUrl = m_BaseUrl + api;

	// 附加Query参数
	if (!params.isEmpty()) {
		QUrl url(fullUrl);
		QUrlQuery query;
		for (auto it = params.begin(); it != params.end(); ++it) {
			query.addQueryItem(it.key(), it.value().toVariant().toString());
		}
		url.setQuery(query);
		fullUrl = url.toString();
	}

	QUrl reqUrl(fullUrl);
	QNetworkRequest request = Prepare_Request(reqUrl, headers,
		body.isEmpty() ? nullptr : "application/json");

	// 根据HTTP方法发送请求
	QNetworkReply *reply = nullptr;
	if (httpMethod == "GET") {
		reply = m_Manager->get(request);
	}
	else if (httpMethod == "POST") {
		reply = m_Manager->post(request, body);
	}
	else if (httpMethod == "PUT") {
		reply = m_Manager->put(request, body);
	}
	else if (httpMethod == "DELETE") {
		reply = m_Manager->deleteResource(request);
	}

	if (reply) {
		reply->setProperty("api", api);
		reply->setProperty("respType", (int)respType);  // 标记响应类型
		m_PendingReplies.append(reply);
		Setup_Timeout(reply);
	}

	return reply;
}

// =====================================================================
// ================= 1. GET 请求 =======================================
// =====================================================================
void c_HTTP_Client::Send_GET_Request(QString api, QJsonObject params, QJsonObject headers) {
	Send_Request(api, "GET", QByteArray(), params, headers, Response_JSON);
}

// GET请求期望二进制响应（用于图片/文件下载）
void c_HTTP_Client::Send_GET_Raw(QString api, QJsonObject params, QJsonObject headers) {
	Send_Request(api, "GET", QByteArray(), params, headers, Response_Raw);
}

// =====================================================================
// ================= 2. POST 请求 ======================================
// =====================================================================
void c_HTTP_Client::Send_POST_Request(QString api, QJsonObject body, QJsonObject headers) {
	// 如果body为空则不发送Content-Type，防止后端对无Body的POST校验报400
	QByteArray postData;
	if (!body.isEmpty()) {
		postData = QJsonDocument(body).toJson(QJsonDocument::Compact);
	}
	emit Status("c_HTTP_Client::Send_POST_Request:" + m_BaseUrl + api);
	Send_Request(api, "POST", postData, QJsonObject(), headers, Response_JSON);
}

// =====================================================================
// ================= 3. PUT 请求 =======================================
// =====================================================================
void c_HTTP_Client::Send_PUT_Request(QString api, QJsonObject body, QJsonObject headers) {
	QByteArray putData;
	if (!body.isEmpty()) {
		putData = QJsonDocument(body).toJson(QJsonDocument::Compact);
	}
	Send_Request(api, "PUT", putData, QJsonObject(), headers, Response_JSON);
}

// =====================================================================
// ================= 4. DELETE 请求 ====================================
// =====================================================================
void c_HTTP_Client::Send_DELETE_Request(QString api, QJsonObject params, QJsonObject headers) {
	Send_Request(api, "DELETE", QByteArray(), params, headers, Response_JSON);
}

// =====================================================================
// ================= 响应接收与解析 ====================================
// =====================================================================
void c_HTTP_Client::Read_Ready(QNetworkReply *reply) {
	if (!reply) return;
	QString api = reply->property("api").toString();
	int respType = reply->property("respType").toInt();

	// 从进行中列表移除（无论成功还是失败）
	m_PendingReplies.removeAll(reply);

	if (reply->error() != QNetworkReply::NoError) {
		QString errMsg = reply->errorString();
		if (reply->error() == QNetworkReply::OperationCanceledError)
			errMsg = "请求超时或已取消 (5s)";
		emit Response_Error(api, errMsg);
		reply->deleteLater();
		return;
	}

	QByteArray buffer = reply->readAll();
	reply->deleteLater();
	if (buffer.isEmpty()) return;

	// 二进制响应：直接返回原始数据（图片/文件下载场景）
	if (respType == Response_Raw) {
		emit Response_Raw_Done(api, buffer);
		return;
	}

	// JSON响应：解析为QJsonObject
	QJsonParseError jsonError;
	QJsonDocument doc = QJsonDocument::fromJson(buffer, &jsonError);

	// 延迟清洗策略：仅在首次解析因NaN/Infinity失败时替换重试
	// 保护Base64图像数据不被篡改
	if (jsonError.error != QJsonParseError::NoError) {
		if (jsonError.errorString().contains("illegal number")) {
			QByteArray cleanBuffer = buffer;
			cleanBuffer.replace("NaN", "null");
			cleanBuffer.replace("Infinity", "null");
			cleanBuffer.replace("-Infinity", "null");
			doc = QJsonDocument::fromJson(cleanBuffer, &jsonError);
		}
	}

	if (jsonError.error != QJsonParseError::NoError || !doc.isObject()) {
		emit Response_Error(api, "JSON解析失败: " + jsonError.errorString());
		return;
	}

	emit Response_Done(api, doc.object());
}
