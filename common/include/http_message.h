#ifndef EXPLORER_HTTP_MESSAGE_H
#define EXPLORER_HTTP_MESSAGE_H

#include <QString>
#include <QMap>
#include <QJsonDocument>

class HttpMessage {
public:
    QString getVersion() const;
    QMap<QString, QString> getHeaders() const;
    QJsonDocument getBody() const;

    void setVersion(const QString& version);
    void addHeader(const QString& header, const QString& value);
    void setBody(const QJsonDocument&);

    explicit operator std::string() const;

protected:
    QString mHttpVersion; // example: 'HTTP/1.1'
    QMap<QString, QString> mHeaders;
    QJsonDocument mBody;
};

int parseHeaders(HttpMessage& message, const QStringList& lines);
void parseBody(HttpMessage& message, const QStringList& lines, int index);

#endif //EXPLORER_HTTP_MESSAGE_H
