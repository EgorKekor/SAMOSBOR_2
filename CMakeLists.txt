cmake_minimum_required(VERSION 3.1)

project(game)

include_directories(include)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")


add_executable(server  src/main_server.cpp include/server.h include/connection.h include/message.h include/secure_queue.h src/server.cpp src/connection.cpp ) 

add_executable(client  src/client.cpp include/connection.h include/message.h include/secure_queue.h src/connection.cpp ) 
