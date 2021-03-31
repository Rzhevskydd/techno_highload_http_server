#ifndef HTTP_STATIC_SERVER_RESPONSE_H
#define HTTP_STATIC_SERVER_RESPONSE_H

#include <sstream>
#include <string_view>


#include "Request.h"

std::string build_http_response(const Request & request, status::Type& status);

class ResponseBuilder {
public:
    ResponseBuilder() = default;
    std::string operator()(const Request & request, status::Type& status);
private:
    std::ostringstream sstream_;
    void checkFileAvailable(const std::string& file_path, status::Type & status);
    void writeHeader(const Request& request, status::Type& status);
};


#endif //HTTP_STATIC_SERVER_RESPONSE_H
