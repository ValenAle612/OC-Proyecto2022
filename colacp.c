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
 * EL ERROR ESTA ACA
*/
void intercambiar_entradas(TNodo nodo1, TNodo nodo2) {
    TEntrada temp = (TEntrada) malloc(sizeof(struct entrada));
    temp->clave = nodo1 -> entrada->clave;
    temp->valor = nodo1->entrada->valor;
    nodo1 -> entrada ->clave= nodo2 -> entrada->clave;
    nodo1->entrada->valor = nodo2->entrada->valor;
    nodo2 -> entrada->clave = temp->clave;
    nodo2->entrada->valor = temp->valor;
    free(temp);
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
    mientras no este ordenado
    miro los hijos y me quedo con el mas chico
    si es el izquierdo
        el nuevo hijo derecho del izquierdo es el derecho
        el nuevo hijo izquierdo del ex izquierdo va a ser el mas chico de los hijos

*/

/**
 * Ordena la cola cuando se elimina un elemento.
 *
 *
 *
*/
TNodo ordenar_eliminado(TColaCP cola, TNodo nodo_raiz) {
    TNodo menor_actual = ELE_NULO;
    if(nodo_raiz -> hijo_izquierdo != ELE_NULO){
        menor_actual = nodo_raiz -> hijo_izquierdo; //asumo que el menor es el izquierdo
        //printf("Hijo izquierdo actual: Clave %i, Valor %i.\n", menor_actual->entrada->clave, menor_actual->entrada->valor);
        //si el derecho es mas chiquito los intercambio de lugar
        if(nodo_raiz -> hijo_derecho != ELE_NULO && cola -> comparador(menor_actual -> entrada, nodo_raiz -> hijo_derecho -> entrada) == 1){
            menor_actual = nodo_raiz -> hijo_derecho;
            //printf("Hijo izquierdo actual: Clave %i, Valor %i.\n", menor_actual->entrada->clave, menor_actual->entrada->valor);
        }
        intercambiar_entradas(nodo_raiz, menor_actual);
        ordenar_eliminado(cola, menor_actual);
    }
    return menor_actual;
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
            if(cola->comparador(nodo_actual -> entrada, nuevo_nodo -> entrada) == 1) {
                nodo_actual -> hijo_izquierdo = nuevo_nodo;
                nuevo_nodo -> padre = nodo_actual;
            }
            else {
                nodo_actual -> padre = nuevo_nodo;
                nuevo_nodo -> hijo_izquierdo = nodo_actual;
                cola -> raiz = nuevo_nodo;
            }
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
    toRet -> clave = (nodo_original -> entrada -> clave);
    toRet -> valor = (nodo_original -> entrada -> valor);
    return toRet;
}


/**
    Elimina y retorna la entrada con mayor prioridad
    de la cola.
    #define PRIMERO_MENOR_PRIORIDAD -1
    #define PRIMERO_MAYOR_PRIORIDAD 1
    #define IGUAL_PRIORIDAD 0
*/
TNodo ordenar_luego_de_eliminar(TColaCP cola, TNodo raiz_actual) {
    TNodo nodo_eliminar;
    TEntrada entrada_actual = raiz_actual -> entrada;
    if (raiz_actual->hijo_izquierdo == ELE_NULO && raiz_actual->hijo_derecho == ELE_NULO) {
        nodo_eliminar = raiz_actual;
    }

    if(raiz_actual -> hijo_izquierdo != ELE_NULO) {
        if(raiz_actual->hijo_derecho == ELE_NULO) {
            intercambiar_entradas(raiz_actual, raiz_actual -> hijo_izquierdo);
            nodo_eliminar = ordenar_luego_de_eliminar(cola, raiz_actual -> hijo_izquierdo);
        }
        else {
            //tenemos 2 hijos
            if(cola->comparador(raiz_actual -> hijo_izquierdo -> entrada, raiz_actual -> hijo_derecho -> entrada) == 1) {
                    //hijo iz menor que hijo derecho
                intercambiar_entradas(raiz_actual, raiz_actual -> hijo_izquierdo);
                nodo_eliminar = ordenar_luego_de_eliminar(cola, raiz_actual -> hijo_izquierdo);
            }
            else {
                //hijo izq mayor que hijo der
                //printf("entre aca wacho, %i tiene mayor prioridad que %i\n", raiz_actual->hijo_izquierdo->entrada->clave, raiz_actual->hijo_derecho->entrada->clave);
                //printf("este es el hijo derecho de la raiz: %i", raiz_actual->hijo_derecho->entrada->clave);
                intercambiar_entradas(raiz_actual, raiz_actual -> hijo_derecho);
                nodo_eliminar = ordenar_luego_de_eliminar(cola, raiz_actual -> hijo_derecho);
            }
        }
    }

    return nodo_eliminar;
}


/*
ordenarLuegoDeEliminar(TColaCP cola, TNodo raiz_actual)
    Verifico si la cola esta vacia -> error
    TEntrada guardo la entrada de la raiz que voy a eliminar
    miro si la raiz actual tiene hijos
        si tiene solo hijo izquierdo
            raiz de la cola ahora es hijo izquierdo
        si tiene ambos hijos
            si hijo izquierdo tiene mas prioridad que hijo derecho
                raiz de la cola ahora es hijo izquierdo
                llamo a ordenarLuegoDeEliminar con la cola e hijo izquierdo
            sino
                raiz de la cola ahora es hijo derecho
                llamo a ordenarLuegoDeEliminar con la cola e hijo derecho



    en la funcion que llama:
        raiz de la cola tiene padre nulo
        hago un free en la ex raiz
*/

TEntrada cp_eliminar(TColaCP cola){

    TNodo nodo_actual = cola -> raiz;
    TNodo nodo_eliminar = ELE_NULO;
    TEntrada toRet = ELE_NULO;
    TNodo padre_nodo_eliminar;

    //TODO revisar pos nulas y ele nulos y creacion de cola(valor inicial de raiz)
    if(nodo_actual == POS_NULA){
        printf("ERROR: LA COLA ESTA VACIA\n");
        exit(CCP_NO_INI);
    }

    if(cola -> cantidad_elementos != 0) {
        nodo_eliminar = nodo_actual;
        toRet = copiar_entrada(nodo_actual);
        //printf("Entrada a eliminar: Clave %i, Valor %i.\n", toRet->clave, toRet->valor);
        nodo_eliminar = ordenar_luego_de_eliminar(cola, nodo_actual);
        //printf("ordene luego de eliminar\n");
        cola -> cantidad_elementos--;
    }
    if(nodo_eliminar != ELE_NULO && nodo_eliminar != cola->raiz) {
        padre_nodo_eliminar = nodo_eliminar->padre;
        if (padre_nodo_eliminar->hijo_izquierdo == nodo_eliminar) {
            if (padre_nodo_eliminar->hijo_derecho != ELE_NULO) {
                padre_nodo_eliminar->hijo_izquierdo = padre_nodo_eliminar->hijo_derecho;
                padre_nodo_eliminar->hijo_derecho = ELE_NULO;
            }
            else {
                padre_nodo_eliminar->hijo_izquierdo = ELE_NULO;
            }
        }
        else {
            padre_nodo_eliminar->hijo_derecho = ELE_NULO;
        }
    }
    free(nodo_eliminar);
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
