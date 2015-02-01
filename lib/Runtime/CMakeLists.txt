QT4_WRAP_CPP(graph_value_moc ../../include/Runtime/GraphValue.hpp)
QT4_WRAP_CPP(window_value_moc ../../include/Runtime/WindowValue.hpp)
add_library(Runtime Functions.cpp UserFunction.cpp Runtime.cpp ${graph_value_moc} ${window_value_moc})
# target_link_libraries(Runtime Display sfml-system sfml-window sfml-graphics)