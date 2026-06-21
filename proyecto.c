#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDAs/list.h"
#include "TDAs/map.h"
#include "TDAs/heap.h"

// Representa una "arista" en el grafo
typedef struct vuelo{
    char origen[4];
    char destino[4];
    int duracion;
    int horaSalida;
}vuelo;

// Representa "entidades" en el grafo
typedef struct aeropuerto{
    char codigo[4];
    char nombre[50];
    char ciudad[50];
    char pais[50];
    List* lVuelos; // Lista de adyacencia: guarda todos los vuelos que salen de aquí
}aeropuerto;

// Estructura principal que encapsula toda la red
typedef struct grafoVuelo{
    Map* aeropuertos; // Mapa central para buscar entidades 
}grafoVuelo;

// Estructura utilizada para empaquetar y devolver el resultado de una búsqueda
typedef struct Ruta {
    List* escalasVist; 
    int tiempoTotal;
    int escalasT;
} Ruta;

// Estructura física auxiliar requerida para el algoritmo de Dijkstra
typedef struct elementoCola{
    char codigoIATA[4];
    int distanciaA;
}elementoCola;

// Función para que el mapa sepa comparar textos
int isEqualS(void *key1, void *key2) {
    if (strcmp((char*)key1, (char*)key2) == 0) {
        return 1; 
    }
    return 0; 
}

// Crea una nueva entidades y lo añade a la red
void agregarAeropuerto(grafoVuelo* grafo, char* codigo, char* nombre, char* ciudad, char* pais) {
    if(map_search(grafo->aeropuertos, codigo) != NULL) {
        printf("Error: El aeropuerto %s ya existe.\n", codigo);
        return;
    }

    aeropuerto* nuevoAero = (aeropuerto*)malloc(sizeof(aeropuerto));
    strcpy(nuevoAero->codigo, codigo);
    strcpy(nuevoAero->nombre, nombre);
    strcpy(nuevoAero->ciudad, ciudad);
    strcpy(nuevoAero->pais, pais);
    nuevoAero->lVuelos = list_create();
    map_insert(grafo->aeropuertos, nuevoAero->codigo, nuevoAero);
    printf("Aeropuerto %s registrado con exito.\n", codigo);
}

// Crea una nueva arista dirigida entre dos vértices
void agregarVuelo(grafoVuelo* grafo, char* origen, char* destino, int duracion, int horaSalida) {
    aeropuerto* aeroO = (aeropuerto*)map_search(grafo->aeropuertos, origen);
    aeropuerto* aeroD = (aeropuerto*)map_search(grafo->aeropuertos, destino);

    if (aeroO == NULL || aeroD == NULL) {
        printf("Error: Aeropuerto NO encontrado.\n");
        return;
    }

    vuelo* nuevoVuelo = (vuelo*)malloc(sizeof(vuelo));
    strcpy(nuevoVuelo->origen, origen);
    strcpy(nuevoVuelo->destino, destino);
    nuevoVuelo->duracion = duracion;
    nuevoVuelo->horaSalida = horaSalida;
    list_pushBack(aeroO->lVuelos, nuevoVuelo);

    printf("Vuelo registrado con exito.\n");
}


int main() {
    grafoVuelo* grafo = (grafoVuelo*)malloc(sizeof(grafoVuelo));
    grafo->aeropuertos = map_create(isEqualS);
    int opcion;
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
                char codigo[4];
                char nombre[50];
                char ciudad[50];
                char pais[50];

                printf("\n--- REGISTRAR NUEVO AEROPUERTO ---\n");
                printf("Ingrese código IATA (3 letras ej: SCL, BOG): ");
                scanf("%3s", codigo);

                printf("Ingrese nombre del aeropuerto: ");
                scanf(" %49[^\n]", nombre);

                printf("Ingrese ciudad: ");
                scanf(" %49[^\n]", ciudad);

                printf("Ingrese pais: ");
                scanf(" %49[^\n]", pais);

                agregarAeropuerto(grafo, codigo, nombre, ciudad, pais);
                break;
            }
            case '2': {
                char origen[4];
                char destino[4];
                int horarioSalida = 0;
                int duracionTotal = 0;

                int hora = 0;
                int minuto = 0;
                int datosLeidos;
                
                printf("\n--- REGISTRAR NUEVO VUELO ---\n");
                printf("Ingrese codigo IATA de origen: ");
                scanf("%3s", origen);

                printf("Ingrese codigo IATA de destino: ");
                scanf("%3s", destino);

                printf("Duracion ej: hora exacta -> 12 || hora+minutos -> 12:45\n");
                printf("Ingrese la duracion: ");
                datosLeidos = scanf("%d:%d", &hora, &minuto);

                if(datosLeidos == 2 || datosLeidos ==1) duracionTotal = (hora * 60) + minuto;
                else printf("Error de formato.\n");

                printf("Horario de salida ej: hora exacta -> 12 || hora+minutos -> 12:45\n");
                printf("Ingrese el horario de salida: ");
                hora = minuto = 0;
                datosLeidos = scanf("%d:%d", &hora, &minuto);

                if(datosLeidos == 2 || datosLeidos ==1) horarioSalida = (hora * 100) + minuto;
                else printf("Error de formato.\n");

                agregarVuelo(grafo, origen, destino, duracionTotal, horarioSalida);
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