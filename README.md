# Range-trees-and-Interval-Trees
Implementation of range trees and interval trees for windowing queries.

Given a set of axis-parallel line segments and a query rectangle, the desired output is to identify all the line segments that intersect with the query rectangle. This functionality is implemented using range trees and interval trees.

20 April 2017  
Meghana M Reddy  

 
FOLDER STRUCTURE / FILES:  
The folder contains the required source and header files. 
1. binaryRangeTree.h
2. binaryRangeTree.cpp
3. line.h
4. interval_tree.h
5. interval_tree.cpp

Range trees are implemented in the files binaryRangeTree.h and binaryRangeTree.cpp.   
Interval Trees are implemented in the files interval_tree.h and interval_tree.cpp.  
Additional helper classes are contained in the file line.h.  


TO COMPILE :
* Run "make" to compile.
* Run "make clean" to delete the compiled file.
* The compiled file has the name "windowing".



TO RUN   
./windowing <input filename (optional)>  

The input file is optional. The default file name is "input.txt"


INPUT (Lines and query rectangle):
* The input needs to be given as a text file. The default input file is "input.txt" which has to be present in the same folder.
* If some other input file needs to be chosen, use commandline.

FORMAT OF INPUT FILE
* The first line of the input file contains two numbers - n m. The first number specifies the number of lines. The second number specifies the number of queries.
* The next n lines specifies the end points of the lines. A line is specified by its two end points - x1 y1 x2 y2.
* Following this, the next m lines contain query rectangles. Each query rectangle is specified by its left lower and right upper end point.
* The query rectangle is hence x1 y1 x2 y2, where (x1, y1) is its left lower end point and (x2 y2) is its right upper end point.
* Only orthogonal windowing has been implemented, i.e., the line segments have to be either vertical or horizontal.


OUTPUT:  
* The query rectangle's endpoints are printed first, followed by the line segments which intersect the query rectangle.
* The line segments are specified using their end points.
* No output is given in case the area of the query rectangle is 0.

