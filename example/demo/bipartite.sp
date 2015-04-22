import "resource/functions";
auto g1=generate("complete_bipartite" 5 8);
auto f=<0/1>(5.0 8.0);
auto w = display(g1);
change_layout(w "bipartite" f);
