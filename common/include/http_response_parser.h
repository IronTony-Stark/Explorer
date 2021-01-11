#ifndef EXPLORER_HTTP_RESPONSE_PARSER_H
#define EXPLORER_HTTP_RESPONSE_PARSER_H

#include "http_response.h"

class HttpResponseParser {
public:
    HttpResponseParser() = default;
    explicit HttpResponseParser(QString);

    void setResponse(const QString&);

    HttpResponse parse();

private:
    void parseStartLine(HttpResponse&, const QString&);

    QString mResponse;
};

#endif //EXPLORER_HTTP_RESPONSE_PARSER_H
