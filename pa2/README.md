/****************************************************************************************
Ann Sasi
pa2
CruzID asasi
README.md

*****************************************************************************************/

This repository contains the implementation of a Graph ADT as well as BFS traversal algorithm. In addition, there is a client file utilizing the Graph structure and BFS algorithms to take in input and output the shortest path to a vertex from a source on the graph utilizing BFS. It is built utlizing List ADT functions to Enqueue and Dequeue. The project is structured as follows:

List.h: Header file for a C program that implements a doubly linked List ADT. It contains constructors and destructors, as well as getters and setters.

List.c: The implementation of the getters, setters, constructors, and destructors mentioned above. It is implementing a doubly linked list designed to be navigated with a cursor that possesses an index characteristic.

Graph.h: Header file for a C program implementing a Graph ADT as well as BFS traversal algorithm.

Graph.c: The implementation of a Graph ADT including initialization as well as manipulation procedures, constructors, and destructors. The file contains methods allowing for direcetional and non-directional connections to be coreated between vertexes as well as BFS algorithm and the ability to get the shortest path from one source to a vertex. 

GraphTest.c: A file containing function calls to methods in Graph.c to test each method's functionality.

FindPath.c: A C program that acts as a client to Graph.h and takes in input as a file and constructs a graph using this data. The first line is inputted as the source and the following lines are used to created arcs until the delimitter. From there, the lines are used to find the shortest path. The output is the adjacency list of each value in the graph as well as the shortest path from one value to another.

Makefile: A makefile for easy compilation of the project. It defines rules for building the executable files from the source code

README.md: Simply a description of everything mentioned above.