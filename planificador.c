#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colacp.h"

typedef struct ciudad {
    char * nombre;
    float pos_x;
    float pos_y;
} * TCiudad;

int fCompararCiudades(TEntrada c1, TEntrada c2){

    return 0;
}

/**
    Permite visualizar el listado de todas las ciudades a visitar,
    ordenadas de forma ascendente en función de la distancia que
    existe entre la ubicación de estas ciudades y la ubicacion actual
    del usuario.
*/
void mostrarAscendente(){

}

/**
    Permite visualizar el listado de todas las ciudades a visitar,
    ordenadas de forma descendente en función de la distancia que
    existe entre la ubicación de estas ciudades y la ubicacion actual
    del usuario.
*/
void mostrarDescendente(){

}

/**
    Permite visualizar un listado con el orden en el que todas
    las ciudades a visitar deben ser visitadas de forma tal que
    el usuario ubicado en una ciudad de origen, conduzca siempre
    a la proxima ciudad mas cercana al origen.
    Se indica la distancia total recorrida con esta planificación.
*/
void ReducirHorasManejo(){

}

TColaCP obtenerCiudades(char * ruta_archivo){
    FILE * archivo;
    int linea;
    char * palabra = malloc(50 * sizeof(char)), caracterActual;

    TCiudad c;
    TEntrada entry;
    TColaCP cp = crear_cola_cp( &fCompararCiudades );

    archivo = fopen(ruta_archivo,"r");

 /*   linea = 1;

    while((caracterActual = fgetc(archivo)) != EOF ){

        if(linea == 1 && caracterActual != ';'){
            entry = malloc(sizeof(struct entrada));
            c = malloc(sizeof(struct ciudad));
            c -> nombre = ELE_NULO;
            c -> pos_x = (int) * palabra;
        }

    }*/ //se me quemo el cerebro jajja

    fclose(archivo);

    return cp;

}

int main(int argc, char *argv[]){

    int opcion;
    char * ruta_archivo;
    FILE * archivo; //ubicación actual del usuario

    ruta_archivo = argv[1];

    TColaCP cp = obtenerCiudades(ruta_archivo);

    printf("Archivo leido\n");
    printf("\n");

    printf("------- MENÚ DE OPERACIONES -------");

    printf("1. Mostrar Ascendente \n");
    printf("2. Mostrar Descendente \n");
    printf("3. Reducir horas de manejo \n");
    printf("4. Salir \n");
    printf("\n");
    printf("Ingrese opcion (1-4): ");

    scanf("%d",&opcion);

    while(opcion == 1 || opcion == 2 || opcion == 2){

        printf("\n");
        switch(opcion){
            case 1:
                mostrarAscendente();
                break;
            case 2:
                mostrarDescendente();
                break;
            case 3:
                ReducirHorasManejo();
                break;
        }

        printf("¿Desea realizar otra operacion? \n");
        printf(" SI (1) | NO (0)" );
        scanf("%d",&opcion);
        if(opcion == TRUE){
            printf("------- MENÚ DE OPERACIONES -------");

            printf("1. Mostrar Ascendente \n");
            printf("2. Mostrar Descendente \n");
            printf("3. Reducir horas de manejo \n");
            printf("4. Salir \n");
            printf("\n");
            printf("Ingrese opcion (1-4): ");

            scanf("%d",&opcion);
        }

    }


    return 0;

}



