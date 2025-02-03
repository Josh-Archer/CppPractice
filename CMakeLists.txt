cmake_minimum_required(VERSION 3.10)

project(josh)

find_package(cpprestsdk CONFIG REQUIRED)

add_executable(josh test.cpp)

target_link_libraries(josh PRIVATE cpprestsdk::cpprestsdk)
