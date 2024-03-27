/****************************************************************************************
Ann Sasi
pa2
CruzID asasi
Graph.c

*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "Graph.h"
#define WHITE 0
#define BLACK 1
#define GREY 2
typedef struct GraphObj{
    int* color;
    int* distance;
    int* parent;
    int order;
    int size;
    int source;
    List* neighbors;
    // bool BFSed;
}GraphObj;
/*** Constructors-Destructors ***/
Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    assert(G != NULL);
    G -> neighbors = calloc(n+1, sizeof(List));
    G -> color = calloc(n+1, sizeof(int));
    G -> distance = calloc(n+1, sizeof(int));
    G -> parent = calloc(n+1, sizeof(int));
    G -> order = n;
    G -> size = 0;
    G -> source = NIL;
    for (int i=1; i<n+1; i++){
        G -> neighbors[i] = newList();
        G -> parent[i] = NIL;
        G -> distance[i] = INF;
        G -> color[i] = WHITE;
    }
    return G;
}
void freeGraph(Graph* pG){
    for (int i = 0; i <= (*pG) -> order; i++){
        freeList(&(*pG) -> neighbors[i]);
    }
    free((*pG) -> neighbors);
    free((*pG) -> parent);
    free((*pG) -> distance);
    free((*pG) -> color);
    free(*pG);
    *pG = NULL;

}
//frees all heap memory associated with the Graph *pG,
//then sets the handle *pG to NULL
/*** Access functions ***/
int getOrder(Graph G){
    if (G == NULL){
        printf("Graph Error: calling getOrder() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return (G -> order);
}
int getSize(Graph G){
    if (G == NULL){
        printf("Graph Error: calling getSize() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return (G -> size);
}
int getSource(Graph G){
    if (G == NULL){
        printf("Graph Error: calling getSource() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (G -> source == NIL){ 
        return NIL;    
        }
    return (G -> source);
}
int getParent(Graph G, int u){
    if (G == NULL){
        printf("Graph Error: calling getParent() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    else if (1 > u  || u > getOrder(G)){
        printf("%d",getOrder(G));
        printf("Graph Error: calling getParent() on bad List reference\n");
        exit(EXIT_FAILURE);
    }
    if (G -> source == NIL){ 
        return NIL;    
        }
    return G -> parent[u];
}

int getDist(Graph G, int u){
    if (1 > u || u > getOrder(G)){
        printf("Graph Error: calling getDist() on bad List reference\n");
        exit(EXIT_FAILURE);
    }
    else if (G == NULL){
        printf("Graph Error: calling getDist() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (G -> source == NIL){ 
        return INF;    
        }
    return G -> distance[u];
}

// Function getPath()
// appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if
// no such path exists
void getPath(List L, Graph G, int u){
    if (1 > u || u > getOrder(G)){
        printf("Graph Error: calling getParent() on bad List reference\n");
        exit(EXIT_FAILURE);
    }
    else if (G == NULL){
        printf("Graph Error: calling getParent() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    else if (getSource(G) == NIL){
        printf("Graph Error: calling getPath() on List reference w/o calling BFS\n");
        exit(EXIT_FAILURE);
    }
    if (G -> source == u){
        append(L,u);
    }
    else if (G -> parent[u] == NIL){
        append(L, NIL);

    }
    else{
        getPath(L, G, getParent(G, u));
        append(L, u);}

}
/*** Manipulation procedures ***/
// Function makeNull() deletes all edges of G, restoring it to its 
// original (no edge) state. (This is called a null graph in graph theory literature)
void makeNull(Graph G){
    if (G == NULL){
        printf("Graph Error: calling makeNull() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    int nums = getOrder(G);
    for (int j = 1; j <= nums ; j++){
        clear(G -> neighbors[j]);
    }
    G -> size = 0;
}
// Function addEdge()
// inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u. 
// Your program is required to maintain these lists in sorted order by increasing labels
void addEdge(Graph G, int u, int v){
    if (G == NULL){
        printf("Graph Error: calling addEdge() on NULL List reference\n");
        exit(EXIT_FAILURE);
        }
    else if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
        printf("Graph Error: calling addEdge() on parameters that are too small.\n");
        exit(EXIT_FAILURE);
        } 
    addArc(G,u,v);
    addArc(G,v,u);
    G -> size --;
}

// Function addArc()
// inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency
// List of v)
void addArc(Graph G, int u, int v){
    if (G == NULL){
        printf("Graph Error: calling makeNull() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    else if ( u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
        printf("Graph Error: calling addArc() on parameters that are too small.\n");
        exit(EXIT_FAILURE);
        }
    List U = G -> neighbors[u];
    moveFront(U);
    while (index(U) >=0){
        if (get(U) == v){
            return;
        }
        else if (get(U) > v){
            insertBefore(U, v);
            G -> size++;
            return;
        }
        moveNext(U);
    }
    append(U, v);
    G -> size++;
}

void BFS(Graph G, int s) {
    if (G == NULL){
        printf("Graph Error: calling BFS() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    else if ( 1 > s || s >getOrder(G)){
        printf("%d",getOrder(G));
        printf("Graph Error: calling BFS() on parameters that are too small.\n");
        exit(EXIT_FAILURE);
        } 
    for (int x = 1; x <= G-> order; x++) {
        if (x != s) {
            G -> color[x] = WHITE;
            G -> distance[x] = INF;
            G -> parent[x] = NIL;
            }
        }
    G -> source = s;
    G -> color[s] = GREY;
    G -> distance[s] = 0;
    G -> parent[s] = NIL;
    List Queue = newList();
    append(Queue, s);
    while (Queue -> length != 0 ){
        int x = front(Queue);
        deleteFront(Queue);
        moveFront(G->neighbors[x]);
        while (index(G->neighbors[x]) >= 0) {
            int val  = get(G -> neighbors[x]);
            if (G -> color[val]== WHITE){
                G -> color[val] = GREY;
                G -> distance[val] = (G -> distance[x])+1;
                G -> parent[val] = x;
                append(Queue, val);
            }
            moveNext(G->neighbors[x]);
        }
        G -> color[x] = BLACK;
    }
    freeList(&Queue);
}
        
void printGraph(FILE* out, Graph G){
    if (out == NULL || G == NULL){
        printf("Graph Error: calling printGraph() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= getOrder(G); i++){
        fprintf(out, "%d: ", i);
        printList(out, G -> neighbors[i]);
        fprintf(out, "\n");
    }
}  
