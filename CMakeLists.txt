cmake_minimum_required(VERSION 3.15.0)
project(reversi VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(${PROJECT_NAME}
    src/reversi.hpp
    src/reversi.cpp
    src/main.cpp
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
