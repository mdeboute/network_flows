cmake_minimum_required(VERSION 2.8.12)
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-std=c++11)
project(network_flows)
include_directories(include)
file(GLOB SRC
    src/main.cpp
    src/parser.cpp
    src/manipulation.cpp
    src/Structures.cpp
)
add_executable(a.out ${SRC})
