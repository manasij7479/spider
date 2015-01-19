cmake_minimum_required(VERSION 2.8.7)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_subdirectory(Display)
add_subdirectory(Runtime)
add_library(spiderMain empty.cpp)
target_link_libraries(spiderMain Display Runtime)
