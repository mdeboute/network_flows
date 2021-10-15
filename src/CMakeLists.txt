add_executable (hello hello.cpp)

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/hello
  DESTINATION bin
  RENAME ${CMAKE_PROJECT_NAME}-hello)