cmake_minimum_required(VERSION 3.0.0)

project(spider)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
FIND_PACKAGE(BISON REQUIRED)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fexceptions -fPIC") 
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

execute_process(COMMAND ${BISON_EXECUTABLE} ${PROJECT_SOURCE_DIR}/include/graph/util/gml/gmlparser.y)
file(RENAME ${PROJECT_BINARY_DIR}/gmlparser.tab.c ${PROJECT_SOURCE_DIR}/include/graph/util/gml/gmlparser.tab.c)

include_directories(include)
include_directories(${Qt5Widgets_INCLUDE_DIRS})

add_subdirectory(lib)

add_executable(spider main/qtmain.cpp)
qt5_use_modules(spider Widgets Core)
target_link_libraries(spider Display Runtime)
file(COPY resource DESTINATION .)
file(COPY example DESTINATION .)

add_subdirectory(example)