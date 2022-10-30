#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colacp.h"

#define LONGITUD_NOMBRE 50

typedef struct ciudad {
    char * nombre;
    float pos_x;
    float pos_y;
} * TCiudad;

int fCompararCiudades(TEntrada c1, TEntrada c2){

    int X1, X2, Y1, Y2;
    
    return 0;
}

/**
    Permite visualizar el listado de todas las ciudades a visitar,
    ordenadas de forma ascendente en funci�n de la distancia que
    existe entre la ubicaci�n de estas ciudades y la ubicacion actual
    del usuario.

    |X2 − X1| + |Y2 − Y1|

    la prioridad es la distancia de esa ciudad a la ciudad de origen, se muestran desde la que tiene menos prioridad a la que tiene mas
*/
void mostrarAscendente(TColaCP cola_ciudades){
    TCiudad ciudad_actual;
    int numero_ciudad = 1;

    while(cola_ciudades -> cantidad_elementos != 0) {
        ciudad_actual = cola_ciudades -> raiz -> entrada -> valor;
        printf("%i. %s.", numero_ciudad, ciudad_actual -> nombre);
        cp_eliminar(cola_ciudades);
        numero_ciudad++;
    }
   //TODO hay que liberar el espacio de la cola??   
}

/**
    Permite visualizar el listado de todas las ciudades a visitar,
    ordenadas de forma descendente en funci�n de la distancia que
    existe entre la ubicaci�n de estas ciudades y la ubicacion actual
    del usuario.

    la prioridad es la distancia de esa ciudad a la ciudad de origen, se muestran desde la que tiene mas prioridad a la que tiene menos
*/

void mostrarDescendente(TColaCP cola_ciudades){
  
    TCiudad ciudad_actual;
    char * nombre_ciudad = malloc(LONGITUD_NOMBRE * sizeof(char));

    if(cola_ciudades -> cantidad_elementos > 0) {
        ciudad_actual = cola_ciudades -> raiz -> entrada -> valor;
        strcpy(nombre_ciudad, ciudad_actual -> nombre);
        cp_eliminar(cola_ciudades);
        mostrarDescendente(cola_ciudades);
        printf("%i. %s.", cola_ciudades -> cantidad_elementos, ciudad_actual -> nombre);
    }

    free(nombre_ciudad);
}

/**
void mostrarDescendente(TColaCP cola_ciudades) {
    if(cola_ciudades -> cantidad_elementos != 0)
        mostrarDescendenteAux(cola_ciudades, cola_ciudades -> cantidad_elementos);
}
*/

/**
    Permite visualizar un listado con el orden en el que todas
    las ciudades a visitar deben ser visitadas de forma tal que
    el usuario ubicado en una ciudad de origen, conduzca siempre
    a la proxima ciudad mas cercana al origen.
    Se indica la distancia total recorrida con esta planificaci�n.

    la prioridad es la distancia a la ultima ciudad insertada, empezando por la original y recorriendo todas guardando la mas cercana, 
    podria usar opcionalmente una lista para ir sacandolas de ahi pero no se si se puede, para no recorrer lo que ya inserte
    se muestran en orden descendente
*/
void ReducirHorasManejo(FILE *archivo){

}

TColaCP obtenerCiudades(char * ruta_archivo){
    FILE * archivo;
    int linea;
    char * palabra = malloc(LONGITUD_NOMBRE * sizeof(char)), caracterActual;

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
    FILE * archivo; //ubicaci�n actual del usuario

    ruta_archivo = argv[1];

    TColaCP cp = obtenerCiudades(ruta_archivo);

    printf("Archivo leido\n");
    printf("\n");

    printf("------- MEN� DE OPERACIONES -------");

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
                cp = obtenerCiudades(ruta_archivo);
                mostrarAscendente(cp);
                break;
            case 2:
                cp = obtenerCiudades(ruta_archivo);
                mostrarDescendente(cp);
                break;
            case 3:
                cp = obtenerCiudades(ruta_archivo);  
                ReducirHorasManejo(cp);
                break;
        }

        printf("�Desea realizar otra operacion? \n");
        printf(" SI (1) | NO (0)" );
        scanf("%d",&opcion);
        if(opcion == TRUE){
            printf("------- MEN� DE OPERACIONES -------");

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



