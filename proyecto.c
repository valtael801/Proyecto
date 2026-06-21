
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDAs/extra.h"
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
typedef struct Ruta{
    List* escalasVist; 
    int tiempoTotal;
    int escalasT;
} Ruta;
 
// Estructura física auxiliar requerida para el algoritmo de Dijkstra
typedef struct elementoCola{
    char codigoIATA[4];
    int distanciaA;
}elementoCola;

//Estructura física auxiliar para almacenar información de cada nodo durante la ejecución de Dijkstra
typedef struct datoDijkstra {
    int distancia;
    char anterior[4];
    int visitado;
} datoDijkstra;
 
// Función para que el mapa sepa comparar textos
int isEqualS(void *key1, void *key2){
    if (strcmp((char*)key1, (char*)key2) == 0) {
        return 1; 
    }
    return 0; 
}
 
// Función auxiliar: busca un aeropuerto por código y devuelve el puntero real a la entidad 
aeropuerto* buscarAero(grafoVuelo* grafo, char* codigo){
    MapPair* resultado = map_search(grafo->aeropuertos, codigo);
    if(resultado == NULL) return NULL;
    return (aeropuerto*)resultado->value;
}
 
// Crea una nueva entidades y lo añade a la red
void agregarAeropuerto(grafoVuelo* grafo, char* codigo, char* nombre, char* ciudad, char* pais){
    if(buscarAero(grafo, codigo) != NULL) {
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
void agregarVuelo(grafoVuelo* grafo, char* origen, char* destino, int duracion, int horaSalida){
    aeropuerto* aeroO = buscarAero(grafo, origen);
    aeropuerto* aeroD = buscarAero(grafo, destino);
 
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
 
// Buscar un aeropuerto por su código IATA
void buscarAeropuerto(grafoVuelo* grafo, char* codigo){
    aeropuerto* aero = buscarAero(grafo, codigo);
    if(aero == NULL){
        printf("Error: Aeropuerto %s NO encontrado.\n", codigo);
        return;
    }
 
    printf("\n--- INFORMACION AEROPUERTO ---\n");
    printf("Codigo IATA: %s\n", aero->codigo);
    printf("Nombre: %s\n", aero->nombre);
    printf("Ciudad: %s\n", aero->ciudad);
    printf("Pais: %s\n", aero->pais);
}
 
// Mostrar un listado simple de los aeropuertos registrados
void visualizarAeropuertos(grafoVuelo* grafo){
    printf("\n--- LISTA DE AEROPUERTOS REGISTRADOS ---\n");
    MapPair* parActual = map_first(grafo->aeropuertos);
    if(parActual == NULL){
        printf("No hay aeropuertos registrados.\n");
        return;
    }
 
    while(parActual != NULL){
        aeropuerto* aeroActual = (aeropuerto*)parActual->value;
        printf("- %s. %s (%s, %s)\n", aeroActual->codigo, aeroActual->nombre, aeroActual->ciudad, aeroActual->pais);
        parActual = map_next(grafo->aeropuertos);
    }
}
 
void visualizarRed(grafoVuelo* grafo){
    printf("\n========================================\n");
    printf("        RED DE VUELOS REGISTRADOS        \n");
    printf("========================================\n");

    MapPair* parActual = map_first(grafo->aeropuertos);
    if(parActual == NULL){
        printf("No hay aeropuertos registrados.\n");
        return;
    }

    while(parActual != NULL){
        aeropuerto* aeroActual = (aeropuerto*)parActual->value;
        printf("\nAeropuerto: %s (%s, %s)\n", aeroActual->nombre, aeroActual->ciudad, aeroActual->pais);
        
        vuelo* vueloActual = (vuelo*)list_first(aeroActual->lVuelos);
        if(vueloActual == NULL) printf("- No hay vuelos registrados desde este aeropuerto.\n");

        while(vueloActual != NULL){
            int horasDuracion = vueloActual->duracion / 60;
            int minDuracion = vueloActual->duracion % 60;
            int horaSalidaVista = vueloActual->horaSalida / 100;
            int minSalidaVista = vueloActual->horaSalida % 100;

            printf(" - Destino: %s | Duracion: %dh %0dm | Salida: %02d:%02d hrs\n", vueloActual->destino, horasDuracion, minDuracion, horaSalidaVista, minSalidaVista);
            vueloActual = (vuelo*)list_next(aeroActual->lVuelos);
        }
        printf("----------------------------------------\n");
        parActual = map_next(grafo->aeropuertos);
    }
}

void mostrarSubCaso1(grafoVuelo* grafo){
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
}

void mostrarSubCaso2(grafoVuelo* grafo){
    char codigoB[4];
    printf("\n--- BUSCAR AEROPUERTO ---\n");
    printf("Ingrese codigo IATA a buscar: ");
    scanf("%3s", codigoB);
    buscarAeropuerto(grafo, codigoB);
}

void mostrarCaso2(grafoVuelo* grafo){
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
}

void subMenuAero(grafoVuelo* grafo){
    char subOpcion = 0;
    do{
        printf("\n--- GESTION DE AEROPUERTOS ---\n");
        printf("1. Agregar Aeropuerto\n");
        printf("2. Buscar Aeropuerto\n");
        printf("3. Visualizar Aeropuertos\n");
        printf("4. Volver al Menu Principal\n");
        printf("Seleccione una opcion: ");
 
        if (scanf(" %c", &subOpcion) != 1) subOpcion = '0';
 
        switch (subOpcion) {
            case '1': {
                mostrarSubCaso1(grafo);
                break;
            }
            case '2':{
                mostrarSubCaso2(grafo);
                break;
            }
            case '3':{
                visualizarAeropuertos(grafo);
                break;
            }
            case '4':{
                printf("\nVolviendo al menu principal\n");
                break;
            }
            default:
                printf("\nError: Opcion no valida. Ingrese un numero del 1 al 4.\n"); 
        }
        if (subOpcion != '4') presioneTeclaParaContinuar();
    }while (subOpcion != '4');
}

void mostrarCaso4(grafoVuelo* grafo){
    char origen[4];
    char destino[4];

    printf("\n--- BUSCAR RUTA OPTIMA ---\n");

    printf("Ingrese codigo IATA de origen: ");
    scanf("%3s", origen);

    printf("Ingrese codigo IATA de destino: ");
    scanf("%3s", destino);

    aeropuerto* aeroOrigen = buscarAero(grafo, origen);
    aeropuerto* aeroDestino = buscarAero(grafo, destino);

    if(aeroOrigen == NULL || aeroDestino == NULL){
        printf("Error: Aeropuerto no encontrado.\n");
        return;
    }

    printf("Origen: %s\n", origen);
    printf("Destino: %s\n", destino);
    printf("La busqueda de ruta optima aun esta en desarrollo.\n");
}
 
int main() {
    grafoVuelo* grafo = (grafoVuelo*)malloc(sizeof(grafoVuelo));
    grafo->aeropuertos = map_create(isEqualS);
    char opcion;
    do {
        printf("\n========================================\n");
        printf("    SISTEMA DE GESTION DE VUELOS        \n");
        printf("========================================\n");
        printf("1. Aeropuerto\n");
        printf("2. Agregar Vuelo\n");
        printf("3. Visualizar Red\n");
        printf("4. Buscar Ruta Optima\n");
        printf("5. Salir\n");
        printf("========================================\n");
        printf("Seleccione una opcion: ");
 
        if (scanf(" %c", &opcion) != 1) opcion = '0';
 
        switch (opcion) {
            case '1': {
                subMenuAero(grafo);
                break;
            }
            case '2': {
                mostrarCaso2(grafo);
                break;
            }
            case '3':{
                visualizarRed(grafo);
                break;
            }
            case '4':{
                mostrarCaso4(grafo);
                break;
            }
            case '5':
                break;
            default:
                printf("\nError: Opcion no valida. Ingrese un numero del 1 al 5.\n");
        }
        if (opcion != '1' && opcion != '5') {
            presioneTeclaParaContinuar();
        }
    } while (opcion != '5');
    return 0;
}