#ifndef EXPLORER_HTTP_REQUEST_PARSER_H
#define EXPLORER_HTTP_REQUEST_PARSER_H

#include "http_request.h"

class HttpRequestParser {
public:
    HttpRequestParser() = default;
    explicit HttpRequestParser(QString  request);

    void setRequest(const QString& request);

    HttpRequest parse();

private:
    void parseStartLine(HttpRequest&, const QString&);
    void parseTarget(HttpRequest&, const QString&);

    QString mRequest;
};

#endif //EXPLORER_HTTP_REQUEST_PARSER_H
