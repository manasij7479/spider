QT4_WRAP_CPP(windowui_moc ../../include/QtDisplay/WindowUI.hpp)
add_library(Display GraphSprite.cpp WindowUI.cpp ${windowui_moc})