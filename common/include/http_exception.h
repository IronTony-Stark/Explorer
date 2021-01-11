//
// Created by Iron Tony on 17/12/2020.
//

#ifndef EXPLORERCOMMON_HTTP_EXCEPTION_H
#define EXPLORERCOMMON_HTTP_EXCEPTION_H

#include <exception>
#include <string>

class HttpException final : public std::exception {
public:
    HttpException(int statusCode, std::string message, std::string details)
            : mStatusCode(statusCode), mMessage(std::move(message)), mDetails(std::move(details)),
              mWhat(std::to_string(mStatusCode) + " " + mMessage + "\n" + mDetails) {}

    const char* what() const noexcept override {
        return mWhat.c_str();
    }

    const int mStatusCode;
    const std::string mMessage;
    const std::string mDetails;
    const std::string mWhat;
};

#endif //EXPLORERCOMMON_HTTP_EXCEPTION_H
