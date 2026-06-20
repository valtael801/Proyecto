#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDAs/list.h"
#include "TDAs/map.h"
#include "TDAs/heap.h"

typedef struct Vuelo{
    char destino[10];
    int duracion;
    char horario[10];
}Vuelo;

typedef struct Aeropuerto{
    char codigo[10];
    List* lVuelos;
}Aeropuerto;

typedef struct grafoVuelo{
    Map* aeropuertos;
}grafoVuelo;

typedef struct Ruta {
    List* escalas; 
    int tiempoTotal;
} Ruta;

void agregarAeropuerto(grafoVuelo* grafo, char* codigo) {
    Aeropuerto* nuevoAero = (Aeropuerto*)malloc(sizeof(Aeropuerto));
    strcpy(nuevoAero->codigo, codigo);
    nuevoAero->lVuelos = createList(); 
    insertMap(grafo->aeropuertos, nuevoAero->codigo, nuevoAero); 
    printf("-> Aeropuerto %s registrado con éxito.\n", codigo);
}

void agregarVuelo(grafoVuelo* grafo, char* origen, char* destino, int duracion, char* horario) {
    Aeropuerto* aeroO = (Aeropuerto*)searchMap(grafo->aeropuertos, origen);
    if (aeroO == NULL) {
        printf("Error: El aeropuerto %s no existe en la red.\n", origen);
        return;
    }
    Vuelo* nuevoVuelo = (Vuelo*)malloc(sizeof(Vuelo));
    strcpy(nuevoVuelo->destino, destino);
    nuevoVuelo->duracion = duracion;
    strcpy(nuevoVuelo->horario, horario);
    pushBack(aeroO->lVuelos, nuevoVuelo); 
    printf("Vuelo de %s a %s registrado con éxito.\n", origen, destino);
}


int main() {
    grafoVuelo* grafo = (grafoVuelo*)malloc(sizeof(grafoVuelo));
    grafo->aeropuertos = createMap(); 

    int opcion;
    char entrada[10];

    do {
        printf("\n========================================\n");
        printf("    SISTEMA DE GESTIÓN DE VUELOS        \n");
        printf("========================================\n");
        printf("1. Agregar Aeropuerto\n");
        printf("2. Agregar Vuelo\n");
        printf("3. Visualizar Red\n");
        printf("4. Buscar Ruta Óptima (Dijkstra)\n");
        printf("5. Salir\n");
        printf("========================================\n");
        printf("Seleccione una opción: ");

        if (scanf(" %c", &opcion) != 1) opcion = '0';

        switch (opcion) {
            case 1: {
                char codigo[10];
                printf("Ingrese código del aeropuerto (ej. MIA, LIM): ");
                scanf("%9s", codigo);
                agregarAeropuerto(grafo, codigo);
                break;
            }
            case 2: {
                char origen[10], destino[10], horario[10];
                int duracion;
                printf("Código origen (ej. SCL, MAD): "); scanf("%9s", origen);
                printf("Código destino: "); scanf("%9s", destino);
                printf("Duración (minutos): ");
                while (scanf("%d", &duracion) != 1) {
                    printf("Error. Ingrese un número válido para la duración: ");
                }
                printf("Horario (ej. 14:30): "); 
                scanf("%9s", horario);                
                agregarVuelo(grafo, origen, destino, duracion, horario);
                break;
            }
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            default:
                printf("\nError: Opción no válida. Ingrese un número del 1 al 5.\n");
        }
    } while (opcion != 5);
    return 0;
}