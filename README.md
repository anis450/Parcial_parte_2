# Sistema de Gestión de Estudiantes en C con Memoria Dinámica

Este proyecto implementa un sistema básico de gestión de estudiantes en C, utilizando memoria dinámica para optimizar el uso de recursos al almacenar registros.

## Objetivo
- Gestionar registros de estudiantes de forma dinámica y eficiente.
- Optimizar el espacio usado, evitando desperdicio de memoria.
- Permitir crear y liberar estudiantes sin fugas de memoria.

## Características del Programa
1. Uso de memoria dinámica con `malloc` y `free`.
2. Cada registro contiene:
   - Nombre y apellido (`char*` dinámicos).
   - Edad (optimizada con *bitfields*).
   - ID (entero único).
   - Calificaciones (array dinámico `float*`).
3. Funciones auxiliares:
   - `crearEstudiante`: asigna memoria y construye un registro.
   - `liberarEstudiante`: libera toda la memoria ocupada por un estudiante.
   - `mostrarEstudiante`: imprime la información y sus calificaciones.

## Código Principal

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *nombre;
    char *apellido;
    unsigned int edad : 7;   // Optimizado con bitfield (0-127 años)
    unsigned int id;
    float *calificaciones;
    int numMaterias;
} Estudiante;

// Crear estudiante dinámicamente
Estudiante *crearEstudiante(const char *nombre, const char *apellido, 
                            int edad, unsigned int id, float *notas, int numMaterias) {
    Estudiante *e = (Estudiante *)malloc(sizeof(Estudiante));
    if (!e) {
        fprintf(stderr, "Error: no se pudo asignar memoria para el estudiante.\n");
        exit(EXIT_FAILURE);
    }

    e->nombre = (char *)malloc(strlen(nombre) + 1);
    e->apellido = (char *)malloc(strlen(apellido) + 1);
    if (!e->nombre || !e->apellido) {
        fprintf(stderr, "Error: no se pudo asignar memoria para cadenas.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(e->nombre, nombre);
    strcpy(e->apellido, apellido);

    e->edad = edad;
    e->id = id;

    e->calificaciones = (float *)malloc(numMaterias * sizeof(float));
    if (!e->calificaciones) {
        fprintf(stderr, "Error: no se pudo asignar memoria para calificaciones.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < numMaterias; i++) {
        e->calificaciones[i] = notas[i];
    }
    e->numMaterias = numMaterias;

    return e;
}

// Liberar memoria de un estudiante
void liberarEstudiante(Estudiante *e) {
    if (e) {
        free(e->nombre);
        free(e->apellido);
        free(e->calificaciones);
        free(e);
    }
}

// Mostrar datos de un estudiante
void mostrarEstudiante(Estudiante *e) {
    printf("Estudiante: %s %s, ID: %u, Edad: %u\n", 
           e->nombre, e->apellido, e->id, e->edad);
    printf("Notas: ");
    for (int i = 0; i < e->numMaterias; i++) {
        printf("%.2f ", e->calificaciones[i]);
    }
    printf("\n");
}

int main() {
    float notas1[] = {4.5, 3.8, 5.0};
    float notas2[] = {3.2, 4.0};

    Estudiante *e1 = crearEstudiante("Ana", "Hernandez", 20, 101, notas1, 3);
    Estudiante *e2 = crearEstudiante("Carlos", "Lopez", 21, 102, notas2, 2);

    mostrarEstudiante(e1);
    mostrarEstudiante(e2);

    liberarEstudiante(e1);
    liberarEstudiante(e2);

    return 0;
}
```

## Ejecución

1. Compilar el programa:
   ```bash
   gcc gestion_estudiantes.c -o gestion_estudiantes
   ```

2. Ejecutar:
   ```bash
   ./gestion_estudiantes
   ```

## Ejemplo de salida

```
Estudiante: Ana Hernandez, ID: 101, Edad: 20
Notas: 4.50 3.80 5.00 
Estudiante: Carlos Lopez, ID: 102, Edad: 21
Notas: 3.20 4.00
```

## Conclusiones
- El uso de memoria dinámica permite ajustar el tamaño exacto para cada registro.
- El empleo de bitfields ayuda a optimizar espacio en campos pequeños como edad.
- El sistema es extensible para manejar un conjunto mayor de estudiantes con `realloc` si se desea.
