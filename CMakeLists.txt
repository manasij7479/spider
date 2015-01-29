cmake_minimum_required(VERSION 2.8.7)

project(spider)
project(qspider)
find_package(KDE4 REQUIRED)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fexceptions") 
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

include_directories(include)
include_directories(${KDE4_INCLUDES})

link_directories(lib)


add_subdirectory(lib)
# add_subdirectory(test)

add_executable(spider main/main.cpp)
target_link_libraries(spider spiderMain X11 pthread sfml-system sfml-window sfml-graphics)

kde4_add_executable(qspider main/qtmain.cpp main/mainwindow.cpp)
target_link_libraries(qspider ${KDE4_KDEUI_LIBS} 

                                ${KDE4_KIO_LIBS}

                                ${KDE4_KTEXTEDITOR_LIBS})


file(COPY resource DESTINATION .)
