# ✈️ Optimización de Itinerarios de Viaje

## 📖 Descripción

Este proyecto consiste en una aplicación desarrollada en lenguaje C cuyo objetivo es encontrar la ruta aérea de menor duración entre dos aeropuertos.

Para representar el problema se modela una red de vuelos donde cada aeropuerto corresponde a un nodo y cada vuelo a una conexión entre ellos. A partir de esta estructura, el sistema es capaz de analizar las rutas disponibles y determinar automáticamente cuál es la alternativa más conveniente para el usuario.

La solución fue desarrollada utilizando distintos Tipos de Datos Abstractos vistos durante el curso:

* 🗺️ **Mapa:** almacena la información de los aeropuertos utilizando el código IATA como identificador único.
* 🌐 **Grafo Dirigido Ponderado:** representa la red de vuelos y las conexiones entre aeropuertos.
* ⚡ **Cola de Prioridad:** apoya la ejecución del algoritmo de búsqueda.
* 📍 **Algoritmo de Dijkstra:** permite calcular la ruta de menor duración entre un origen y un destino.

---

## 🛠️ Compilación y ejecución

### 1. Clonar o descargar el proyecto

Descargue el repositorio o el archivo comprimido y descomprímalo en una carpeta de su preferencia.

### 2. Abrir el proyecto

Abra la carpeta del proyecto utilizando Visual Studio Code.

### 3. Compilar

Abra una terminal dentro de la carpeta principal y ejecute:

```bash
gcc proyecto.c TDAs/*.c -o proyecto
```

### 4. Ejecutar

```bash
./proyecto
```

---

## 📋 Funcionalidades principales

### ✈️ Gestión de Aeropuertos

Permite registrar, buscar y visualizar aeropuertos dentro del sistema.

Cada aeropuerto almacena:

* Código IATA
* Nombre
* Ciudad
* País

Además, se valida que cada código IATA sea único dentro de la red.

---

### 🛫 Gestión de Vuelos

Permite registrar conexiones entre aeropuertos.

Para cada vuelo se almacena:

* Aeropuerto de origen
* Aeropuerto de destino
* Duración del vuelo
* Horario de salida

Antes de registrar un vuelo se verifica que ambos aeropuertos existan previamente en el sistema.

---

### 🔎 Búsqueda de Ruta Óptima

Implementa el algoritmo de Dijkstra para encontrar el trayecto de menor duración entre dos aeropuertos.

Como resultado se obtiene:

* Ruta encontrada
* Tiempo total de viaje
* Cantidad de escalas realizadas

---

### 🌐 Visualización de la Red

Muestra todos los aeropuertos registrados y sus conexiones disponibles.

Esta funcionalidad permite verificar visualmente la estructura completa de la red aérea construida por el usuario.

---

## 💻 Ejemplo de uso

### Paso 1: Registrar aeropuertos

Ingresar los siguientes aeropuertos:

```text
SCL - Santiago, Chile
LIM - Lima, Perú
BOG - Bogotá, Colombia
```

Resultado:

```text
Aeropuerto registrado con éxito.
```

---

### Paso 2: Registrar vuelos

```text
Origen: SCL
Destino: LIM
Duración: 4 horas
Salida: 08:30
```

```text
Origen: LIM
Destino: BOG
Duración: 3 horas
Salida: 14:15
```

Resultado:

```text
Vuelo registrado con éxito.
```

---

### Paso 3: Buscar ruta óptima

Entrada:

```text
Origen: SCL
Destino: BOG
```

Salida:

```text
Ruta encontrada:
SCL → LIM → BOG

Tiempo total: 7 horas
Escalas: 1
```

---

### Paso 4: Visualizar red

Salida de ejemplo:

```text
Aeropuerto: Arturo Merino Benítez (Santiago, Chile)
Destino: LIM | Duración: 4h | Salida: 08:30

Aeropuerto: Jorge Chávez (Lima, Perú)
Destino: BOG | Duración: 3h | Salida: 14:15
```

---

## 📊 Complejidades consideradas

| Operación                     | Complejidad |
| ----------------------------- | ----------- |
| Buscar aeropuerto             | O(n)        |
| Registrar aeropuerto          | O(n)        |
| Registrar vuelo               | O(n)        |
| Visualizar red                | O(n + m)    |
| Buscar ruta óptima (Dijkstra) | O(m · n)    |

Donde:

* **n** corresponde a la cantidad de aeropuertos.
* **m** corresponde a la cantidad de vuelos registrados.

---

## 👩‍💻 Integrantes

* Renata Gallardo
* Benjamín Vera
* Nicolás Gaete
* Cristian Baeza

Pontificia Universidad Católica de Valparaíso
Estructuras de Datos – 2026
