#include "http_exception.h"
#include "http_request_parser.h"

HttpRequestParser::HttpRequestParser(QString  request)
        : mRequest(std::move(request)) {}

void HttpRequestParser::setRequest(const QString& request) {
    mRequest = request;
}

HttpRequest HttpRequestParser::parse() {
    HttpRequest request;

    QStringList lines = mRequest.split(QRegExp("[\r\n]"));

    parseStartLine(request, lines[0].trimmed());
    int bodyLineIndex = parseHeaders(request, lines);
    parseBody(request, lines, bodyLineIndex);

    return request;
}

void HttpRequestParser::parseStartLine(HttpRequest& request, const QString& startLine) {
    QStringList words = startLine.split(" ");

    if (words.size() < 3)
        throw HttpException(400, "Bad Request", "HTTP Invalid Start Line");

    request.setMethod(getMethodByName(words[0].toStdString()));

    QString version = words[words.size() - 1];
    if (version != "HTTP/1.0" && version != "HTTP/1.1")
        throw HttpException(400, "Bad Request", "Illegal HTTP version: " + version.toStdString());
    request.setVersion(version);

    QString target = words[1];
    for (int i = 2; i < words.size() - 1; ++i)
        target += " " + words[i];
    parseTarget(request, target);
}

void HttpRequestParser::parseTarget(HttpRequest& request, const QString& target) {
    QStringList targetParams = target.split("?");
    if (targetParams.empty())
        throw HttpException(400, "Bad Request", "HTTP Missing Target");
    if (targetParams.size() > 2)
        throw HttpException(400, "Bad Request", "HTTP Target Must Have Only One '?'");
    request.setTarget(targetParams[0]);

    if (targetParams.size() == 2) {
        QStringList params = targetParams[1].split("&");
        for (const auto& param : params) {
            QStringList keyValue = param.split("=");
            if (keyValue.size() != 2)
                throw HttpException(400, "Bad Request", "HTTP Illegal query parameter");
            QString key = keyValue[0];
            QString value = keyValue[1];
            request.addQueryParam(key, value);
        }
    }
}
