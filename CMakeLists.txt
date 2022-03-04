cmake_minimum_required(VERSION 2.8.12)
project(network_flows)
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-std=c++11)

find_library(GUROBI_LIBRARY_CPLUS libgurobi_c++.a PATHS /opt/local/stow/gurobi910/linux64/lib/ /Library/gurobi903/mac64/lib/ /home/pierre/Bureau/prog/gurobi/gurobi951/linux64/lib)
find_library(GUROBI_LIBRARY libgurobi91.so OR libgurobi90.dylib OR libgurobi95.so PATHS /opt/local/stow/gurobi910/linux64/lib/ /Library/gurobi903/mac64/lib/ /home/pierre/Bureau/prog/gurobi/gurobi951/linux64/lib/)

set(GUROBI_LIBRARIES ${GUROBI_LIBRARY_CPLUS} ${GUROBI_LIBRARY})
message(STATUS "GUROBI_LIBRARIES : ${GUROBI_LIBRARIES}")

set(GUROBI_INCLUDE_DIR /opt/local/stow/gurobi910/linux64/include/ /Library/gurobi903/mac64/include/ /home/pierre/Bureau/prog/gurobi/gurobi951/linux64/include)

include_directories(include ${GUROBI_INCLUDE_DIR})

file(GLOB SRC src/*.cpp)
file(GLOB SRC_MAIN src/exec/main.cpp)
add_executable(a.out ${SRC} ${SRC_MAIN})
target_link_libraries(a.out ${GUROBI_LIBRARIES})

file(GLOB SRC_MAXFLOW_SOLVER src/exec/maxFlowSolver.cpp)
add_executable(maxFlowSolver.out ${SRC} ${SRC_MAXFLOW_SOLVER})
target_link_libraries(maxFlowSolver.out ${GUROBI_LIBRARIES})

file(GLOB SRC_MINCOST_SOLVER src/exec/minCostSolver.cpp)
add_executable(minCostSolver.out ${SRC} ${SRC_MINCOST_SOLVER})
target_link_libraries(minCostSolver.out ${GUROBI_LIBRARIES})

execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/data/ ${CMAKE_CURRENT_BINARY_DIR}/data)
