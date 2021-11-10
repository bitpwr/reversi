set(APP_NAME reversi-cli)

add_executable(${APP_NAME} src/main.cpp)
target_link_libraries(${APP_NAME} reversi)
set_target_properties(${APP_NAME} PROPERTIES CXX_STANDARD 20)

install(TARGETS ${APP_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} )
