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

TColaCP cp;//colacp global
TCiudad ubicacionActual;//ubicacion actual del usuario


int fCompararCiudades(TEntrada e1, TEntrada e2){

    int prioridad = 0;
    int c1, c2;

    c1 = ( e1 -> clave );
    c2 = ( e2 -> clave );

    if(c1 > c2){
        prioridad = -1;
    }else
        if(c1 < c2)
            prioridad = 1;

    return prioridad;
}
/*
int fCompararCiudadesInverso(TEntrada e1, TEntrada e2){
    int toReturn;
    toReturn = fCompararCiudades(e1,e2) * (-1);
    return toReturn;
}*/

void fEliminarCiudades(TEntrada e){
    TCiudad aux;
    aux = e -> clave;
    free(aux);
    aux = e -> valor;
    free(aux);
}
/*
void mostrarAscendente(TColaCP cola_ciudades){
    printf("entra a mostrar ascendente");
    TEntrada entrada_raiz;
    TCiudad ciudad_actual;
    int numero_ciudad = 1;

    while(cp_cantidad(cola_ciudades) != 0) {
        entrada_raiz = cp_eliminar(cola_ciudades);
        ciudad_actual = entrada_raiz -> valor;
        printf("%i. %s.\n", numero_ciudad, ciudad_actual -> nombre);
        numero_ciudad++;
    }
   //TODO hay que liberar el espacio de la cola??
}*/
/**
    Permite visualizar el listado de todas las ciudades a visitar,
    ordenadas de forma ascendente en función de la distancia que
    existe entre la ubicación de estas ciudades y la ubicacion actual
    del usuario.
*/
void mostrarAscendente(){
    TColaCP aux;
    TEntrada e_aux;
    TCiudad c;
    int index;

    printf("------- MOSTRAR ASCENDENTE -------\n");

    aux = crear_cola_cp( &fCompararCiudades );
    index = 1;

    while(cp_cantidad(cp) != 0){
        e_aux = cp_eliminar(cp);
        c = (TCiudad) e_aux->valor;

        printf("%d. %s \n",index,c->nombre);
        cp_insertar(aux,e_aux);

        index++;
    }

    cp_destruir(cp,&fEliminarCiudades);
    printf("\n");
    cp = aux;
}

/**
    Permite visualizar el listado de todas las ciudades a visitar,
    ordenadas de forma descendente en función de la distancia que
    existe entre la ubicación de estas ciudades y la ubicacion actual
    del usuario.
*/
void mostrarDescendente(){

    printf("------- MOSTRAR DESCENDENTE -------\n");

    int cantidad_elementos;
    TCiudad ciudad_actual;
    char * nombre_ciudad = malloc(LONGITUD_NOMBRE * sizeof(char));

    if(cp_cantidad(cp) > 0) {
        ciudad_actual = cp -> raiz -> entrada -> valor;
        strcpy(nombre_ciudad, ciudad_actual -> nombre);
        cantidad_elementos = cp_cantidad(cp);
        cp_eliminar(cp);
        mostrarDescendente();
        printf("%i. %s.\n", cantidad_elementos, ciudad_actual -> nombre);
    }
    free(nombre_ciudad);
}

/**
    Permite visualizar un listado con el orden en el que todas
    las ciudades a visitar deben ser visitadas de forma tal que
    el usuario ubicado en una ciudad de origen, conduzca siempre
    a la proxima ciudad mas cercana al origen.
    Se indica la distancia total recorrida con esta planificación.
*/
void ReducirHorasManejo(){
    int distanciaTotal, index;
    TColaCP aux;
    TEntrada e_aux;
    TCiudad c, anterior;

    aux = crear_cola_cp(&fCompararCiudades);
    anterior = ubicacionActual;
    distanciaTotal = 0;
    index = 0;

    while(cp_cantidad(cp) != 0){
        e_aux = cp_eliminar(cp);
        c = (TCiudad)e_aux -> valor;

        printf("%d. %s \n",index,c->nombre);

        distanciaTotal += ( c->pos_x - anterior -> pos_x ) + ( c->pos_y - anterior->pos_y );

        cp_insertar(aux,e_aux);

        anterior = c;
        index++;
    }

    printf(" DISTANCIA TOTAL RECORRIDA: %d. \n",distanciaTotal);


}

void obtenerCiudades(FILE * archivo){

    TCiudad c;
    TEntrada entry;

    int x, y;
    char ciudad[255];

    cp = crear_cola_cp( &fCompararCiudades );

    fscanf(archivo,"%d;%d\n",&x,&y);//ubicación actual del usuario

    ubicacionActual = malloc(sizeof(struct ciudad));
    ubicacionActual -> pos_x = x;
    ubicacionActual -> pos_y = y;


    while(!feof(archivo)){
        fscanf(archivo,"%[^;];", ciudad);
        fscanf(archivo,"%d;", &x);
        fscanf(archivo,"%d\n",&y);

        c = (TCiudad) malloc(sizeof(struct ciudad)); //en mostrar y reducir no olvidar de hacer free
        c->nombre = malloc(sizeof(char)*50);
        strcpy(c->nombre, ciudad);
        c -> pos_x = x;
        c -> pos_y = y;

        entry = (TEntrada) malloc(sizeof(struct entrada));
        entry -> clave = (int)((x - ubicacionActual->pos_x) + (y - ubicacionActual->pos_y));
        entry -> valor = c;

        cp_insertar(cp,entry);
    }

    fclose(archivo);

}

int main(int argc, char *argv[]){

    int opcion;
    char * ruta_archivo;
    FILE * archivo; //ubicación actual del usuario

    if(argc!=2){
        printf("ERROR: Cantidad de argumentos equivocado");
        return ERROR_INVOCACION_PROGRAMA;
    }

    ruta_archivo = argv[1];

    archivo = fopen(ruta_archivo,"r");

    if(archivo == NULL){
        printf("ERROR: Archivo no encontrado");
        return ERROR_APERTURA_ARCHIVO;
    }

    obtenerCiudades(archivo);

    printf("Archivo leido\n");
    printf("\n");

    do {
        printf("------- MENU DE OPERACIONES -------\n");
        printf("1. Mostrar Ascendente \n");
        printf("2. Mostrar Descendente \n");
        printf("3. Reducir horas de manejo \n");
        printf("4. Salir \n");
        printf("\n");
        printf("Ingrese opcion (1-4): ");

        fflush(stdin);
        scanf("%d",&opcion);
        if(opcion == 1)
            mostrarAscendente();
        if(opcion == 2)
            mostrarDescendente();
        if(opcion == 3)
            ReducirHorasManejo();
        printf("\n");
        /*
        switch(opcion){
            case 1:
                mostrarAscendente();
            case 2:
                mostrarDescendente();
            case 3:
                ReducirHorasManejo();
        }*/

    } while(opcion == 1 || opcion == 2 || opcion == 3);

    printf("\n");
    printf("GRACIAS, VUELVA PRONTOS\n");

    cp_destruir(cp,&fEliminarCiudades);
    free(ubicacionActual);

    return 0;

}


