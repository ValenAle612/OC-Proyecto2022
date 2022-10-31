#include <stdio.h>
#include <stdlib.h>
#include "colacp.h"

int fComparador(TEntrada c1, TEntrada c2){

    int clave1 = c1 -> clave;
    int clave2 = c2 -> clave;

    if(clave1 < clave2){
        return -1;
    }
    else if(clave1 > clave2){
        return 1;
    }
    else
        return 0;
}

void mostrarElementosCola(TColaCP cola) {
    TEntrada entrada_eliminada;
    printf("Aun no entre a while.\n");
    while(cola -> cantidad_elementos != 0) {
        printf("Estoy por eliminar.\n");
        entrada_eliminada = cp_eliminar(cola);
        printf("Clave eliminada: %i. Valor eliminado: %i.\n", entrada_eliminada->clave, entrada_eliminada->valor);
        printf("Elementos restantes en la cola: %i.\n", cola->cantidad_elementos);
    }
}


int main()
{
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

    printf("Cree la cola?\n");
    printf("Cantidad de elementos en la cola: %i.\n", cola_test->cantidad_elementos);
    resultado = cp_insertar(cola_test, entrada1);
    printf("Agregue raiz? %i.\n", resultado);
    printf("Raiz actual: Clave %i, Valor %i.\n", cola_test->raiz->entrada->clave, cola_test->raiz->entrada->valor);
    printf("Cantidad de elementos en la cola: %i.\n", cola_test->cantidad_elementos);
    resultado = cp_insertar(cola_test, entrada2);
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


    return 0;
}
