import "resource/functions";
auto g = generate("petersen");
auto window = display(g);
change_layout(window "bicircular");
kruskal_cb
(
        g
        mark_edge_v2
        create_list(window "red")
);