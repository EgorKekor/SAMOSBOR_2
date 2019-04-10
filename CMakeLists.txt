cmake_minimum_required(VERSION 3.1)

project(game)

include_directories(include)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")

include(FindProtobuf)
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})

# to find *.bp.h files
include_directories(${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate_cpp(PROTO_SRC PROTO_HEADER src/proto/event.proto)
add_library(proto ${PROTO_HEADER} ${PROTO_SRC})

add_executable(server  src/main_server.cpp include/server.h include/connection.h include/message.h include/secure_queue.h src/server.cpp src/connection.cpp ) 

add_executable(client  src/client.cpp include/connection.h include/message.h include/secure_queue.h src/connection.cpp ) 

target_link_libraries(server proto ${PROTOBUF_LIBRARY})
target_link_libraries(client proto ${PROTOBUF_LIBRARY})
