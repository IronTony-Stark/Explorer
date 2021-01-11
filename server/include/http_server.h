#ifndef HTTPDAEMON_H
#define HTTPDAEMON_H

#include <QTcpServer>

#include "filesystem.h"
#include "http_request_parser.h"
#include "http_response.h"

class QTcpSocket;

class HttpServer : public QTcpServer {
Q_OBJECT

public:
    explicit HttpServer(quint16 port, QObject* parent = nullptr);

    void incomingConnection(long long socket) override;

private slots:
    void readFromClient();
    void discardClient();

private:
    QString readMessage(QTcpSocket* socket);
    void writeMessage(QTcpSocket* socket, const QString& message);
    void closeSocket(QTcpSocket* socket);

    QJsonDocument processRequest(const HttpRequest&);
    void processError(HttpResponse& response, int statusCode, const char* message, const char* details);

    FileSystem mFileSystem;
    HttpRequestParser mRequestParser;
};

#endif // HTTPDAEMON_H
