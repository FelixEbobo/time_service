cmake_minimum_required(VERSION 3.0)

project(time_service_time)

add_library(time_service_time STATIC time.cpp)

include_directories("/usr/local/include/boost/format") 
target_link_libraries(time_service_time
                    "/usr/local/include/boost/format.hpp")