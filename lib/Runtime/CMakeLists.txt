add_library(Runtime SHARED Functions.cpp)
target_link_libraries(Runtime Display sfml-system sfml-window sfml-graphics)