
include(CTest)

find_package(Catch2 REQUIRED)

set(TEST_BIN_DIR ${CMAKE_BINARY_DIR}/bin/test)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TEST_BIN_DIR})

add_executable(firsttest test.cpp)

target_include_directories(firsttest PRIVATE ${Catch2_INCLUDE_DIR})

add_test(NAME FirstTest COMMAND ${TEST_BIN_DIR}/firsttest)
