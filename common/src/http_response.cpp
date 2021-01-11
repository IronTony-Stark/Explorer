#include "http_response.h"

int HttpResponse::getStatusCode() const {
    return mStatusCode;
}

QString HttpResponse::getStatusCodeStr() const {
    return mStatusCodeStr;
}

void HttpResponse::setStatusCode(int statusCode) {
    mStatusCode = statusCode;
}

void HttpResponse::setStatusCodeStr(const QString& statusCodeStr) {
    mStatusCodeStr = statusCodeStr;
}

HttpResponse::operator std::string() const {
    std::string response;

    response += mHttpVersion.toStdString() + " " +
                std::to_string(mStatusCode) + " " +
                mStatusCodeStr.toStdString() + "\n";

    const HttpMessage& message = *this;
    std::string messageStr = static_cast<std::string>(message);
    response += messageStr;

    return response;
}
