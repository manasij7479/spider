import "resource/functions";
auto g = generate("empty_directed");
auto i = 1;
insert_vertex(g 0);
while( 'i lesser 10)
{
	insert_vertex(g i);
	insert_edge(g i sub(i 1) i);
	i = 'i add 1;
}
display(g);