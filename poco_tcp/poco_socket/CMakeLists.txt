find_package(Poco REQUIRED Foundation Net Util)

set(TCP_SOURCES poco_socket.cpp task1.cpp)
set(TCP_HEADERS ${PROJECT_SOURCE_DIR}/include)
set(TCP_RESOURCES ${PROJECT_SOURCE_DIR}/resources)

add_executable(poco_socket ${TCP_SOURCES})

add_custom_command(TARGET poco_socket POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${TCP_RESOURCES} $<TARGET_FILE_DIR:poco_socket>/resources)

target_link_libraries(poco_socket PRIVATE Poco::Foundation Poco::Net)

target_include_directories(poco_socket PUBLIC ${TCP_HEADERS})