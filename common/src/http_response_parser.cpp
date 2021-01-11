#include "http_exception.h"
#include "http_response_parser.h"

HttpResponseParser::HttpResponseParser(QString  response)
    : mResponse(std::move(response)) {}

void HttpResponseParser::setResponse(const QString& response) {
    mResponse = response;
}

HttpResponse HttpResponseParser::parse() {
    HttpResponse response;

    QStringList lines = mResponse.split(QRegExp("[\r\n]"));

    parseStartLine(response, lines[0].trimmed());
    int bodyLineIndex = parseHeaders(response, lines);
    parseBody(response, lines, bodyLineIndex);

    return response;
}

void HttpResponseParser::parseStartLine(HttpResponse& response, const QString& startLine) {
    QStringList words = startLine.split(" ");

    if (words.size() < 3)
        throw HttpException(400, "Bad Request", "HTTP Invalid Start Line");

    QString version = words[0];
    if (version != "HTTP/1.0" && version != "HTTP/1.1")
        throw HttpException(400, "Bad Request", "Illegal HTTP version: " + version.toStdString());
    response.setVersion(version);

    int statusCode = words[1].toInt();
    if (statusCode < 100 || statusCode > 599)
        throw HttpException(400, "Bad Request", "HTTP Illegal Status Code");
    response.setStatusCode(statusCode);

    QString statusStr;
    for (int i = 2; i < words.size(); ++i)
        statusStr += words[i];

    response.setStatusCodeStr(statusStr);
}
