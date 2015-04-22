import "resource/functions";
auto g = generate("cycle" 10);
auto window = display(g);
auto path = dijkstra_path(g 2 7);
for_each
(
    gen_pairs(path)
    mark_edge_v2
    create_list(window "red")
);