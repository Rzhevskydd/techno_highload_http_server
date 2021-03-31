#include "common.h"
#include <string>

bool custom_ends_with(const std::string_view& str, const std::string& suffix) {
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

mime_type::Type mime_type::GetContentType(const std::string_view & file_path) {
    if (custom_ends_with(file_path, "html") || custom_ends_with(file_path,"htm")) {
        return mime_type::Mime_Type_HTML;
    }
    else if (custom_ends_with(file_path,"css")) {
        return mime_type::Mime_Type_CSS;
    }
    else if (custom_ends_with(file_path,"gif")) {
        return mime_type::Mime_Type_GIF;
    }
    else if (custom_ends_with(file_path,"png")) {
        return mime_type::Mime_Type_PNG;
    }
    else if (custom_ends_with(file_path,"jpg") || custom_ends_with(file_path,"jpe") || custom_ends_with(file_path,"jpeg")) {
        return mime_type::Mime_Type_JPG;
    }
    else if (custom_ends_with(file_path,"tiff") || custom_ends_with(file_path,"tif")) {
        return mime_type::Mime_Type_TIFF;
    }
    else if (custom_ends_with(file_path,"bmp")) {
        return mime_type::Mime_Type_BMP;
    }
    else if (custom_ends_with(file_path,"js")) {
        return mime_type::Mime_Type_JS;
    }
    else if (custom_ends_with(file_path,"swf")) {
        return mime_type::Mime_Type_SWF;
    }
    return mime_type::Mime_Type_PLAIN;
}
