# Qt 5.12.1 模块知识库 — Robot_App 项目

> 生成日期: 2026-07-11 | 基于 Qt 5.15 官方文档 (向下兼容 Qt 5.12)
> 本文档整理 Robot_App 项目所用 Qt 模块的核心知识点、API 参考和项目中的实际使用模式。

---

## 目录

1. [QNetworkAccessManager — HTTP 网络通讯](#1-qnetworkaccessmanager)
2. [QModbusTcpClient — Modbus TCP 现场总线](#2-qmodbustcpclient)
3. [QTimer — 定时器](#3-qtimer)
4. [QThread — 工作线程管理](#4-qthread)
5. [QJsonDocument / QJsonObject — JSON 序列化](#5-qjsondocument--qjsonobject)
6. [QPainter — 2D图形绘制(地图/雷达)](#6-qpainter)
7. [QMetaObject::invokeMethod — 跨线程方法调用](#7-qmetaobjectinvokemethod)
8. [QLabel (scaledContents) — 图像自适应显示](#8-qlabel-scaledcontents)
9. [QNetworkReply — HTTP 响应处理](#9-qnetworkreply)
10. [QTcpSocket — TCP Socket 通信](#10-qtcpsocket)
11. [项目中的线程模型](#11-线程模型)

---

## 1. QNetworkAccessManager

**项目用途**: `HTTP_Client` 类封装，与煜禾森 Magic 底盘 HTTP REST API 通信。

**头文件**: `<QNetworkAccessManager>` | **模块**: `QT += network` | **引入**: Qt 4.4

### 核心概念

```
QNetworkAccessManager(单例/QObject线程亲和)
  ├── get(QNetworkRequest)    → QNetworkReply*  (GET请求)
  ├── post(QNetworkRequest, data) → QNetworkReply*  (POST请求)
  ├── put(QNetworkRequest, data)  → QNetworkReply*  (PUT请求)
  ├── deleteResource(QNetworkRequest) → QNetworkReply* (DELETE请求)
  └── finished(QNetworkReply*) 信号 ← 统一响应入口
```

### 关键特性

| 特性 | 说明 |
|------|------|
| **异步API** | 所有请求非阻塞，通过 `finished` 信号获取响应 |
| **请求排队** | 同一host/port最多6个并行请求(HTTP)，超出排队 |
| **线程亲和** | 只能在创建线程使用，跨线程操作需信号槽 |
| **Reply生命周期** | 用户负责 `deleteLater()`，不可在 `finished` 槽内直接delete |
| **连接池** | 自动管理TCP连接复用 |
| **Content-Type** | 空Body时不应设置，否则某些服务端返回400 |

### 项目使用模式 (HTTP_Client.cpp)

```cpp
// 1. 创建Manager（在Init中，HTTP线程内）
m_Manager = new QNetworkAccessManager;
QObject::connect(m_Manager, &QNetworkAccessManager::finished,
                 this, &c_HTTP_Client::Read_Ready);

// 2. 构建请求头（Prepare_Request统一封装）
QNetworkRequest request(url);
request.setRawHeader("Authorization", "Bearer " + token);
request.setRawHeader("Accept-Encoding", "gzip, deflate");  // 压缩
request.setRawHeader("Connection", "keep-alive");            // 长连接

// 3. 发送请求
QNetworkReply *reply = m_Manager->post(request, postData);
reply->setProperty("api", api);  // 标记API路径用于回调匹配

// 4. 超时保护（5秒）
QTimer::singleShot(5000, reply, [reply]() {
    if (reply->isRunning()) reply->abort();
});

// 5. 响应处理
void Read_Ready(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        emit Response_Error(api, reply->errorString());
    } else {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        emit Response_Done(api, doc.object());
    }
    reply->deleteLater();  // 必须延迟删除
}
```

### 常用错误码

| 错误 | 含义 | 处理 |
|------|------|------|
| `NoError` | 成功 | 正常解析 |
| `OperationCanceledError` | 超时/取消 | 日志"请求超时(5s)" |
| `ConnectionRefusedError` | 连接被拒 | 端口不可达 |
| `HostNotFoundError` | 域名解析失败 | IP地址错误 |

---

## 2. QModbusTcpClient

**项目用途**: `ModeBusTCP_Client` 类封装，与 CGXi 协作机器人通过 Modbus TCP 通信。

**头文件**: `<QModbusTcpClient>` | **模块**: `QT += serialbus` | **引入**: Qt 5.8

### 类继承关系

```
QModbusDevice (基类)
  ├── stateChanged()    设备状态变化信号
  ├── errorOccurred()   设备错误信号
  ├── connectDevice()   发起连接
  ├── disconnectDevice()断开连接
  └── setConnectionParameter() 设置连接参数
      └── QModbusClient (抽象)
          ├── sendReadRequest(QModbusDataUnit, serverAddress)
          ├── sendWriteRequest(QModbusDataUnit, serverAddress)
          ├── setTimeout()  超时ms
          └── setNumberOfRetries() 重试次数
              └── QModbusTcpClient
                  ├── open()  TCP连接
                  └── close() TCP断开
```

### 设备状态机

```
UnconnectedState ─→ ConnectingState ─→ ConnectedState
       ↑                                      │
       └──────────── ClosingState ←───────────┘
```

### QModbusDataUnit — 数据单元

```cpp
// 寄存器类型枚举
QModbusDataUnit::DiscreteInputs   // 离散输入 (功能码02)
QModbusDataUnit::Coils            // 线圈 (功能码01/05/15)
QModbusDataUnit::InputRegisters   // 输入寄存器 (功能码04)
QModbusDataUnit::HoldingRegisters // 保持寄存器 (功能码03/06/16)

// 构造: (寄存器类型, 起始地址, 数量)
QModbusDataUnit unit(QModbusDataUnit::HoldingRegisters, 0, 124);

// 读取: sendReadRequest返回QModbusReply*
auto *reply = m_ModbusDevice->sendReadRequest(unit, 1); // slaveId=1

// 写入: 逐值设置后sendWriteRequest
unit.setValue(i, registerValue);
auto *reply = m_ModbusDevice->sendWriteRequest(unit, 1);
```

### QModbusReply — 异步响应

```cpp
// 检查是否已完成
if (!reply->isFinished()) {
    connect(reply, &QModbusReply::finished, this, &handler);
} else {
    reply->deleteLater();  // 已完成但出错
}

// 获取结果
const QModbusDataUnit result = reply->result();
quint16 startAddr = result.startAddress();
QVector<quint16> values = result.values();  // 注意：返回QVector<quint16>
```

### 项目使用模式 (ModeBusTCP_Client.cpp)

```cpp
// 1. 创建 + 配置
m_ModbusDevice = new QModbusTcpClient;
m_ModbusDevice->setConnectionParameter(NetworkAddressParameter, ip);
m_ModbusDevice->setConnectionParameter(NetworkPortParameter, 502);
m_ModbusDevice->setTimeout(1000);          // 1秒超时
m_ModbusDevice->setNumberOfRetries(2);     // 重试2次

// 2. 连接 (异步)
m_ModbusDevice->connectDevice();
// State_Changed → ConnectedState → emit Connect_Done()

// 3. 分批读取1000个寄存器 (避开Modbus协议125寄存器限制)
// 每批124个，共9批读完
Read_HoldingRegisters(0, 124);      // 第1批: 0-123
Read_HoldingRegisters(124, 124);    // 第2批: 124-247
// ... 共8批
Read_HoldingRegisters(992, 8);      // 最后一批: 992-999

// 4. 读完成回调
void Read_Ready_HoldingRegisters() {
    auto *reply = qobject_cast<QModbusReply*>(sender());
    const QModbusDataUnit unit = reply->result();
    // memcpy到缓存数组 (带越界保护)
    memcpy(m_buffer.read_HoldingRegisters + unit.startAddress(),
           unit.values().data(),
           sizeof(quint16) * unit.valueCount());
    reply->deleteLater();
}
```

### Register 限制说明
- Modbus协议单次读/写上限: **125个寄存器**
- 项目采用 124/批 (留1个余量)
- CGXi控制器还有**通用寄存器区** (1000-1999 uint16, 2000-3999 uint32, 4000-5999 float)，当前未读取

---

## 3. QTimer

**项目用途**: 状态轮询定时器、移动控制持续发送、HTTP超时保护、连接重试。

**头文件**: `<QTimer>` | **模块**: `QT += core` | **所有平台**

### 两种用法

| 方式 | 代码 | 适用场景 |
|------|------|---------|
| **实例化** | `QTimer *t = new QTimer; t->start(200); connect(t, timeout, ...)` | 长期重复定时 |
| **单次** | `QTimer::singleShot(5000, receiver, slot)` | 一次性延迟操作 |

### 精度等级 (Qt::TimerType)

| 类型 | 误差 | 说明 |
|------|------|------|
| `PreciseTimer` | ±1ms | 毫秒精度，CPU唤醒频繁 |
| `CoarseTimer` (默认) | ±5% | 粗精度，节能 |
| `VeryCoarseTimer` | ±500ms | 极粗，仅适合秒级 |

### 关键API — singleShot(receiver版)

```cpp
// 推荐：带receiver保护，receiver销毁后自动取消回调
QTimer::singleShot(5000, reply, [reply]() {
    if (reply->isRunning()) reply->abort();
});

// 不推荐：无receiver保护的functor版，reply销毁后会崩溃
QTimer::singleShot(5000, [reply]() { reply->abort(); });  // ⚠️危险
```

**项目实际使用**: `Setup_Timeout()` 使用 `singleShot(ms, reply, lambda)` 保护模式。

### 项目中的定时器实例

| 定时器 | 间隔 | 线程 | 用途 |
|--------|------|------|------|
| `m_PollTimer` (Magic_Remote) | 200ms | HTTP线程 | 底盘状态轮询 |
| `m_MoveTimer` (Robot_App_Widget) | 80ms | 主线程 | 移动控制持续发送(12.5Hz) |
| `QTimer::singleShot(3000)` (CGXi_Remote) | 3s | Modbus线程 | 断线重连 |
| `QTimer::singleShot(1500)` (Magic_Remote) | 1.5s | HTTP线程 | 地图切换后延迟获取信息 |

### 重要注意事项

- 定时器必须在**目标线程**中启动和停止
- 不能在外部线程操作定时器
- 0ms间隔的定时器会在事件处理完后立即触发

---

## 4. QThread

**项目用途**: Magic 和 CGXi 通讯模块各自运行在独立线程中。

**头文件**: `<QThread>` | **模块**: `QT += core`

### 项目线程架构

```
主线程 (GUI)
  ├── m_Magic_Remote_Thread   → c_Magic_Remote
  │     └── m_HTTP_Thread      → c_HTTP_Client
  │           └── QNetworkAccessManager
  └── m_CGXi_Remote_Thread    → c_CGXi_Remote
        └── m_ModeBusTCP_Thread→ c_ModeBusTCP_Client
              └── QModbusTcpClient
```

### 标准启动模式

```cpp
// 1. 创建对象和工作线程
m_Magic_Remote = new c_Magic_Remote;
m_Magic_Remote_Thread = new QThread;

// 2. 将对象移动到工作线程
m_Magic_Remote->moveToThread(m_Magic_Remote_Thread);

// 3. 绑定生命周期
connect(m_Magic_Remote_Thread, &QThread::started,  m_Magic_Remote, &c_Magic_Remote::Init);
connect(m_Magic_Remote_Thread, &QThread::finished, m_Magic_Remote, &QObject::deleteLater);

// 4. 启动
m_Magic_Remote_Thread->start();
```

### 安全退出模式

```cpp
// 1. 停止内部定时器/标志
m_Scan = false;

// 2. 请求中断 → 退出事件循环 → 等待完成
m_Magic_Remote_Thread->requestInterruption();
m_Magic_Remote_Thread->quit();
m_Magic_Remote_Thread->wait(3000);  // 最多等3秒

// 3. finished信号触发deleteLater自动清理
```

### 关键规则

| 规则 | 说明 |
|------|------|
| **moveToThread** | 对象的所有槽函数在目标线程执行 |
| **QObject::connect** | 跨线程信号槽使用 `Qt::QueuedConnection` (异步) |
| **finished → deleteLater** | 线程结束后自动清理对象 |
| **requestInterruption** | 温和通知，配合 `isInterruptionRequested()` 检查 |

---

## 5. QJsonDocument / QJsonObject

**项目用途**: Magic REST API 的 JSON 请求体和响应解析。

**头文件**: `<QJsonDocument>`, `<QJsonObject>` | **模块**: `QT += core`

### 序列化 (C++ → JSON)

```cpp
// 构造JSON对象
QJsonObject body;
body["userCode"] = "admin";
body["password"] = "admin123";

// 序列化为字节数组
QByteArray postData = QJsonDocument(body).toJson(QJsonDocument::Compact);
// 输出: {"userCode":"admin","password":"admin123"}
```

### 反序列化 (JSON → C++)

```cpp
QByteArray buffer = reply->readAll();
QJsonParseError error;
QJsonDocument doc = QJsonDocument::fromJson(buffer, &error);

if (error.error == QJsonParseError::NoError && doc.isObject()) {
    QJsonObject obj = doc.object();
    QString token = obj["token"].toString();
    bool success = obj["successed"].toBool();

    // 嵌套对象
    QJsonObject data = obj["data"].toObject();
    double x = data["worldPosition"].toObject()["x"].toDouble();

    // 数组
    QJsonArray arr = obj["list"].toArray();
    for (const auto &item : arr) {
        QJsonObject elem = item.toObject();
    }
}
```

### NaN/Infinity 防御

```cpp
// Python后端可能返回 NaN 或 Infinity (特别是激光雷达数据)
// Qt JSON解析器无法处理这些值
if (error.errorString().contains("illegal number")) {
    QByteArray clean = buffer;
    clean.replace("NaN", "null");
    clean.replace("Infinity", "null");
    clean.replace("-Infinity", "null");
    doc = QJsonDocument::fromJson(clean, &error);
}
```

### 常用类型转换

| JSON类型 | C++类型 | 方法 |
|----------|---------|------|
| String | `QString` | `.toString()` |
| Number(int) | `int` | `.toInt()` |
| Number(double) | `double` | `.toDouble()` |
| Boolean | `bool` | `.toBool()` |
| Object | `QJsonObject` | `.toObject()` |
| Array | `QJsonArray` | `.toArray()` |
| null | — | `.isNull()` |

---

## 6. QPainter

**项目用途**: `Magic_Map_View` 地图渲染, `Magic_Lidar_View` 激光雷达渲染。

**头文件**: `<QPainter>` | **模块**: `QT += gui`

### 坐标变换系统

```cpp
// 保存/恢复状态 (入栈/出栈)
painter.save();
  painter.translate(x, y);       // 平移坐标系
  painter.rotate(-angle);        // 旋转 (度, 顺时针为正)
  painter.scale(s, s);           // 缩放
  // ... 在世界坐标下绘制 ...
painter.restore();               // 恢复之前的状态
```

### 绘制API

```cpp
// 线条
painter.setPen(QPen(Qt::black, 2.0));
painter.drawLine(p1, p2);

// 填充路径
QPainterPath path;
path.moveTo(0, 0); path.lineTo(10, 5); path.lineTo(5, 10);
path.closeSubpath();
painter.setBrush(QColor(0, 220, 80, 200));  // RGBA
painter.drawPath(path);

// 图像
QRectF target(-gw/2, -gh/2, gw, gh);
painter.drawImage(target, mapImage);

// 圆点
painter.setBrush(Qt::white);
painter.drawEllipse(center, radius, radius);

// 文本
painter.drawText(pos, QString("(%1,%2)").arg(x).arg(y));

// 圆角矩形 (HUD背景)
painter.setBrush(QColor(0, 0, 0, 160));
painter.drawRoundedRect(QRectF(10,10,200,90), 6, 6);
```

### 渲染提示 (性能/质量平衡)

```cpp
painter.setRenderHint(QPainter::Antialiasing, true);       // 抗锯齿
painter.setRenderHint(QPainter::SmoothPixmapTransform, true); // 平滑缩放
```

---

## 7. QMetaObject::invokeMethod

**项目用途**: 从主线程触发工作线程中的槽函数（跨线程方法调用）。

**头文件**: `<QMetaObject>` | **模块**: `QT += core`

### 标准模式

```cpp
// 跨线程异步调用 (QueuedConnection → 自动排队到目标线程事件循环)
QMetaObject::invokeMethod(m_Magic_Remote,       // 目标对象
    "Robot_Move",                                // 方法名(字符串)
    Qt::QueuedConnection,                        // 连接类型
    Q_ARG(double, linearSpeed),                  // 参数1
    Q_ARG(double, angularSpeed),                 // 参数2
    Q_ARG(double, 0.0));                         // 参数3
```

### 关键规则

| 规则 | 说明 |
|------|------|
| **方法名匹配** | 第一个参数是C字符串方法名，运行时查找 |
| **参数数量** | Q_ARG的数量必须**精确匹配**目标方法参数个数 |
| **默认参数** | invokeMethod **不应用** C++ 默认参数值！必须显式传递所有参数 |
| **QueuedConnection** | 跨线程必须使用，调用不阻塞当前线程 |
| **返回值** | 返回 `bool`：调用成功/失败 |

### 常见错误

```cpp
// ❌ 错误：只传2个参数，但 Robot_Move 有3个参数(第3个有默认值)
QMetaObject::invokeMethod(m_Magic_Remote, "Robot_Move", Qt::QueuedConnection,
    Q_ARG(double, lv), Q_ARG(double, av));

// ✅ 正确：显式传递全部3个参数
QMetaObject::invokeMethod(m_Magic_Remote, "Robot_Move", Qt::QueuedConnection,
    Q_ARG(double, lv), Q_ARG(double, av), Q_ARG(double, 0.0));
```

---

## 8. QLabel (scaledContents)

**项目用途**: 在 `tab_Camera` 中显示前/后相机实时画面。

### 核心属性

```cpp
// .ui文件中设置
<property name="scaledContents"><bool>true</bool></property>
<property name="sizePolicy">
  <sizepolicy hsizetype="Preferred" vsizetype="Fixed"/>
</property>
<property name="maximumSize">
  <size><width>800</width><height>600</height></size>
</property>
```

### scaledContents 工作原理

```
默认 (false): pixmap尺寸 → 决定label尺寸 → label要求layout放大 → 正反馈循环
设为true:     label尺寸(由layout决定) → pixmap按比例缩放填充 → 稳定
```

### 代码刷新模式

```cpp
// ✅ 正确：只setPixmap，Qt自动按label尺寸缩放
if (!r.frontCameraImage.isNull())
    ui->label_FrontCamera->setPixmap(QPixmap::fromImage(r.frontCameraImage));

// ❌ 错误：手动scaled + setPixmap → label→size()一直变大
ui->label->setPixmap(pixmap.scaled(ui->label->size()));  // 正反馈！
```

### 必备配套属性

| 属性 | 作用 |
|------|------|
| `scaledContents=true` | pixmap缩放适配label尺寸 |
| `sizePolicy(Fixed)` | 垂直方向不随内容变化 |
| `maximumSize` | 硬限制最大尺寸（双重保险） |

---

## 9. QNetworkReply

**项目用途**: `QNetworkAccessManager` 返回的响应对象。

### 关键操作

```cpp
// 检查错误
if (reply->error() == QNetworkReply::NoError) { ... }

// 读取响应体
QByteArray buffer = reply->readAll();

// 检查是否还在传输中 (超时取消使用)
if (reply->isRunning()) reply->abort();

// 附加自定义属性 (用于回调中识别请求)
reply->setProperty("api", "/cmd/robot_move");
QString api = reply->property("api").toString();

// 生命周期管理
reply->deleteLater();  // 延迟删除，绝不可在槽函数中delete
```

### 常用错误码

| 错误 | 说明 |
|------|------|
| `NoError` | 成功 |
| `ConnectionRefusedError` | 服务端未运行/端口错误 |
| `RemoteHostClosedError` | 服务端断开连接 |
| `HostNotFoundError` | DNS解析失败 |
| `TimeoutError` | 连接超时 |
| `OperationCanceledError` | 手动abort()或singleShot超时取消 |
| `ContentNotFoundError` | HTTP 404 |
| `AuthenticationRequiredError` | HTTP 401 (未授权) |

---

## 10. QTcpSocket

**项目用途**: `Robot_Client` / `Robot_Server` — 通用TCP JSON通讯和精扫UDP通讯。

**头文件**: `<QTcpSocket>`, `<QUdpSocket>` | **模块**: `QT += network`

### TCP Client模式 (Robot_Client.cpp)

```cpp
QTcpSocket *m_Socket = new QTcpSocket;
m_Socket->connectToHost(ip, port);  // 异步连接

connect(m_Socket, &QTcpSocket::readyRead, this, &handler);
connect(m_Socket, &QAbstractSocket::stateChanged, this, &stateHandler);

// 发送JSON
QByteArray data = QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
m_Socket->write(data);

// 接收 (需处理TCP分包：以分隔符/长度前缀界定消息边界)
QByteArray buffer = m_Socket->readAll();
```

### UDP Client模式 (Scan_Client.cpp)

```cpp
QUdpSocket *m_Socket = new QUdpSocket;
m_Socket->bind(port);  // 绑定到本地端口
m_Socket->writeDatagram(data, QHostAddress(ip), port);  // 发送
// 接收: readyRead → readDatagram()
```

---

## 11. 线程模型

### 完整架构图

```
┌──────────────────────────────────────────────────────────────────┐
│  主线程 (GUI + QApplication::exec)                                │
│  ├── System_Scan() 10ms定时器 → Magic_Scan() + CGXi_Scan()       │
│  ├── Move_Timer_Tick() 80ms → invokeMethod(m_Magic_Remote)        │
│  └── UI事件处理 (按钮点击 → invokeMethod → 工作线程)              │
├──────────────────────────────────────────────────────────────────┤
│  m_Magic_Remote_Thread (底盘业务线程)                              │
│  └── c_Magic_Remote                                               │
│      ├── Poll_Status() 200ms定时器                                │
│      │   ├── On_Response_Done() 响应解析                          │
│      │   └── emit Update_Magic_DB() → 主线程刷新UI                │
│      └── m_HTTP_Thread (HTTP网络线程)                              │
│          └── c_HTTP_Client                                        │
│              ├── QNetworkAccessManager                            │
│              ├── Send_GET/POST/PUT/DELETE                         │
│              └── Read_Ready() 响应回调                             │
├──────────────────────────────────────────────────────────────────┤
│  m_CGXi_Remote_Thread (机械臂业务线程)                             │
│  └── c_CGXi_Remote                                               │
│      ├── 状态机: 读→写→读循环                                     │
│      ├── 读124寄存器/批 × 8批 + 余8个 = 1000寄存器             │
│      └── m_ModeBusTCP_Thread (Modbus TCP线程)                     │
│          └── c_ModeBusTCP_Client                                  │
│              ├── QModbusTcpClient                                │
│              ├── sendReadRequest / sendWriteRequest               │
│              └── Read_Ready_HoldingRegisters() 回调               │
└──────────────────────────────────────────────────────────────────┘
```

### 跨线程通信汇总

| 方向 | 机制 | 示例 |
|------|------|------|
| 主线程→工作线程 | `QMetaObject::invokeMethod` + QueuedConnection | 按钮点击 → Robot_Move |
| 工作线程→主线程 | signal/slot (Qt自动QueuedConnection) | Update_Magic_DB → 刷新UI |
| 跨工作线程 | 通过主线程中转 + signal/slot | Status → Write_Magic_List |

### 线程安全数据

| 数据 | 保护方式 | 访问线程 |
|------|---------|---------|
| `g_Magic` (s_Magic_DB) | 写线程唯一(HTTP线程写, 主线程只读) | HTTP + Main |
| `g_CGXi` (s_CGXi_DB) | 写线程唯一(Modbus线程写, 主线程只读) | Modbus + Main |
| `g_Communicate_DB` | 读多写少，JSON Object | Main |
| `m_buffer` (s_ModBus_DB) | 私有成员，信号传递结构体副本 | Modbus |

---

## 附录：模块依赖清单 (Debug|x64)

```
QT += core gui network sql serialbus widgets printsupport charts websockets concurrent
```

| 模块 | 主要类 | 项目使用 |
|------|--------|---------|
| `core` | QTimer, QThread, QJsonDocument, QMetaObject | 基础架构 |
| `gui` | QPainter, QImage, QPixmap | 地图/雷达/相机 |
| `network` | QNetworkAccessManager, QTcpSocket, QUdpSocket | Magic HTTP, TCP通讯 |
| `serialbus` | QModbusTcpClient, QModbusDataUnit | CGXi Modbus |
| `widgets` | QMainWindow, QLabel, QPushButton, QTabWidget | UI框架 |
| `charts` | QPolarChart, QScatterSeries | 数据可视化 |
| `websockets` | QWebSocket | WebSocket通讯 |
| `sql` | MySQL driver | 数据库 |
