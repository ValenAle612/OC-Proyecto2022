#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colacp.h"

// Macros con códigos de finalización
#define LONGITUD_NOMBRE               50
#define ERROR_APERTURA_ARCHIVO        -1
#define ERROR_INVOCACION_PROGRAMA     -2

typedef struct ciudad {
    char * nombre;
    float pos_x;
    float pos_y;
} * TCiudad;

TCiudad ubicacionActual;//ubicacion actual del usuario


int fCompararCiudades(TEntrada e1, TEntrada e2){

    int prioridad = 0;
    float c1, c2;

    c1 = *(float*)( e1 -> clave );
    c2 = *(float*)( e2 -> clave );

    if(c1 > c2){
        prioridad = -1;
    }else
        if(c1 < c2)
            prioridad = 1;

    return prioridad;
}

void fEliminarCiudades (TEntrada e) {

    TCiudad ciudad_actual;
    ciudad_actual = e -> valor;
    free(e -> clave);
    free(ciudad_actual -> nombre);
    free(ciudad_actual);

}

/**
    Permite visualizar el listado de todas las ciudades a visitar,
    ordenadas de forma ascendente en función de la distancia que
    existe entre la ubicación de estas ciudades y la ubicacion actual
    del usuario.
*/
void mostrarAscendente(TColaCP cp){

    TEntrada e_aux;
    TCiudad c;
    int index;

    printf("\tMOSTRAR ASCENDENTE:\n\n");

    index = 1;
    while(cp_cantidad(cp) > 0){

        e_aux = cp_eliminar(cp);
        c = (TCiudad) e_aux->valor;

        printf("\t%d. %s \n",index,c->nombre);
        fEliminarCiudades(e_aux);
        index++;
    }

    printf("\n");
}

/**
    Permite visualizar el listado de todas las ciudades a visitar,
    ordenadas de forma descendente en función de la distancia que
    existe entre la ubicación de estas ciudades y la ubicacion actual
    del usuario.
*/
void mostrarDescendente(TColaCP cp){

    int cantidad_elementos;
    TEntrada entrada_actual;
    TCiudad ciudad_actual;
    char * nombre_ciudad;

    if(cp_cantidad(cp) > 0) {

        nombre_ciudad = malloc(LONGITUD_NOMBRE * sizeof(char));

        cantidad_elementos = cp_cantidad(cp);
        entrada_actual = cp_eliminar(cp);
        ciudad_actual = entrada_actual -> valor;
        strcpy(nombre_ciudad, ciudad_actual -> nombre);
        mostrarDescendente(cp);

        printf("\t%i. %s.\n", cantidad_elementos, ciudad_actual -> nombre);

        fEliminarCiudades(entrada_actual);
    }
    else {
        printf("\tMOSTRAR DESCENDENTE:\n\n");
    }
}

/**
    Permite visualizar un listado con el orden en el que todas
    las ciudades a visitar deben ser visitadas de forma tal que
    el usuario ubicado en una ciudad de origen, conduzca siempre
    a la proxima ciudad mas cercana al origen.
    Se indica la distancia total recorrida con esta planificación.
*/
void ReducirHorasManejo(TColaCP cp){

    float distanciaTotal;
    int index;
    TEntrada e_aux;
    TCiudad c, anterior;

    printf("\tREDUCIR HORAS MANEJO:\n\n");

    anterior = ubicacionActual;
    distanciaTotal = 0;
    index = 1;

    while(cp_cantidad(cp) > 0){

        e_aux = cp_eliminar(cp);
        c = (TCiudad)e_aux -> valor;

        printf("\t%d. %s \n",index,c->nombre);

        distanciaTotal += ( c->pos_x - anterior -> pos_x ) + ( c->pos_y - anterior->pos_y );

        anterior = c;
        fEliminarCiudades(e_aux);
        index++;
    }
    printf("\n\tDISTANCIA TOTAL RECORRIDA: %f \n",distanciaTotal);

}

TColaCP obtenerCiudades(FILE * archivo){

    TCiudad c;
    TEntrada entry;
    TColaCP cp;

    float x, y;
    char ciudad[255];

    fseek(archivo, 0, SEEK_SET);

    cp = crear_cola_cp( &fCompararCiudades );
    fscanf(archivo,"%f;%f\n",&x,&y);//ubicación actual del usuario
    ubicacionActual -> pos_x = x;
    ubicacionActual -> pos_y = y;


    while(!feof(archivo)){

        fscanf(archivo,"%[^;];", ciudad);
        fscanf(archivo,"%f;", &x);
        fscanf(archivo,"%f\n",&y);

        c = (TCiudad) malloc(sizeof(struct ciudad));
        c->nombre = malloc(sizeof(char)*50);
        strcpy(c->nombre, ciudad);
        c -> pos_x = x;
        c -> pos_y = y;

        entry = (TEntrada) malloc(sizeof(struct entrada));
        entry -> clave = malloc(sizeof(int));
        *(float*)entry -> clave = ((x - ubicacionActual->pos_x) + (y - ubicacionActual->pos_y));
        entry -> valor = c;

        cp_insertar(cp,entry);
    }

    return cp;

}

int planificador(FILE *archivo){

    TColaCP cola;
    int opcion;

    printf("Archivo leido\n\n");
    ubicacionActual = malloc(sizeof(struct ciudad)); //agregado desp

    do {
        printf("\n------- MENU DE OPERACIONES -------\n\n");
        printf("1. Mostrar Ascendente \n");
        printf("2. Mostrar Descendente \n");
        printf("3. Reducir horas de manejo \n");
        printf("4. Salir \n\n");
        printf("Ingrese opcion (1-4): ");

        fflush(stdin);
        scanf("%d",&opcion);

        cola = obtenerCiudades(archivo);
        printf(" \n");

        switch(opcion){
            case 1:
                mostrarAscendente(cola);
                break;
            case 2:
                mostrarDescendente(cola);
                break;
            case 3:
                ReducirHorasManejo(cola);
                break;
            case 4:
                printf("\nGRACIAS, VUELVA PRONTOS\n");
                break;
            default:
                printf("OPCION INVALIDA; INTENTE NUEVAMENTE\n");
            break;
        }
        cp_destruir(cola,&fEliminarCiudades);

    } while(opcion != 4);


    free(ubicacionActual);
    fclose(archivo);

    return 0;

}

int main(int argc, char *argv[]){

    FILE *archivo;

    if(argc != 2) {
        printf("ERROR: Cantidad de argumentos equivocado");
        return ERROR_INVOCACION_PROGRAMA;
    }

    archivo = fopen(argv[1],"r");

    if(archivo == NULL) {
        printf("ERROR: Archivo no encontrado");
        return ERROR_APERTURA_ARCHIVO;
    }

    return planificador(archivo);
}


