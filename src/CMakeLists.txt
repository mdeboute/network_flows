add_executable (app main.cpp)

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/app
  DESTINATION bin
  RENAME ${CMAKE_PROJECT_NAME}-app)