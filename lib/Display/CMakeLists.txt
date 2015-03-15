QT5_WRAP_CPP(windowui_moc ../../include/QtDisplay/WindowUI.hpp)
QT5_WRAP_CPP(mainwindow_moc ../../include/QtDisplay/MainWindow.hpp)
QT5_WRAP_CPP(editor_moc ../../include/QtDisplay/SpiderEditor.hpp)
QT5_WRAP_CPP(output_moc ../../include/QtDisplay/OutputPane.hpp)
add_library(Display WindowUI.cpp MainWindow.cpp SpiderEditor.cpp OutputPane.cpp
                    ${windowui_moc} ${mainwindow_moc} ${editor_moc} ${output_moc})
qt5_use_modules(Display Widgets Core)
target_link_libraries(Display Runtime)
