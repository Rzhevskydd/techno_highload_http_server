#include <filesystem>
#include <string_view>

#include "Response.h"

std::string ResponseBuilder::operator()(const Request &request, status::Type &status) {
    checkFileAvailable(request.path, status);
    writeHeader(request, status);

    return sstream_.str();
}

void ResponseBuilder::checkFileAvailable(const std::string &file_path, status::Type &status) {
    if (status == status::Status_200_OK && !std::filesystem::exists(file_path)) {
        if (custom_ends_with(file_path, NOT_FOUND_STR)) {
            status = status::Status_404_Not_Found;
            return;
        }

        if (custom_ends_with(file_path, "index.html")) {
            status = status::Status_403_Forbidden;
        } else {
            status = status::Status_404_Not_Found;
        }
    }
}

void ResponseBuilder::writeHeader(const Request &request, status::Type &status) {
    sstream_ << request.version << ' ' << status << End_Of_Line
             << "Server: http_static_server" << End_Of_Line
             << "Date: " << __DATE__ << ' ' << __TIME__ << End_Of_Line
             << "Connection: Close" << End_Of_Line;

    if (status == status::Status_200_OK) {
        sstream_ << "Content-Length: " << std::filesystem::file_size(request.path) << End_Of_Line
                 << "Content-Type: " << mime_type::GetContentType(request.path) << End_Of_Line;
    }
    sstream_ << End_Of_Line;
}

std::string build_http_response(const Request &request, status::Type &status) {
    ResponseBuilder builder;
    return builder(request, status);
}
