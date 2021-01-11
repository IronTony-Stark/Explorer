#include "http_exception.h"
#include "http_message.h"

QString HttpMessage::getVersion() const {
    return mHttpVersion;
}

QMap<QString, QString> HttpMessage::getHeaders() const {
    return mHeaders;
}

QJsonDocument HttpMessage::getBody() const {
    return mBody;
}

void HttpMessage::setVersion(const QString& version) {
    mHttpVersion = version;
}

void HttpMessage::addHeader(const QString& header, const QString& value) {
    mHeaders.insert(header, value);
}

void HttpMessage::setBody(const QJsonDocument& body) {
    mBody = body;
}

HttpMessage::operator std::string() const {
    std::string message;

    for (auto it = mHeaders.begin(); it != mHeaders.end(); ++it)
        message += it.key().toStdString() + ":" + it.value().toStdString() + "\n";

    message += "\n";

    message += mBody.toJson(QJsonDocument::Compact).toStdString();

    return message;
}

int parseHeaders(HttpMessage& message, const QStringList& lines) {
    int i = 1;
    while (i < lines.size()) {
        if (lines[i].isEmpty())
            return ++i;

        QStringList headerValue = lines[i].split(":");
        if (headerValue.size() != 2)
            throw HttpException(400, "Bad Request", "HTTP Invalid Headers");

        QString header = headerValue[0].trimmed();
        QString value = headerValue[1].trimmed();

        if (header.isEmpty() || value.isEmpty())
            throw HttpException(400, "Bad Request", "HTTP Invalid Headers");

        message.addHeader(header, value);
        ++i;
    }

    throw HttpException(400, "Bad Request", "HTTP Empty Line Not Found");
}

void parseBody(HttpMessage& message, const QStringList& lines, int index) {
    QString body;
    for (int i = index; i < lines.size(); ++i) {
        if (i != index)
            body += "\n";
        body += lines[i];
    }

    if (body.isEmpty()) {
        message.setBody(QJsonDocument());
        return;
    }

    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(body.toUtf8(), &jsonError);
    if (QJsonParseError::NoError != jsonError.error)
        throw HttpException(400, "Bad Request", "HTTP Body Must Be a Valid Json");
    else
        message.setBody(doc);
}
