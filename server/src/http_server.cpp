#include <QJsonObject>
#include <QTcpSocket>
#include <http_exception.h>

#include "http_server.h"

HttpServer::HttpServer(quint16 port, QObject* parent) :
        QTcpServer(parent) {
    listen(QHostAddress::Any, port);
}

void HttpServer::incomingConnection(long long socket) {
    auto* tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readFromClient()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(discardClient()));
    tcpSocket->setSocketDescriptor(socket);
    qInfo() << "Incoming Connection" << tcpSocket;
}

void HttpServer::readFromClient() {
    auto* socket = dynamic_cast<QTcpSocket*>(sender());

    if (socket == nullptr) {
        qCritical() << "Invalid Socket Sender. Expected TCP";
        return;
    }

    QString request = readMessage(socket);

    mRequestParser.setRequest(request);
    HttpResponse httpResponse;
    httpResponse.setVersion("HTTP/1.1");
    try {
        HttpRequest httpRequest = mRequestParser.parse();
        QJsonDocument body = processRequest(httpRequest);
        httpResponse.setStatusCode(200);
        httpResponse.setStatusCodeStr("OK");
        httpResponse.setBody(body);
    } catch (const HttpException& httpException) {
        processError(httpResponse, httpException.mStatusCode,
                     httpException.mMessage.c_str(), httpException.mDetails.c_str());
    } catch (const std::exception& exc) {
        const char* what = exc.what();
        qCritical() << what;

        processError(httpResponse, 500, "Internal Server Error", what);
    }

    std::string response = static_cast<std::string>(httpResponse);

    writeMessage(socket, QString(response.c_str()));

    closeSocket(socket);
}

void HttpServer::discardClient() {
    auto* socket = dynamic_cast<QTcpSocket*>(sender());

    if (socket == nullptr) {
        qCritical() << "Invalid Socket Sender. Expected TCP";
        return;
    }

    qInfo() << "Discard Client" << socket;
    socket->deleteLater();
}

QString HttpServer::readMessage(QTcpSocket* socket) {
    QString message = socket->readAll();
    qInfo() << "Request" << socket << "\n" << message.toStdString().data();
    return message;
}

void HttpServer::writeMessage(QTcpSocket* socket, const QString& message) {
    qInfo() << "Response" << socket << "\n" << message.toStdString().data();
    socket->write(message.toUtf8());
}

void HttpServer::closeSocket(QTcpSocket* socket) {
    qInfo() << "Close Socket" << socket;
    socket->close();

    if (socket->state() == QTcpSocket::UnconnectedState)
        delete socket;
}

QJsonDocument HttpServer::processRequest(const HttpRequest& httpRequest) {
    if (httpRequest.getMethod() != Method::GET)
        throw HttpException(400, "Bad Request", "Server can only process GET requests");

    QString target = httpRequest.getTarget();
    QMap<QString, QString> params = httpRequest.getQueryParams();

    if (target == "/files/root" && params.isEmpty())
        return mFileSystem.getRootFiles();
    else if (target == "/files" && params.contains("path"))
        return mFileSystem.getFilesByPath(params.value("path"));
    else if (target == "/dirs/root" && params.isEmpty())
        return mFileSystem.getRootDirs();
    else if (target == "/dirs" && params.contains("path"))
        return mFileSystem.getDirsByPath(params.value("path"));

    throw HttpException(400, "Bad Request", "Invalid target or/and query params");
}

void HttpServer::processError(HttpResponse& response, int statusCode, const char* message, const char* details) {
    QJsonDocument body;
    QJsonObject json;
    json.insert("reason", details);
    body.setObject(json);

    response.setStatusCode(statusCode);
    response.setStatusCodeStr(message);
    response.setBody(body);
}
