cmake_minimum_required(VERSION 3.15.0)
project(reversi VERSION 0.2.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
include(GNUInstallDirs)

option(BUILD_SHARED_LIBS "Defines if the reversi library should be shared or static" OFF)

add_subdirectory(lib)
add_subdirectory(cli)

enable_testing()
add_subdirectory(test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
