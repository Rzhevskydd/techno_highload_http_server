#include <iostream>
#include <fstream>
#include <map>
#include <filesystem>
#include "server/Server.h"

struct Config {
    std::string host;
    size_t port;
    size_t threads_limit;
    size_t maxConnections;
    std::string document_root;
};

Config ParseConfig(const std::string& path) {
    Config config{};
//    std::ifstream file("httpd.conf");
//    std::string line;
//    int pos;

    std::map<std::string, std::string> config_map;

    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("invalid path: " + path);
    }

    for (std::string line; std::getline(file, line);) {
        auto pos = line.find(' ');
        if (pos == std::string::npos) {
            throw std::runtime_error("invalid config format, need : <key> <value>");
        }
        config_map.emplace(line.substr(0, pos), line.substr(pos + 1, line.find(' ', pos + 1)));
    }

    auto it = config_map.find("host");
    if (it == config_map.end()) {
        throw std::runtime_error("host undefined");
    }
    config.host = it->second;

    it = config_map.find("port");
    if (it == config_map.end()) {
        throw std::runtime_error("port undefined");
    }
    // поймаем эксепшн наверху в мейне
    config.port = std::stoul(it->second);

    it = config_map.find("thread_limit");
    if (it == config_map.end()) {
        throw std::runtime_error("thread_limit undefined");
    }
    config.threads_limit = std::stoul(it->second);

    it = config_map.find("document_root");
    if (it == config_map.end()) {
        throw std::runtime_error("root undefined");
    }
    std::filesystem::path p = it->second;

    if (!std::filesystem::exists(it->second)) {
        // тут не знаю, пока кидаю exception;
        throw std::runtime_error("root doesn't exists");
    }
    if (!std::filesystem::is_directory(it->second)) {
        throw std::runtime_error("not a directory");
    }
    config.document_root = it->second;
    return config;
}


int main() {

//    std::string host = "127.0.0.1";
//    auto port = 8081;
//    auto num_workers = 8;  // get num of CPU cores
//    auto doc_root = "/home/danil_rzhevsky/TECHOPARK/highload/http_static_server/doc_root";

    auto config = ParseConfig("../httpd.conf");

    Server server(config.host, config.port, config.threads_limit, config.document_root);
    try {
        server.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Undefined exception" << std::endl;
    }

    return 0;
}
