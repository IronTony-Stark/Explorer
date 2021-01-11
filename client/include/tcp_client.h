//
// Created by Iron Tony on 18/12/2020.
//

#ifndef EXPLORERSERVER_TCP_CLIENT_H
#define EXPLORERSERVER_TCP_CLIENT_H

#include <QTcpSocket>
#include <QObject>
#include <QQueue>
#include <QVector>
#include <http_response_parser.h>
#include <http_request.h>

#include "file_list/file.h"
#include "busy_indicator.h"
#include "error_text.h"
#include "file_tree/dir.h"

class TcpClient : public QObject {
Q_OBJECT

    enum class State {
        IDLE, GET_FILES, GET_ROOT_DIRS, GET_DIRS
    };

public:
    TcpClient(QString host, int port, BusyIndicator&, ErrorText&);
    ~TcpClient() override;

    void getRootFiles();
    void getFilesByPath(const QString& path);

    void getRootDirs();
    void getDirsByPath(const QString& path);

signals:
    void filesReceived(const QString&, const QVector<File>&);
    void dirsReceived(const QVector<Dir>&);
    void rootDirsReceived(const QVector<Dir>&);

private slots:
    void onReadyRead();
    void onError(QAbstractSocket::SocketError socketError);

private:
    void connectSocket(const QString& host, int port);
    void disconnectSocket();

    QString read();
    void write(const QString& message);
    void sendRequest(const HttpRequest& request);

    void processResponseBody(const QJsonObject&);

    QTcpSocket* mSocket;
    HttpResponseParser mResponseParser;

    State mState = State::IDLE;

    BusyIndicator& mBusyIndicator;
    ErrorText& mErrorText;

    QString mHost;
    int mPort;
};

#endif //EXPLORERSERVER_TCP_CLIENT_H
