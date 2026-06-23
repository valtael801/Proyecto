#include "graph.h"
#include <stdlib.h>
 
typedef struct {
  void *key;
  List *aristas;
} GraphVertex;
 
struct Graph {
  Map *vertices; 
};
 
Graph *graph_create(int (*is_equal)(void *key1, void *key2)) {
  Graph *graph = (Graph *)malloc(sizeof(Graph));
  if (graph == NULL) return NULL;
  graph->vertices = map_create(is_equal);
  return graph;
}
 
void graph_addVertex(Graph *graph, void *key) {
  if (graph == NULL) return;
  if (map_search(graph->vertices, key) != NULL) return; 
 
  GraphVertex *nuevoVertice = (GraphVertex *)malloc(sizeof(GraphVertex));
  nuevoVertice->key = key;
  nuevoVertice->aristas = list_create();
 
  map_insert(graph->vertices, key, nuevoVertice);
}
 
int graph_existsVertex(Graph *graph, void *key) {
  if (graph == NULL) return 0;
  return map_search(graph->vertices, key) != NULL;
}
 
int graph_addEdge(Graph *graph, void *origen, void *destino, int peso, void *data) {
  if (graph == NULL) return 0;
 
  MapPair *parOrigen = map_search(graph->vertices, origen);
  if (parOrigen == NULL) return 0;
  if (map_search(graph->vertices, destino) == NULL) return 0;
 
  GraphVertex *verticeOrigen = (GraphVertex *)parOrigen->value;
 
  GraphEdge *nuevaArista = (GraphEdge *)malloc(sizeof(GraphEdge));
  nuevaArista->destino = destino;
  nuevaArista->peso = peso;
  nuevaArista->data = data;
 
  list_pushBack(verticeOrigen->aristas, nuevaArista);
  return 1;
}
 
List *graph_getEdges(Graph *graph, void *key) {
  if (graph == NULL) return NULL;
  MapPair *par = map_search(graph->vertices, key);
  if (par == NULL) return NULL;
  GraphVertex *vertice = (GraphVertex *)par->value;
  return vertice->aristas;
}
 
void *graph_firstVertex(Graph *graph) {
  if (graph == NULL) return NULL;
  MapPair *par = map_first(graph->vertices);
  if (par == NULL) return NULL;
  return par->key;
}
 
void *graph_nextVertex(Graph *graph) {
  if (graph == NULL) return NULL;
  MapPair *par = map_next(graph->vertices);
  if (par == NULL) return NULL;
  return par->key;
}
 
int graph_vertexCount(Graph *graph) {
  if (graph == NULL) return 0;
  int contador = 0;
  MapPair *par = map_first(graph->vertices);
  while (par != NULL) {
    contador++;
    par = map_next(graph->vertices);
  }
  return contador;
}