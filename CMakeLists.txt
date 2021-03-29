cmake_minimum_required(VERSION 3.17)
project(http_static_server)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Werror -Wpedantic -std=c++1z -pthread")
set(LIBEVENT_NAME "event")
set(LIBEVENT_LIB_DIR "/usr/local/lib")
set(LIBEVENT_INCLUDE_DIR "/usr/local/include")

link_directories("${LIBEVENT_LIB_DIR}/")

include_directories("${LIBEVENT_INCLUDE_DIR}")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(http_static_server main.cpp server/Server.cpp server/Server.h socket/Socket.cpp socket/Socket.h work_queue/WorkQueue.cpp work_queue/WorkQueue.h event_callbacks.cpp work_queue/Worker.cpp work_queue/Worker.h http/Request.cpp http/Request.h http/common.h)

target_link_libraries(http_static_server ${LIBEVENT_NAME})
target_include_directories(http_static_server PUBLIC
        "${PROJECT_SOURCE_DIR}/http"
        "${PROJECT_SOURCE_DIR}/server"
        "${PROJECT_SOURCE_DIR}/response"
        "${PROJECT_SOURCE_DIR}/request"
        "${PROJECT_SOURCE_DIR}/socket"
        "${PROJECT_SOURCE_DIR}/work_queue"
        )