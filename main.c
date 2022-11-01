#include <stdio.h>
#include <stdlib.h>
#include "colacp.h"

#define PRIMERO_MENOR_PRIORIDAD -1
#define PRIMERO_MAYOR_PRIORIDAD 1
#define IGUAL_PRIORIDAD 0

 //  f devuelve -1 si la clave de la entrada como clave1 tiene menor prioridad que la clave2 -> clave1 > clave2

int fComparador(TEntrada c1, TEntrada c2){

    int clave1 = c1 -> clave;
    int clave2 = c2 -> clave;

    if(clave1 < clave2){
        return PRIMERO_MAYOR_PRIORIDAD;
    }
    else if(clave1 > clave2){
        return PRIMERO_MENOR_PRIORIDAD;
    }
    else
        return IGUAL_PRIORIDAD;
}

void mostrarArbol(TColaCP cola, TNodo nodo) {
    TNodo nodo_izquierdo, nodo_derecho;
    if (nodo == ELE_NULO) {
        printf("Nodo actual es nulo.\n");
        //TODO: no hacemos nada
    }
    else {
        if(nodo->hijo_izquierdo!=ELE_NULO){
            nodo_izquierdo = nodo->hijo_izquierdo;
            printf("\tHijo izquierdo de %i: Clave: %i, Valor %i.\n", nodo->entrada->clave, nodo_izquierdo->entrada->clave, nodo_izquierdo->entrada->valor);
        }
        if(nodo->hijo_derecho!=ELE_NULO){
            nodo_derecho = nodo->hijo_derecho;
            printf("\tHijo derecho de %i: Clave: %i, Valor %i.\n", nodo->entrada->clave, nodo_derecho->entrada->clave, nodo_derecho->entrada->valor);
        }
        if(nodo->hijo_izquierdo!=ELE_NULO)
            mostrarArbol(cola, nodo_izquierdo);
        if(nodo->hijo_derecho!=ELE_NULO)
            mostrarArbol(cola, nodo_derecho);
    }
}

TColaCP ordenarColaEze(TColaCP colaDesordenada) {
    TColaCP colaOrdenada = crear_cola_cp(colaDesordenada->comparador);
    TEntrada entrada;
    while (colaDesordenada->cantidad_elementos != 0) {
        entrada = cp_eliminar(colaDesordenada);
        cp_insertar(colaOrdenada, entrada);
    }
    printf("termine de ordenar la cola\n");
    return colaOrdenada;
}


int mostrarElementosCola(TColaCP cola) {
    TEntrada entrada_eliminada;
    //printf("Aun no entre a while.\n");
    while(cola -> cantidad_elementos != 0) {
        printf("\n\tvoy a eleminar la raiz:\n");
        entrada_eliminada = cp_eliminar(cola);
        printf("Clave eliminada: %i. Valor eliminado: %i.\n", entrada_eliminada->clave, entrada_eliminada->valor);
        printf("Elementos restantes en la cola: %i.\n", cola->cantidad_elementos);
        //printf("\n\tmuestro la cola antes de ordenarla\n");
        //mostrarArbol(cola, cola->raiz);
        //cola = ordenarColaEze(cola);
        //printf("\n\tmuestro la cola despues de ordenarla\n");
        mostrarArbol(cola, cola->raiz);
    }
    return 1;
}

int main()
{
    TNodo nodo_ultimo;
    printf("Hello world!\n");
    int resultado;
    TColaCP cola_test = crear_cola_cp(&fComparador);
    TEntrada entrada_eliminada;

    TEntrada entrada1 = (TEntrada) malloc(sizeof(struct entrada));
    entrada1 -> clave = 34;
    entrada1 -> valor = 879;
    TEntrada entrada2 = (TEntrada) malloc(sizeof(struct entrada));
    entrada2 -> clave = 223;
    entrada2 -> valor = 547;
    TEntrada entrada3 = (TEntrada) malloc(sizeof(struct entrada));
    entrada3 -> clave = 33;
    entrada3 -> valor = 545;
    TEntrada entrada4 = (TEntrada) malloc(sizeof(struct entrada));
    entrada4 -> clave = 57;
    entrada4 -> valor = 983;
    TEntrada entrada5 = (TEntrada) malloc(sizeof(struct entrada));
    entrada5 -> clave = 7;
    entrada5 -> valor = 556;
    TEntrada entrada6 = (TEntrada) malloc(sizeof(struct entrada));
    entrada6 -> clave = 8;
    entrada6 -> valor = 678;

    printf("Cree la cola?\n");
    printf("Cantidad de elementos en la cola: %i.\n", cola_test->cantidad_elementos);
    resultado = cp_insertar(cola_test, entrada1);
    printf("Agregue raiz? %i.\n", resultado);
    printf("Raiz actual: Clave %i, Valor %i.\n", cola_test->raiz->entrada->clave, cola_test->raiz->entrada->valor);
    printf("Cantidad de elementos en la cola: %i.\n", cola_test->cantidad_elementos);
    resultado = cp_insertar(cola_test, entrada6);
    printf("Agregue elemento? %i.\n", resultado);
    printf("Cantidad de elementos en la cola: %i.\n", cola_test->cantidad_elementos);
    printf("Raiz actual: Clave %i, Valor %i.\n", cola_test->raiz->entrada->clave, cola_test->raiz->entrada->valor);
    resultado = cp_insertar(cola_test, entrada3);
    printf("Agregue elemento? %i.\n", resultado);
    printf("Cantidad de elementos en la cola: %i.\n", cola_test->cantidad_elementos);
    printf("Raiz actual: Clave %i, Valor %i.\n", cola_test->raiz->entrada->clave, cola_test->raiz->entrada->valor);
    resultado = cp_insertar(cola_test, entrada4);
    printf("Agregue elemento? %i.\n", resultado);
    printf("Cantidad de elementos en la cola: %i.\n", cola_test->cantidad_elementos);
    printf("Raiz actual: Clave %i, Valor %i.\n", cola_test->raiz->entrada->clave, cola_test->raiz->entrada->valor);
    resultado = cp_insertar(cola_test, entrada5);
    printf("Agregue elemento? %i.\n", resultado);
    printf("Cantidad de elementos en la cola: %i.\n", cola_test->cantidad_elementos);
    printf("Raiz actual: Clave %i, Valor %i.\n", cola_test->raiz->entrada->clave, cola_test->raiz->entrada->valor);
    resultado = cp_insertar(cola_test, entrada2);
    printf("Agregue elemento? %i.\n", resultado);
    printf("Cantidad de elementos en la cola: %i.\n", cola_test->cantidad_elementos);
    printf("Raiz actual: Clave %i, Valor %i.\n", cola_test->raiz->entrada->clave, cola_test->raiz->entrada->valor);
    printf("\n");
    mostrarArbol(cola_test, cola_test->raiz);
    printf("Termine de mostrar elementos de la cola(del mostrar arbol).\n");
    printf("\n");
    nodo_ultimo = buscar_ubicacion(cola_test, cola_test->cantidad_elementos);
    printf("Ultimo elemento encontrado: Clave %i, Valor %i.\n", nodo_ultimo->entrada->clave, nodo_ultimo->entrada->valor);

    int res = mostrarElementosCola(cola_test);
    printf("Termine de mostrar elementos de la cola?.\n");


    printf("Termino todo los odio a todos FEDELACONCHADETUMADRE");
    return 0;
}
