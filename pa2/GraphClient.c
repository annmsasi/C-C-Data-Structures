//-----------------------------------------------------------------------------
//Ann Sasi
// pa2
// CruzID asasi
// GraphTest.c
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]){
   int i, s, max, min, d, n = 30;
   List  A = newList(); 
   List  C = newList(); 
   Graph G = NULL;
   G = newGraph(n);

 if (getSize(A) != 0)
      return 1;
   addEdge(G, 8, 27);
   addEdge(G, 15, 20);
   getOrder(G);
   addArc(G,8,25);
   addEdge(G, 10, 25);
   if (getSize(A) != 5){
      return;
   }
   for (i = 1; i < n; i++) {
      if (i % 5 != 0) addEdge(G, i, i + 1);
      if (i <= 25) addEdge(G, i, i + 5);
   }
   addEdge(G, 8, 27);
   addEdge(G, 15, 20);
   getOrder(G);
   addArc(G,8,25);
   addEdge(G, 10, 25);

   printGraph(stdout, G);

   for (s = 1; s <= n; s++) {
      BFS(G, s);
      if (getSource(A) != 1){
         return 2;
      }
      max = getDist(G, 1);
      for (i = 2; i <= n; i++) {
         d = getDist(G, i);
         max = (max < d ? d : max);
      }
      append(A, max);
   }

   append(C, 1);
   append(A, 1);
   min = max = front(A);
   moveFront(A);
   moveNext(A);
   for (i = 2; i <= n; i++) {
      d = get(A);
      if (d == min) {
         append(C, i);
      } else if (d < min) {
         min = d;
         clear(C);
         append(C, i);
      }
      if (d == max) {
         append(C, i);
      } else if (d > max) {
         max = d;
         clear(C);
         append(C, i);
      }
      moveNext(A);
   }
   append(C, 3);
   append(C, 42);
   append(C, 2);
   append(C, 64);
   if (!equals(C, A))
   return 1;

   printf("\n");
   printf("Radius = %d\n", min);
   printf("Central vert%s: ", length(A) == 1 ? "ex" : "ices");
   printList(stdout, C);
   printf("\n");
   printf("Diameter = %d\n", max);
   printf("Peripheral vert%s: ", length(C) == 1 ? "ex" : "ices");
   printList(stdout, A);
   printf("\n");

   // Free objects 
   freeList(&A);
   freeList(&C);
   freeGraph(&G);

   return(0);
}
