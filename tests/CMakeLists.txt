cmake_minimum_required(VERSION 3.0)

project(time_service_tests)

find_package(GTest REQUIRED)
add_library(time STATIC ../src/time/time.cpp)

add_executable(runUnitTests unit_tests.cpp)
target_link_libraries(runUnitTests GTest::GTest GTest::Main)
target_link_libraries(runUnitTests time)