#include <iostream>
#include "server/Server.h"


int main() {

    std::string host = "127.0.0.1";
    auto port = 8081;
    auto num_workers = 8;  // get num of CPU cores

    Server server(host, port, num_workers);
    try {
        server.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Undefined exception" << std::endl;
    }

    return 0;
}
