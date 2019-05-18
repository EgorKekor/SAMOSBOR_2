cmake_minimum_required(VERSION 3.13)
project(client)
project(server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer -g -Wextra -Werror -Wall -pedantic")

include(FindProtobuf)
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})

include_directories(.)
include_directories(include/cli)
include_directories(include/res)
include_directories(include/srv)


include_directories(${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate_cpp(PROTO_SRC PROTO_HEADER src/proto/event.proto)
add_library(proto ${PROTO_HEADER} ${PROTO_SRC})

file(GLOB client_SRC
        "src/res/*.cpp"
        "src/cli/*.cpp"
        )

file(GLOB server_SRC
        "src/res/*.cpp"
        "src/srv/*.cpp"
        )

add_executable(client ${client_SRC})
add_executable(server ${server_SRC})


target_link_libraries(client proto ${PROTOBUF_LIBRARY})
target_link_libraries(server proto ${PROTOBUF_LIBRARY})
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
FIND_PACKAGE(SFML 2 REQUIRED system window graphics network audio)

INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(client ${SFML_LIBRARIES} tinyxml)
TARGET_LINK_LIBRARIES(server ${SFML_LIBRARIES} tinyxml)
