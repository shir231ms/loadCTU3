# loadCTU3
ItriInturn_FirstTask

add "loadCTU3.m" for reading the output file, "data.txt", of "main.cpp", 
and then draw those polygons out (only lines, no arcs).

use getWord function for gaining word from ".ctu3" file.
change the type of the floating numbers from "long double" to "double" type. 

sort polygons specially.
add "PointNodeLL.h" for storing sorted X points and Y points.

The type, "Polygon", points to a circular doubly linked list.  
The circular doubly linked list stores Edges and Vertexs details.
"main.cpp" just needs to refer "PEdll.h".
