cmake_minimum_required(VERSION 2.8.8)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(spider)

include_directories(include)
link_directories(lib)


add_subdirectory(lib)
# add_subdirectory(test)

add_executable(spider main.cpp)
target_link_libraries(spider spiderMain OGDF pthread)
