add_library(Runtime Functions.cpp UserFunction.cpp Runtime.cpp)
target_link_libraries(Runtime Display sfml-system sfml-window sfml-graphics)