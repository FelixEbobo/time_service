cmake_minimum_required(VERSION 3.0)

project(time_service)


add_subdirectory(tests)
add_subdirectory(src/time)
add_subdirectory(src/server)
add_subdirectory(src/logging)


find_package(Boost REQUIRED COMPONENTS system thread)
# find_package(Boost 1.75.0 COMPONENTS system asio)
add_executable(main src/main.cpp)

include_directories("/usr/local/include/boost/asio"
                    "/usr/local/include/boost/system"
                    "/usr/local/include/boost/pthread") 
target_link_libraries(main 
                    "/usr/local/include/boost/asio.hpp")

include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(main ${Boost_LIBRARIES})
target_link_libraries(main time_service_time
                           time_service_logging
                           time_service_server)
