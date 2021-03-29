#include "Request.h"

std::pair<Request, status::Type> build_http_request(std::string_view&& request_raw, const std::string &doc_root) {
    RequestBuilder builder;
    return builder(std::move(request_raw), doc_root);
}

std::pair<Request, status::Type>
RequestBuilder::operator()(std::string_view &&request_raw, const std::string &doc_root) {
    request_raw_ = request_raw;

    getHTTPMethod();
    getPath();
    getVersion();

//    CheckMethod() && CheckPath(doc_root_sv) && CheckVersion();
    return std::make_pair(request_, status_);
}

void RequestBuilder::getHTTPMethod() {
    size_t pos = request_raw_.find(" /");

    request_.method = request_raw_.substr(0, pos);
    request_raw_.remove_prefix(pos + 1);
}

void RequestBuilder::getPath() {
    size_t pos = request_raw_.find(" HTTP/");

    request_.path = request_raw_.substr(0, pos);
    request_raw_.remove_prefix(pos + 1);
}

void RequestBuilder::getVersion() {
    size_t pos = request_raw_.find(End_Of_Line);

    request_.version = request_raw_.substr(0, pos);
    request_raw_.remove_prefix(pos);
}
