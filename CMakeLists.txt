cmake_minimum_required(VERSION 2.8.12)
set(CMAKE_BUILD_TYPE Debug)

set(GUROBI_ROOT "/opt/local/stow/gurobi910/linux64/")
set(GUROBI_INCLUDE_DIR "${GUROBI_ROOT}include")
message(STATUS "GUROBI_INCLUDE_DIR : ${GUROBI_INCLUDE_DIR}")
set(GUROBI_LIBRARY_CPLUS "${GUROBI_ROOT}lib/libgurobi_c++.a")
set(GUROBI_LIBRARY "${GUROBI_ROOT}lib/libgurobi91.so")
set(GUROBI_LIBRARIES ${GUROBI_LIBRARY_CPLUS} ${GUROBI_LIBRARY})
message(STATUS "GUROBI_LIBRARIES : ${GUROBI_LIBRARIES}")

add_compile_options(-std=c++11)
project(network_flows)
include_directories(include)
include_directories(${GUROBI_INCLUDE_DIR})
file(GLOB SRC
    src/main.cpp
    src/parser.cpp
    src/manipulation.cpp
    src/Structures.cpp
    src/algorithms.cpp
    src/PLFlows.cpp
)
add_executable(a.out ${SRC})
target_link_libraries(a.out ${GUROBI_LIBRARIES})
