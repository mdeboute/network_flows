add_executable (a.out main.cpp)

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/a.out
  DESTINATION bin
  RENAME ${CMAKE_PROJECT_NAME}-a.out)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_compile_options(-std=c++11)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/exec)