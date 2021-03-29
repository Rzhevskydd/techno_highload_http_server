#ifndef HTTP_STATIC_SERVER_REQUEST_H
#define HTTP_STATIC_SERVER_REQUEST_H

#include "common.h"

struct Request {
    std::string_view version;
    method::Type method;
    std::string path;
};

std::pair<Request, status::Type> build_http_request(std::string_view&& request_raw, const std::string& doc_root);

class RequestBuilder {
public:
    RequestBuilder() = default;
    std::pair<Request, status::Type> operator()(std::string_view&& request_raw, const std::string& doc_root);
private:
    std::string_view request_raw_;
    Request request_;
    status::Type status_ = status::Status_200_OK;

    void getHTTPMethod();
    bool checkMethod();
    void getPath();
    bool checkPath(const std::string_view & document_sv_root);
    void getVersion();
    bool checkVersion();
};


#endif //HTTP_STATIC_SERVER_REQUEST_H
