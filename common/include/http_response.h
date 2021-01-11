#ifndef EXPLORER_HTTP_RESPONSE_H
#define EXPLORER_HTTP_RESPONSE_H

#include "http_message.h"

class HttpResponse : public HttpMessage {
public:
    int getStatusCode() const;
    QString getStatusCodeStr() const;

    void setStatusCode(int);
    void setStatusCodeStr(const QString&);

    explicit operator std::string() const;

private:
    int mStatusCode; // example: 200
    QString mStatusCodeStr; // example: 'OK'
};

#endif //EXPLORER_HTTP_RESPONSE_H
