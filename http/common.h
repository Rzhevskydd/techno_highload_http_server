#ifndef HTTP_STATIC_SERVER_COMMON_H
#define HTTP_STATIC_SERVER_COMMON_H

#include <string>

#define NOT_FOUND_STR "NOT_FOUND"

bool custom_ends_with(const std::string_view& str, const std::string& suffix);

namespace method {
    using Type = std::string_view;
    constexpr Type Method_HEAD = "HEAD";
    constexpr Type Method_GET = "GET";
}

namespace status {
    using Type = std::string_view;
    constexpr Type Status_200_OK = "200 OK";
    constexpr Type Status_400_Bad_Request = "400 Bad Request";
    constexpr Type Status_403_Forbidden = "403 Forbidden";
    constexpr Type Status_404_Not_Found = "404 Not Found";
    constexpr Type Status_405_Not_Allowed = "405 Method Not Allowed";
}
namespace mime_type {
    using Type = std::string_view;
    constexpr Type Mime_Type_PNG = "image/png";
    constexpr Type Mime_Type_JPG = "image/jpeg";
    constexpr Type Mime_Type_TIFF = "image/tiff";
    constexpr Type Mime_Type_HTML = "text/html";
    constexpr Type Mime_Type_PLAIN = "text/plain";
    constexpr Type Mime_Type_CSS = "text/css";
    constexpr Type Mime_Type_GIF = "image/gif";
    constexpr Type Mime_Type_BMP = "image/bmp";
    constexpr Type Mime_Type_JS = "application/javascript";
    constexpr Type Mime_Type_SWF = "application/x-shockwave-flash";
    Type GetContentType(const std::string_view &file_path);

}
constexpr std::string_view End_Of_Line = "\r\n";


#endif //HTTP_STATIC_SERVER_COMMON_H
