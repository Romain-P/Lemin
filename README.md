# Lem-in

Parser that handles warning and error messages.
 - Duplicated node (position or name)
 - Unknown parsed line
 - Circular paths (then showing useless nodes)
 - Fatal errors (no starting/ending node or w/o link)
 - No valid path found

Examples of use:  
```
./lem_in < map/valid
./lem_in map/warn_circular_nodes
```
No memory leak and no error. Valgrind my friend.