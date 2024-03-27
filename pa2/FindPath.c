/****************************************************************************************
Ann Sasi
pa2
CruzID asasi
FindPath.c

*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

#define MAX_LEN 300

int main(int argc, char *argv[]) {
    FILE *in, *out;
    int vertices, a, b;

    // Check command line for correct number of arguments
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // Open files
    in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // Read the number of vertices
    fscanf(in, "%d", &vertices);
    // Initialize the graph with the number of vertices
    Graph G = newGraph(vertices);

    while (fscanf(in, "%d %d", &a, &b) == 2) {
        if (a ==0 && b==0){
            break;
        }
        addEdge(G,a,b);
    }
    printGraph(out, G);

    while (fscanf(in, "%d %d", &a, &b) ==2){
        if (a == 0 && b == 0){
            break;
        }
        BFS(G, a);
        List Path = newList();
        getPath(Path, G, b);
        fprintf(out, "\nThe distance from %d to %d is ", a, b);
        if (getDist(G, b) == INF){
            fprintf(out, "infinity\n");
            fprintf(out, "No %d-%d path exists \n", a,b);
        }
        else{
            fprintf(out, "%d\n", getDist(G,b));
            fprintf(out, "A shortest %d-%d path is: ", a,b);
            printList(out, Path);
            fprintf(out, "\n");
        }
        freeList(&Path);
    }
    fprintf(out, "\n");
    fclose(in);
    fclose(out);
    freeGraph(&G);
    return 0;
}
