cmake_minimum_required(VERSION 3.28.1)

project(poco_tcpclient)

set(CLIENT_SOURCES client/poco_tcpclient.cpp client/poco_tcpclient.h)

find_package(Poco REQUIRED Foundation Net)

add_executable(poco_tcpclient ${CLIENT_SOURCES})

target_link_libraries(poco_tcpclient PRIVATE Poco::Foundation Poco::Net)