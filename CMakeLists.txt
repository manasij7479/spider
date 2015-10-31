cmake_minimum_required(VERSION 3.0.0)

project(spider)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(FLEX REQUIRED)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fexceptions -fPIC -Wno-inconsistent-missing-override -Wno-deprecated-register")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")



include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(include)

add_subdirectory(lib)
FLEX_TARGET(Lexer spider.lex  ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cpp)

add_executable(spider main/qtmain.cpp ${FLEX_Lexer_OUTPUTS})
qt5_use_modules(spider Widgets Core)
target_link_libraries(spider Display Runtime Compiler)
file(COPY resource DESTINATION .)
file(COPY example DESTINATION .)

add_subdirectory(example)
