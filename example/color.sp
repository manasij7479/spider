let g generate "petersen"
let w1 display g
change_layout w1 "bicircular"
let c vertex_coloring g
let cols value_at c i0
set_vertex_attribute_all g "color" cols
let cn value_at c i1
set_graph_attribute g "cn" cn
let w2 display g
change_layout w2 "bicircular"