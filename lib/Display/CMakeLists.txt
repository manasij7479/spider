qt_wrap_cpp(Display WindowUI.cpp ../../include/QtDisplay/WindowUI.hpp)
add_library(Display GraphSprite.cpp WindowUI.cpp)