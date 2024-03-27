/****************************************************************************************
Ann Sasi
pa2
CruzID asasi
Graph.h

*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "List.h"
#ifndef GRAPH_H
#define Graph_H
/*** Constructors-Destructors ***/
typedef struct GraphObj* Graph;
Graph newGraph(int n);
void freeGraph(Graph* pG);
#define INF -1
#define NIL -2
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);

#endif