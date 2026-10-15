cmake_minimum_required(VERSION 3.10)

project(josh)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(cpprestsdk CONFIG REQUIRED)

if(UNIX AND NOT APPLE)
    find_package(OpenSSL REQUIRED)
endif()

add_executable(josh test.cpp)
target_link_libraries(josh PRIVATE cpprestsdk::cpprest)
if(UNIX AND NOT APPLE)
    target_link_libraries(josh PRIVATE OpenSSL::SSL OpenSSL::Crypto)
endif()

enable_testing()

add_executable(call_api_test call_api_test.cpp)
target_link_libraries(call_api_test PRIVATE cpprestsdk::cpprest)
if(UNIX AND NOT APPLE)
    target_link_libraries(call_api_test PRIVATE OpenSSL::SSL OpenSSL::Crypto)
endif()

add_test(NAME call_api_test COMMAND call_api_test)
