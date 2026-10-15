cmake_minimum_required(VERSION 3.10)

project(josh)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(cpprestsdk CONFIG REQUIRED)

add_executable(josh test.cpp)

target_link_libraries(josh PRIVATE cpprestsdk::cpprest)

if(UNIX AND NOT APPLE)
    find_package(OpenSSL REQUIRED)
    target_link_libraries(josh PRIVATE OpenSSL::SSL OpenSSL::Crypto)
endif()
