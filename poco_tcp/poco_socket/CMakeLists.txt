find_package(Poco REQUIRED Foundation Net Util)

set(TCP_SOURCES poco_socket.cpp task1.cpp)
set(TCP_HEADERS ${PROJECT_SOURCE_DIR}/include)

add_executable(poco_socket ${TCP_SOURCES})

target_link_libraries(poco_socket PRIVATE Poco::Foundation Poco::Net)

target_include_directories(poco_socket PUBLIC ${TCP_HEADERS})