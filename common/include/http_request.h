#ifndef EXPLORER_HTTP_REQUEST_H
#define EXPLORER_HTTP_REQUEST_H

#include "http_message.h"

enum Method {
    GET, HEAD, POST, PUT, DELETE, CONNECT, OPTIONS, TRACE, PATCH
};

Method getMethodByName(const std::string&);
const std::string& getMethodName(Method method);

class HttpRequest : public HttpMessage {
public:
    Method getMethod() const;
    QString getTarget() const;
    QMap<QString, QString> getQueryParams() const;

    void setMethod(Method);
    void setTarget(const QString&);
    void addQueryParam(const QString&, const QString&);

    explicit operator std::string() const;

private:
    Method mMethod;
    QString mTarget; // example: '/files'
    QMap<QString, QString> mQueryParams;
};

#endif //EXPLORER_HTTP_REQUEST_H
