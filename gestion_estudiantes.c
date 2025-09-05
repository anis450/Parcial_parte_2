#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *nombre;
    char *apellido;
    unsigned int edad : 7;   
    unsigned int id;
    float *calificaciones;
    int numMaterias;
} Estudiante;


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


void liberarEstudiante(Estudiante *e) {
    if (e) {
        free(e->nombre);
        free(e->apellido);
        free(e->calificaciones);
        free(e);
    }
}


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
