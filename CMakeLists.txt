cmake_minimum_required(VERSION 2.8.8)

project(spider)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g") 
include_directories(include)
link_directories(lib)


add_subdirectory(lib)
# add_subdirectory(test)

add_executable(spider main.cpp)
target_link_libraries(spider spiderMain OGDF pthread sfml-system sfml-window sfml-graphics)

file(COPY resource DESTINATION .)
