set(LIB_NAME reversi)

find_package(range-v3 REQUIRED)

add_library(${LIB_NAME}
        src/reversi.cpp
        include/reversi.hpp
)

target_link_libraries(${LIB_NAME} range-v3::range-v3)
target_include_directories(${LIB_NAME} PUBLIC include/)
set_target_properties(${LIB_NAME} PROPERTIES PUBLIC_HEADER "include/reversi.hpp")
set_target_properties(${LIB_NAME} PROPERTIES CXX_STANDARD 20)

install(TARGETS ${LIB_NAME}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
