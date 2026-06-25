#ifndef GRAPH_H
#define GRAPH_H
#include "map.h"
#include "list.h"


typedef struct Graph Graph;


typedef struct {
  void *destino; 
  void *data;    
  int peso;      
} GraphEdge;


Graph *graph_create(int (*is_equal)(void *key1, void *key2));


void graph_addVertex(Graph *graph, void *key);


int graph_existsVertex(Graph *graph, void *key);


int graph_addEdge(Graph *graph, void *origen, void *destino, int peso, void *data);


List *graph_getEdges(Graph *graph, void *key);


void *graph_firstVertex(Graph *graph);


void *graph_nextVertex(Graph *graph);

int graph_vertexCount(Graph *graph);

#endif 