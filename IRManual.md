#Spider IR Reference
The language follows a simple Command Table syntax.
###Keywords are:
* show : show variable
* break : Break out of a block
* let : Declare a variable, `let i int i7479`
* assign : Alter the value of a variable, `assign i j` means i=j  generate "petersen"
* if : if condition {block} . `{` and `}` must be on new lines. There is no else.
* while : WHile loop, structure similar to if.
* function : Define a function. See example below.

_ is treated as a special sybmol that contains the result of the last operation.  
Similarly, __ stores the one before that.

###The types supported are:
* int : Literals must have i prefixed 
* bool: true and false
* float : Literals must have f prefixed
* string : "value"
* list : List of arbitrary values. (Resembles S-Expressions)
* graph : call generate to create a graph and use _ to access it.
* window : call display graphname to display a graph on screen

###Available functions:
Look at lib/Runtime/Functions.cpp
###Available Graph Generators:
Look at GraphNameMap in lib/Runtime/GraphOperations.hpp
###Available layouts:
Look win_change_layout in lib/Runtime/WindowOperations.hpp

TODO: Expand the above sections, and add explanations.

##Example Code:
* Generate and Display a graph:
```
generate "petersen"
display _
change_layout _ "bicircular"
```

* Inspect the BFS of a graph at runtime:
```
generate "generalized_petersen" i20 i4
bfs_animate _ "1"
```
* Define a factorial function:
```
function factorial f int n int
{
    let f int i1
    lesser n i2
    if _
    {
        break
    }
    sub n i1
    factorial _
    mul n _
    assign f _
}
factorial i5
show _
```
* Insert and Delete Vertices:
```
generate "complete" i7
let g graph _
display g
insert_vertex g "8"
insert_edge g "8" "7" i1
remove_edge g "1" "2"
remove_vertex g "3"
```