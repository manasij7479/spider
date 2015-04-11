#Spider IR Reference

###Keywords/Commands:
* show : show variable.
* break : Break out of a block.
* let : Declare a variable, `let i i7479`
* assign : Alter the value of a variable, `assign i j` means i=j
* if : if condition {block} . `{` and `}` must be on new lines. There is no else.
* while : While loop, structure similar to if.
* function : Define a function. See example.

_ is treated as a special symbol that contains the result of the last operation.  

###The types supported are:
* int : Literals must have i prefixed 
* bool: true and false
* float : Literals must have f prefixed
* string : "value"
* list : List of arbitrary values. (Resembles S-Expressions)
* graph : call generate to create standard graph.
* window : call display graphname to display a graph on screen

###Available functions:
Look at lib/Runtime/Functions.cpp
###Available Graph Generators:
Look at GraphNameMap in lib/Runtime/GraphOperations.hpp
###Available layouts:
Look win_change_layout in lib/Runtime/WindowOperations.hpp

###Simple example
```
let g generate "petersen"
display g
change_layout _ "bicircular"
```
Here, display returns a value of type 'window'.
Instead of explicitly assigning it to a variable, we just access it from the `_` meta-identifier.

###More Example code can be found in the example directory