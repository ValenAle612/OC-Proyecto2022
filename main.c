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

int main()
{
    printf("Hello world!\n");
    TColaCP cola_pepe = crear_cola_cp(&fComparador);
    TEntrada entrada1 = (TEntrada) malloc(sizeof(struct entrada));
    entrada1 -> clave = 1;
    entrada1 -> valor = 879;
    TEntrada entrada2 = (TEntrada) malloc(sizeof(struct entrada));
    entrada2 -> clave = 2;
    entrada2 -> valor = 547;
    printf("cree la cola?\n");
    printf("cantidad de elementos en la cola: %i\n", cola_pepe->cantidad_elementos);
    int resultado = cp_insertar(cola_pepe, entrada1);
    printf("agregue raiz? %i\n", resultado);
    printf("cantidad de elementos en la cola: %i\n", cola_pepe->cantidad_elementos);
    resultado = cp_insertar(cola_pepe, entrada2);
    printf("agregue elemento? %i\n", resultado);
    printf("cantidad de elementos en la cola: %i\n", cola_pepe->cantidad_elementos);


    return 0;
}
