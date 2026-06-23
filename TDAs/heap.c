#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heap_top(Heap* pq){
    if(pq->size==0) return NULL;
    return pq->heapArray[0].data;
}

void heap_push(Heap* pq, void* data, int priority) {

    if (pq->size + 1 > pq->capac) {
        pq->capac = pq->capac * 2 + 1;
        pq->heapArray = realloc(
            pq->heapArray,
            pq->capac * sizeof(heapElem)
        );
    }

    int posicion = pq->size;

    // Mientras la prioridad nueva sea menor que la del padre,
    // el elemento sube dentro del Min Heap.
    while (posicion > 0 &&
           pq->heapArray[(posicion - 1) / 2].priority > priority) {

        pq->heapArray[posicion] =
            pq->heapArray[(posicion - 1) / 2];

        posicion = (posicion - 1) / 2;
    }

    pq->heapArray[posicion].priority = priority;
    pq->heapArray[posicion].data = data;
    pq->size++;
}


void heap_pop(Heap* pq) {

    if (pq == NULL || pq->size == 0) {
        return;
    }

    pq->size--;

    if (pq->size == 0) {
        return;
    }

    pq->heapArray[0] = pq->heapArray[pq->size];

    int actual = 0;

    while (1) {
        int izquierdo = 2 * actual + 1;
        int derecho = 2 * actual + 2;
        int menor = actual;

        if (izquierdo < pq->size &&
            pq->heapArray[izquierdo].priority <
            pq->heapArray[menor].priority) {

            menor = izquierdo;
        }

        if (derecho < pq->size &&
            pq->heapArray[derecho].priority <
            pq->heapArray[menor].priority) {

            menor = derecho;
        }

        if (menor == actual) {
            break;
        }

        heapElem auxiliar = pq->heapArray[actual];
        pq->heapArray[actual] = pq->heapArray[menor];
        pq->heapArray[menor] = auxiliar;

        actual = menor;
    }
}

Heap* heap_create(){
   Heap *pq=(Heap*) malloc(sizeof(Heap));
   pq->heapArray=(heapElem*) malloc(3*sizeof(heapElem));
   pq->size=0;
   pq->capac=3; //capacidad inicial
   return pq;
}
