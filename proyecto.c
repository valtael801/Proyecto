#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDAs/list.h"
#include "TDAs/map.h"
#include "TDAs/heap.h"

// Representa una "arista" en el grafo
typedef struct Vuelo{
    char destino[10];
    int duracion;
    char horario[10];
}Vuelo;

// Representa "entidades" en el grafo
typedef struct Aeropuerto{
    char codigo[10];
    List* lVuelos; // Lista de adyacencia: guarda todos los vuelos que salen de aquí
}Aeropuerto;

// Estructura principal que encapsula toda la red
typedef struct grafoVuelo{
    Map* aeropuertos; // Mapa central para buscar entidades 
}grafoVuelo;

// Estructura para guardar el resultado del algoritmo de Dijkstra
typedef struct Ruta {
    List* escalas; 
    int tiempoTotal;
} Ruta;

// Función para que el mapa sepa comparar textos
int is_equal_string(void *key1, void *key2) {
    if (strcmp((char*)key1, (char*)key2) == 0) {
        return 1; 
    }
    return 0; 
}

// Crea una nueva entidades y lo añade a la red
void agregarAeropuerto(grafoVuelo* grafo, char* codigo) {
    Aeropuerto* nuevoAero = (Aeropuerto*)malloc(sizeof(Aeropuerto));
    strcpy(nuevoAero->codigo, codigo);
    nuevoAero->lVuelos = list_create(); 
    map_insert(grafo->aeropuertos, nuevoAero->codigo, nuevoAero); 
    printf("Aeropuerto %s registrado con exito.\n", codigo);
}
// Crea una nueva arista dirigida entre dos vértices
void agregarVuelo(grafoVuelo* grafo, char* origen, char* destino, int duracion, char* horario) {
    Aeropuerto* aeroO = (Aeropuerto*)map_search(grafo->aeropuertos, origen);
    if (aeroO == NULL) {
        printf("Error: El aeropuerto %s no existe en la red.\n", origen);
        return;
    }
    Vuelo* nuevoVuelo = (Vuelo*)malloc(sizeof(Vuelo));
    strcpy(nuevoVuelo->destino, destino);
    nuevoVuelo->duracion = duracion;
    strcpy(nuevoVuelo->horario, horario);
    list_pushBack(aeroO->lVuelos, nuevoVuelo); 
    printf("Vuelo de %s a %s registrado con exito.\n", origen, destino);
}


int main() {
    grafoVuelo* grafo = (grafoVuelo*)malloc(sizeof(grafoVuelo));
    grafo->aeropuertos = map_create(is_equal_string);

    int opcion;
    char entrada[10];

    do {
        printf("\n========================================\n");
        printf("    SISTEMA DE GESTION DE VUELOS        \n");
        printf("========================================\n");
        printf("1. Agregar Aeropuerto\n");
        printf("2. Agregar Vuelo\n");
        printf("3. Visualizar Red\n");
        printf("4. Buscar Ruta Optima (Dijkstra)\n");
        printf("5. Salir\n");
        printf("========================================\n");
        printf("Seleccione una opcion: ");

        if (scanf(" %c", &opcion) != 1) opcion = '0';

        switch (opcion) {
            case '1': {
                char codigo[10];
                printf("Ingrese codigo del aeropuerto (ej. MIA, LIM): ");
                scanf("%9s", codigo);
                agregarAeropuerto(grafo, codigo);
                break;
            }
            case '2': {
                char origen[10], destino[10], horario[10];
                int duracion;
                printf("Codigo origen (ej. SCL, MAD): "); scanf("%9s", origen);
                printf("Codigo destino: "); scanf("%9s", destino);
                printf("Duracion (minutos): ");
                while (scanf("%d", &duracion) != 1) {
                    printf("Error. Ingrese un numero válido para la duración: ");
                }
                printf("Horario (ej. 14:30): "); 
                scanf("%9s", horario);                
                agregarVuelo(grafo, origen, destino, duracion, horario);
                break;
            }
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;
            default:
                printf("\nError: Opcion no válida. Ingrese un número del 1 al 5.\n");
        }
    } while (opcion != '5');
    return 0;
}