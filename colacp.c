#include "stdio.h"
#include <stdlib.h>
#include "colacp.h" //cola con prioridad header

/**
    Crea y retorna una cola con prioridad vac�a.
*/
TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada)){

   TColaCP cp = malloc(sizeof(struct cola_con_prioridad));

   /*
   if(*cp == NULL){
        printf("ERROR: No se pudo reservar espacio en memoria.");
   }
   */

   cp -> cantidad_elementos = 0;
   cp -> raiz = malloc(sizeof(struct nodo));
   cp -> comparador = f;
   cp -> raiz = ELE_NULO;

   return cp;
}

/**
 * Intercambia las entradas de dos nodos parametrizados.
*/
void intercambiar_entradas(TNodo nodo1, TNodo nodo2) {
    TEntrada temp = nodo1 -> entrada;
    nodo1 -> entrada = nodo2 -> entrada;
    nodo2 -> entrada = temp;
}

/**
 * Si es necesario intercambia las entradas hasta que queda la más chica arriba.
*/
void ordenar(TColaCP cola, TNodo nodo){
    if(nodo != cola -> raiz && cola -> comparador(nodo -> entrada, nodo -> padre -> entrada) == 1) {
        intercambiar_entradas(nodo, nodo -> padre);
        ordenar(cola, nodo -> padre);
    }
}

/**
 * Ordena la cola cuando se elimina un elemento.
 *
*/
ordenar_eliminado(TColaCP cola, TNodo nodo_raiz) {
    TNodo menor_actual;
    if(nodo_raiz -> hijo_izquierdo != ELE_NULO){
        menor_actual = nodo_raiz -> hijo_izquierdo;
        if(nodo_raiz -> hijo_derecho != ELE_NULO && cola -> comparador(menor_actual -> entrada, nodo_raiz -> hijo_derecho -> entrada) == -1)
            menor_actual = nodo_raiz -> hijo_derecho;
        if(cola -> comparador(nodo_raiz, cola -> comparador(menor_actual ->entrada, nodo_raiz -> hijo_derecho -> entrada) == -1)) {
            intercambiar_entradas(nodo_raiz, menor_actual);
            ordenar_eliminado(cola, menor_actual);
        }
    }
}

/**
 * Busca la ubicación donde se insertará el siguiente nodo, esto es el primer nodo sin hijos libre
*/
TNodo buscar_ubicacion(TColaCP cola, int cant_elem) {
    TNodo nodo_actual, nodo_siguiente;
    if(cant_elem == 1)
        nodo_actual = cola -> raiz;
    else {
        nodo_actual = buscar_ubicacion(cola, cant_elem/2);
        if(cant_elem%2 == 0)
            nodo_siguiente = nodo_actual -> hijo_izquierdo;
        else
            nodo_siguiente = nodo_actual -> hijo_derecho;
        if(nodo_siguiente != POS_NULA)
            nodo_actual = nodo_siguiente;
    }
    return nodo_actual;
}

/**
    Agrega la entrada a la cola.
    -> Retorna verdadero si procede con �xito
    -> Falso, caso contrario.
*/
int cp_insertar(TColaCP cola, TEntrada entr){
    int inserte = FALSE;

    if (entr != ELE_NULO && entr -> clave!= ELE_NULO) {

        int p, cant_elem;
        TNodo nuevo_nodo, nodo_actual, nodo_aux;
        TEntrada entrada_actual;

        nuevo_nodo = (TNodo) malloc(sizeof(struct nodo));
        nuevo_nodo -> entrada = entr;
        nuevo_nodo -> padre = POS_NULA;
        nuevo_nodo -> hijo_izquierdo = POS_NULA;
        nuevo_nodo -> hijo_derecho = POS_NULA;

        if(cola -> raiz == POS_NULA){
            cola -> raiz = nuevo_nodo;
            inserte = TRUE;
        }
        else if(cola -> raiz -> hijo_izquierdo == POS_NULA && cola -> raiz -> hijo_derecho == POS_NULA) {
            nodo_actual = cola -> raiz;
            nodo_actual -> hijo_izquierdo = nuevo_nodo;
            nuevo_nodo -> padre = nodo_actual;
            inserte = TRUE;
        }
        else {
            nodo_actual = buscar_ubicacion(cola, cola -> cantidad_elementos+1);
            if(nodo_actual -> hijo_izquierdo == POS_NULA)
                nodo_actual -> hijo_izquierdo = nuevo_nodo;
            else
                nodo_actual -> hijo_derecho = nuevo_nodo;
            nuevo_nodo -> padre = nodo_actual;
            ordenar(cola, nuevo_nodo);
            inserte = TRUE;
        }
        cola -> cantidad_elementos++;
    }
    return inserte;
}

/**
 * Crea y retorna una nueva entrada con los valores de la entrada parametrizada.
*/
TEntrada copiar_entrada(TNodo nodo_original) {
    TEntrada toRet = (TEntrada) malloc(sizeof(struct entrada));
    //como guardo esta pija jesus (clave y valor)
    toRet -> clave = nodo_original -> entrada -> clave;
    toRet -> valor = nodo_original -> entrada -> valor;
}


/**
    Elimina y retorna la entrada con mayor prioridad
    de la cola.
*/
TEntrada cp_eliminar(TColaCP cola){

    TNodo nodo_actual = cola -> raiz;
    TEntrada toRet = ELE_NULO;

    //TODO revisar pos nulas y ele nulos y creacion de cola(valor inicial de raiz)
    if(nodo_actual == POS_NULA){
        printf("ERROR: LA COLA ESTA VACIA\n");
        exit(CCP_NO_INI);
    }

    printf("Hasta aca llego bien.\n");
    if(cola -> cantidad_elementos != 0) {
        printf("Antes de copiar entrada.\n");
        toRet = copiar_entrada(nodo_actual);
        printf("Clave eliminada: %i. Valor eliminado: %i.\n", toRet->clave, toRet->valor);
        ordenar_eliminado(cola, nodo_actual);
        printf("Ordenar eliminado funciona.\n");
        free(nodo_actual);
        printf("Clave eliminada: %i. Valor eliminado: %i.\n", toRet->clave, toRet->valor);
        cola -> cantidad_elementos--;
    }
    return toRet ;
}

/**
    Retorna la cantidad de entradas de la cola.
*/
int cp_cantidad(TColaCP cola){

    int cantidad;

    cantidad = cola -> cantidad_elementos;

    return cantidad;
}

static void eliminarInterno(void (*fEliminar)(TEntrada), TNodo actual){
    if(actual -> hijo_izquierdo != POS_NULA){
        eliminarInterno( fEliminar, actual -> hijo_izquierdo );
    }
    if( actual -> hijo_derecho != POS_NULA ){
        eliminarInterno( fEliminar, actual -> hijo_derecho);
    }
    fEliminar( actual -> entrada );
    free(actual);
}

/**
    Elimina todas las entradas y libera toda la memoria utilizada por la queue.
*/
void cp_destruir(TColaCP cola, void (*fEliminar)(TEntrada) ){

    TNodo actual;

    if(cola -> raiz == POS_NULA){
        free(cola);
    }else
        actual = cola -> raiz;

    eliminarInterno(fEliminar,actual);
    free(cola);

}
