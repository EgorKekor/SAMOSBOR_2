cmake_minimum_required(VERSION 3.13)
project(SAMOSBOR_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include(FindProtobuf)
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})

include_directories(.)
include_directories(include)
include_directories(src)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate_cpp(PROTO_SRC PROTO_HEADER src/proto/event.proto)
add_library(proto ${PROTO_HEADER} ${PROTO_SRC})

add_executable(SAMOSBOR_2
        include/server.h
        include/message.h
        include/connection.h
        include/secure_queue.h
        src/main.cpp
        src/server.cpp
        src/connection.cpp
        )

target_link_libraries(SAMOSBOR_2 proto ${PROTOBUF_LIBRARY})
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")