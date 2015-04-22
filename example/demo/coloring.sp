import "resource/functions";
auto g = generate("petersen");

auto w = display(g)
change_layout(w "bicircular");
display_vertex_coloring(w true);

auto w2 = display(g);
change_layout(w2 "bicircular");
display_edge_coloring(w2 true);