
include(CTest)

find_package(Catch2 REQUIRED)

# setup_test(name file1.cpp file2.cpp)
###########################################
macro(setup_test name)
    set(exec test-${name})
    add_executable(${exec} test_main.cpp ${ARGN})
    set_target_properties(${exec}
        PROPERTIES
            CXX_STANDARD 20
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/test)
    target_include_directories(${exec}
        PRIVATE
            ${Catch2_INCLUDE_DIR}
            ${CMAKE_SOURCE_DIR}/src)
    add_test(NAME ${exec} COMMAND ${exec})
endmacro()

setup_test(board
    board/test_board.cpp
    ${CMAKE_SOURCE_DIR}/src/reversi.cpp
)
