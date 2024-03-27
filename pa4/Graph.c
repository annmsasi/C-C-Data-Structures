/****************************************************************************************
Ann Sasi
pa3
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
#define GRAY 2
typedef struct GraphObj{
    int* finish;
    int* discover;
    int* color;
    int* parent;
    int order;
    int size;
    List* neighbors;
    // bool BFSed;
}GraphObj;
/*** Constructors-Destructors ***/
Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    assert(G != NULL);
    G -> neighbors = calloc(n+1, sizeof(List));
    G -> finish = calloc(n+1, sizeof(int));
    G -> discover = calloc(n+1, sizeof(int));
    G -> parent = calloc(n+1, sizeof(int));
    G -> color = calloc(n+1, sizeof(int));
    G -> order = n;
    G -> size = 0;
    for (int i=1; i<=n; i++){
        G -> neighbors[i] = newList();
        G -> parent[i] = NIL;
        G -> discover[i] = UNDEF;
        G -> color[i] =  WHITE;
        G -> finish[i] = UNDEF;
    }
    return G;
}
void freeGraph(Graph* pG){
    for (int i = 0; i <= (*pG) -> order; i++){
        freeList(&(*pG) -> neighbors[i]);
    }
    free((*pG) -> neighbors);
    free((*pG) -> parent);
    free((*pG) -> discover);
    free((*pG) -> finish);
    free((*pG) -> color);
    free(*pG);
    *pG = NULL;

}
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
int getParent(Graph G, int u){
    if (G == NULL){
        printf("Graph Error: calling getParent() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (1 >= u  || u <= getOrder(G)){
        return G -> parent[u];
    }
    return NIL;

    
} /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u){
    if (G == NULL){
        printf("Graph Error: calling getDiscover() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    else if (1 > u  || u > getOrder(G)){
        printf("%d",getOrder(G));
        printf("Graph Error: calling getDiscover() on bad List reference\n");
        exit(EXIT_FAILURE);
    }
    return G -> discover[u];
} /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u){
    if (G == NULL){
        printf("Graph Error: calling getFinish() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    else if (1 > u  || u > getOrder(G)){
        printf("%d",getOrder(G));
        printf("Graph Error: calling getFinish() on bad List reference\n");
        exit(EXIT_FAILURE);
    }

    return G -> finish[u];
} /* Pre: 1<=u<=n=getOrder(G) */
// Manipulation procedures
void addArc(Graph G, int u, int v){
    if (G == NULL){
        printf("Graph Error: calling addArc() on NULL List reference\n");
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
 /* Pre: 1<=u<=n, 1<=v<=n */
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
 /* Pre: 1<=u<=n, 1<=v<=n */
void Visit(Graph G, List S, int* time, int vertex){
    if (G == NULL){
        printf("Graph Error: calling DFS() on NULL List reference\n");
        exit(EXIT_FAILURE);
        }
    G -> discover[vertex] =  ++(*time);
    G -> color[vertex] = GRAY;
    moveFront(G -> neighbors[vertex]);
    while(index(G->neighbors[vertex]) >= 0){
        int val  = get(G -> neighbors[vertex]);
            if (G -> color[val]== WHITE){
                G -> parent[val] = vertex;
                Visit(G,S,time, val);
            }
        moveNext(G -> neighbors[vertex]);
        }
    G -> color[vertex] = BLACK;
    G -> finish[vertex] = ++(*time);
    prepend(S, vertex);
}
void DFS(Graph G, List S){
    if (G == NULL){
        printf("Graph Error: calling DFS() on NULL List reference\n");
        exit(EXIT_FAILURE);
        }
    else if (length(S) != getOrder(G)){
        printf("Graph Error: calling DFS() on small List reference\n");
        exit(EXIT_FAILURE);
        }
    for (int x = 1; x <= getOrder(G); x++){
    G->discover[x] = UNDEF;
    G->finish[x] = UNDEF;
    G -> color[x] = WHITE;
    G -> parent[x] = NIL;
    }   
    List copy = copyList(S);
    clear(S);
    int time = 0;
    for (moveFront(copy); index(copy) >= 0; moveNext(copy)){
        int j = get(copy);
        if ( G -> color[j] == WHITE){
            Visit(G, S, &time, j);
        }
    }
    // when list ! empty and transposed graph
    freeList(&copy);
}

 /* Pre: length(S)==getOrder(G) */
// Other Functions
Graph transpose(Graph G){
    if (G == NULL){
        printf("Graph Error: calling transpose() on NULL List reference\n");
        exit(EXIT_FAILURE);
        }
    Graph trans = newGraph(getOrder(G));
    for (int i = 1; i <= getOrder(G); i++){
        moveFront(G -> neighbors[i]);
        while(index( G -> neighbors[i]) != -1){ 
            int val = get( G -> neighbors[i]);
            addArc(trans, val, i);
            moveNext( G -> neighbors[i]);
        }
    }
    return trans;
}
Graph copyGraph(Graph G){
    Graph Copy = newGraph(getOrder(G));
    Copy -> size = getSize(G);
    for(int i = 0; i <= getOrder(G); i++){
        Copy->neighbors[i] = newList();
    }
    for (int i = 1; i <= getOrder(G); i++) {
        moveFront(G->neighbors[i]);
        while (index(G->neighbors[i]) >= 0) {
            int place = get(G->neighbors[i]);
            addArc(Copy, i, place);
            moveNext(G->neighbors[i]);
        }
    }
    Copy -> parent = copyList(G -> parent);
    Copy -> discover = copyList(G -> discover);
    Copy -> color =  copyList(G -> color);
    Copy -> finish= copyList(G -> finish);
    Copy -> order = getOrder(G);
    return Copy;
}
void printGraph(FILE* out , Graph G){
    for(int i = 1; i <= getOrder(G); i++){
        moveFront(G->neighbors[i]);
        fprintf(out, "%d:", i);
        while(index(G->neighbors[i]) >= 0){
            int neighbor = get(G->neighbors[i]);
            fprintf(out, " %d", neighbor);
            moveNext(G->neighbors[i]);
        }
        fprintf(out, "\n");
    }
}  
