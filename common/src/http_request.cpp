#include <unordered_map>

#include "http_exception.h"
#include "http_request.h"

static const std::unordered_map<std::string, Method> kMethodNames = {
        {"GET",     GET},
        {"HEAD",    HEAD},
        {"POST",    POST},
        {"PUT",     PUT},
        {"DELETE",  DELETE},
        {"CONNECT", CONNECT},
        {"OPTIONS", OPTIONS},
        {"TRACE",   TRACE},
        {"PATCH",   PATCH},
};

Method HttpRequest::getMethod() const {
    return mMethod;
}

QString HttpRequest::getTarget() const {
    return mTarget;
}

QMap<QString, QString> HttpRequest::getQueryParams() const {
    return mQueryParams;
}

void HttpRequest::setMethod(Method method) {
    mMethod = method;
}

void HttpRequest::setTarget(const QString& target) {
    mTarget = target;
}

void HttpRequest::addQueryParam(const QString& param, const QString& value) {
    mQueryParams.insert(param, value);
}

HttpRequest::operator std::string() const {
    std::string request;

    request += getMethodName(mMethod) + " " + mTarget.toStdString();

    if (!mQueryParams.isEmpty())
        request += "?";
    for (auto it = mQueryParams.begin(); it != mQueryParams.end(); ++it) {
        if (it != mQueryParams.begin())
            request += "&";
        request += it.key().toStdString() + "=" + it.value().toStdString();
    }

    request += " " + mHttpVersion.toStdString() + "\n";

    const HttpMessage& message = *this;
    std::string messageStr = static_cast<std::string>(message);
    request += messageStr;

    return request;
}

Method getMethodByName(const std::string& name) {
    auto it = kMethodNames.find(name);
    if (it != kMethodNames.end())
        return it->second;
    else
        throw HttpException(400, "Bad Request", "HTTP Unknown Method");
}

const std::string& getMethodName(Method method) {
    for (const auto& methodName : kMethodNames)
        if (methodName.second == method)
            return methodName.first;

    throw HttpException(500, "Internal Server Error", "HTTP Method Name Not Found");
}

