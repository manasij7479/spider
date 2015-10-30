# QT5_WRAP_CPP(graph_value_moc ../../include/Runtime/GraphValue.hpp)
# QT5_WRAP_CPP(window_value_moc ../../include/Runtime/WindowValue.hpp)
# QT5_WRAP_CPP(type_moc ../../include/Runtime/Type.hpp)

add_library(Compiler AST.cpp GlobalState.cpp Sema.cpp)