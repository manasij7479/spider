clear
let g generate "empty"
insert_vertex g i1
insert_vertex g i2
insert_vertex g i3
insert_vertex g i4
insert_vertex g i5
insert_vertex g i7
insert_vertex g i8
insert_vertex g i9
insert_edge g i1 i2 i1
insert_edge g i1 i3 i2
insert_edge g  i2 i4 i1
insert_edge g i2 i5 i2
insert_edge g i3 i7 i2
insert_edge g i5 i8 i1
insert_edge g i5 i9 i2
display g
change_layout  _  "binary_tree"  i1