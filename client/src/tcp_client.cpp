//
// Created by Iron Tony on 18/12/2020.
//

#include <QJsonObject>
#include <QJsonArray>
#include <http_request.h>
#include <file_tree/dir.h>

#include "file_list/file.h"
#include "tcp_client.h"

TcpClient::TcpClient(QString host, int port, BusyIndicator& busyIndicator, ErrorText& errorText)
        : mSocket(new QTcpSocket(this)), mBusyIndicator(busyIndicator),
          mErrorText(errorText), mHost(std::move(host)), mPort(port) {}

TcpClient::~TcpClient() {
    disconnectSocket();
}

void TcpClient::getRootFiles() {
    HttpRequest request;
    request.setVersion("HTTP/1.1");
    request.setMethod(GET);
    request.setTarget("/files/root");
    mState = State::GET_FILES;
    sendRequest(request);
}

void TcpClient::getFilesByPath(const QString& path) {
    HttpRequest request;
    request.setVersion("HTTP/1.1");
    request.setMethod(GET);
    request.setTarget("/files");
    request.addQueryParam("path", path);
    mState = State::GET_FILES;
    sendRequest(request);
}

void TcpClient::getRootDirs() {
    HttpRequest request;
    request.setVersion("HTTP/1.1");
    request.setMethod(GET);
    request.setTarget("/dirs/root");
    mState = State::GET_ROOT_DIRS;
    sendRequest(request);
}

void TcpClient::getDirsByPath(const QString& path) {
    HttpRequest request;
    request.setVersion("HTTP/1.1");
    request.setMethod(GET);
    request.setTarget("/dirs");
    request.addQueryParam("path", path);
    mState = State::GET_DIRS;
    sendRequest(request);
}

void TcpClient::onReadyRead() {
    QString data = read();
    if (data.isEmpty())
        return;
    mResponseParser.setResponse(data);
    HttpResponse response = mResponseParser.parse();
    if (response.getStatusCode() != 200) {
        QString reason = response.getBody().object().value("reason").toString();
        mErrorText.setError(reason);
    } else {
        processResponseBody(response.getBody().object());
    }

    mBusyIndicator.stop();
}

void TcpClient::onError(QAbstractSocket::SocketError socketError) {
    if (socketError != QAbstractSocket::RemoteHostClosedError)
        mErrorText.setError(mSocket->errorString());
}

void TcpClient::connectSocket(const QString& host, int port) {
    qInfo() << "Connect" << host << port;
    mSocket->connectToHost(host, port);
    connect(mSocket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
    connect(mSocket, &QTcpSocket::errorOccurred, this, &TcpClient::onError);
}

void TcpClient::disconnectSocket() {
    qInfo() << "Disconnect";
    mSocket->abort();
    disconnect(mSocket, &QTcpSocket::readyRead, nullptr, nullptr);
    disconnect(mSocket, &QTcpSocket::errorOccurred, nullptr, nullptr);
}

QString TcpClient::read() {
    QString response = mSocket->readAll();
    qInfo() << "Response\n" << response.toStdString().c_str();
    return response;
}

void TcpClient::write(const QString& message) {
    qInfo() << "Request\n" << message.toStdString().c_str();
    mSocket->write(message.toUtf8());
}

void TcpClient::sendRequest(const HttpRequest& request) {
    mBusyIndicator.run();

    if (mSocket->state() == QAbstractSocket::UnconnectedState)
        connectSocket(mHost, mPort);

    std::string requestStr = static_cast<std::string>(request);
    write(requestStr.c_str());
}

void TcpClient::processResponseBody(const QJsonObject& body) {
    if (mState == State::GET_FILES) {
        QString directory = body.value("directory").toString();

        QVector<File> files;
        QJsonArray array = body.value("files").toArray();

        for (const auto& element : array)
            files.append(File::fromJson(element.toObject()));

        emit filesReceived(directory, files);
    } else if (mState == State::GET_ROOT_DIRS || mState == State::GET_DIRS) {
        QVector<Dir> dirs;
        QJsonArray array = body.value("dirs").toArray();

        for (const auto& element : array)
            dirs.append(Dir::fromJson(element.toObject()));

        if (mState == State::GET_ROOT_DIRS) {
            emit rootDirsReceived(dirs);
        } else {
            emit dirsReceived(dirs);
        }
    } else {
        qCritical() << "Invalid state while processing response body";
    }

    mState = State::IDLE;
}
