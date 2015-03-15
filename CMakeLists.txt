cmake_minimum_required(VERSION 3.0.0)

# project(spider)
project(qspider)
# find_package(KDE4 REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fexceptions -fPIC") 
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

include_directories(include)

# The Qt5Widgets_INCLUDES also includes the include directories for
# dependencies QtCore and QtGui
include_directories(${Qt5Widgets_INCLUDE_DIRS})

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
# add_definitions(${Qt5Widgets_DEFINITIONS})

link_directories(lib)

add_subdirectory(lib)

# add_executable(spider main/main.cpp)
# target_link_libraries(spider spiderMain X11 pthread sfml-system sfml-window sfml-graphics)

add_executable(qspider main/qtmain.cpp)
qt5_use_modules(qspider Widgets Core)
target_link_libraries(qspider spiderMain)
file(COPY resource DESTINATION .)
