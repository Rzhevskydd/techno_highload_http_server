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
    constructPath(doc_root);
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

bool RequestBuilder::constructPath(const std::string & doc_root) {
    size_t query_string_pos = request_.path.find('?');
    if (query_string_pos != std::string::npos) {
        request_.path.resize(query_string_pos);
    }

    if (request_.path.find("../") != std::string::npos) {
        status_ = status::Status_403_Forbidden;
        return false;
    }

    request_.path = doc_root + request_.path;
    if (custom_ends_with(request_.path, "/")) {
        if (custom_ends_with(request_.path, ".html/")) {
            request_.path += NOT_FOUND_STR;

        } else {
            request_.path += "index.html";
        }
    }


    for (size_t url_encode_pos = request_.path.find('%');
            url_encode_pos != std::string::npos;
            url_encode_pos = request_.path.find('%')) {
        std::string_view url_encode = static_cast<std::string_view>(request_.path).substr(url_encode_pos + 1, 2);

        char url_decode = static_cast<char>(std::stoul(url_encode.data(), nullptr, 16));
        if (url_decode == 0) {
            continue;
        }

        request_.path.replace(url_encode_pos, 3, 1, url_decode);
    }

    return true;
}
