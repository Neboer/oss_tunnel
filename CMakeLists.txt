cmake_minimum_required(VERSION 3.16)
project(oss_tunnel)

set(CMAKE_CXX_STANDARD 14)
#find_library(alibabacloud-oss-cpp-sdk)
link_libraries(alibabacloud-oss-cpp-sdk curl crypto pthread)

add_executable(oss_tunnel main.cpp codec/bin_utf8.cpp codec/bin_utf8.h codec/cryption.c)