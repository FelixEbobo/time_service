cmake_minimum_required(VERSION 3.0)

project(time_service_server)

add_library(time_service_server STATIC server.cpp session.cpp)

# find_package(Boost REQUIRED COMPONENTS system bind) 

include_directories("/usr/local/include/boost/bind"
                    "/usr/local/include/boost/asio"
                    "/usr/local/include/boost") 
target_link_libraries(time_service_server 
                    "/usr/local/include/boost/asio.hpp"
                    "/usr/local/include/boost/bind/bind.hpp"
                    "/usr/local/include/boost/shared_ptr.hpp")