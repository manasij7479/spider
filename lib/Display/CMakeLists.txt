QT4_WRAP_CPP(windowui_moc ../../include/QtDisplay/WindowUI.hpp)
QT4_WRAP_CPP(mainwindow_moc ../../include/QtDisplay/MainWindow.hpp)
QT4_WRAP_CPP(editor_moc ../../include/QtDisplay/SpiderEditor.hpp)
QT4_WRAP_CPP(output_moc ../../include/QtDisplay/OutputPane.hpp)
add_library(Display WindowUI.cpp MainWindow.cpp SpiderEditor.cpp OutputPane.cpp
                    ${windowui_moc} ${mainwindow_moc} ${editor_moc} ${output_moc})
target_link_libraries(Display Runtime)