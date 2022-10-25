#include "stdio.h"
#include <stdlib.h>
#include "colacp.h" //cola con prioridad header

/**
    Crea y retorna una cola con prioridad vac�a.
*/
TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada)){

   TColaCP * cp = malloc(sizeof(struct cola_con_prioridad));

   if(*cp == NULL){
        printf("ERROR: No se pudo reservar espacio en memoria.");
   }

   (*cp) -> cantidad_elementos = 0;
   (*cp) -> raiz = malloc(sizeof(struct nodo));
   (*cp) -> comparador = f;

   return * cp;
}

void intercambiar_entradas(TNodo nodo1, TNodo nodo2) {
    TEntrada temp = nodo1 -> entrada;
    nodo1 -> entrada = nodo2 -> entrada;
    nodo2 -> entrada = temp;
}

void ordenar(TColaCP cola, TNodo nodo){
    if(nodo != cola -> raiz && comparador(nodo -> entrada, nuevo -> padre -> entrada == 1)) {
        intercambiar_entradas(nodo, nodo -> padre);
        ordenar(cola, nodo -> padre);
    }
}

ordenar_eliminado(TColaCP cola, TNodo nodo_raiz) {
    TNodo nodo_menor = nodo_raiz -> hijo_izquierdo;
    if(nodo_raiz -> nodo_derecho != ELE_NULO && comparador(nodo_menor ->entrada, nodo_raiz -> hijo_derecho -> entrada) == -1)
        nodo_menor = nodo_raiz -> hijo_derecho;
    if(hijo_menor != ELE_NULO && comparador(nodo_raiz, comparador(nodo_menor ->entrada, nodo_raiz -> hijo_derecho -> entrada) == -1)) {
        intercambiar(nodo_raiz, nodo_menor);
        ordenar_eliminado(cola, nodo_menor)
    }
}

/**
 * Asigna al nodo nuevo el padre del nodo original y
 * al original el nodo nuevo como padre
*/
void intercambiar_padres(TNodo original, TNodo nuevo) {
    nuevo -> padre = original -> padre;
    if((original -> padre -> hijo_izquierdo) == original) {
        original -> padre -> hijo_izquierdo = nuevo; 
    }
    else
        original -> padre -> hijo_derecho = nuevo;
    original -> padre = nuevo;
}

/**
 * Elimina los hijos del nodo original y en su lugar 
 * los asigna como hijos del nodo nuevo.
*/
void intercambiar_hijos(TNodo original, TNodo nuevo) {
    if(original -> hijo_izquierdo != POS_NULA) {
        nuevo -> hijo_izquierdo = original -> hijo_izquierdo;
        original -> hijo_izquierdo = POS_NULA;
    }
    if(original -> hijo_derecho != POS_NULA) {
        nuevo -> hijo_derecho = nuevo -> hijo_derecho;  
        original -> hijo_derecho = POS_NULA; 
    }   
}

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

    if (entr == ELE_NULO || entr -> clave == ELE_NULO)
        break;

    int p, inserte = FALSE, cant_elem;
    TNodo nuevo_nodo, nodo_actual, nodo_aux;
    TEntrada entrada_actual;

    nuevo_nodo = (TNodo) malloc(sizeof(struct nodo));
    nuevo_nodo -> entrada = entr;
    nuevo_nodo -> padre = POS_NULA;
    nuevo_nodo -> hijo_izquierdo = POS_NULA;
    nuevo_nodo -> hijo_derecho = POS_NULA;

    if(cola -> raiz == POS_NULA){
        cola -> raiz = nuevo_nodo;
        cola -> cantidad_elementos = 1;
        inserte = TRUE;
    }
    else if(cola -> raiz -> hijo_izquierdo != POS_NULA && cola -> raiz -> hijo_derecho != POS_NULA) {
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
    return inserte;
}


/**
    Elimina y retorna la entrada con mayor prioridad
    de la cola.
*/
TEntrada cp_eliminar(TColaCP cola){
    TNodo n, aux;
    TEntrada toRet;

    int elimine = FALSE;

    n = cola -> raiz;

    if(n == POS_NULA){
        printf("ERROR: LA COLA ESTA VACIA\n");
        exit(CCP_NO_INI);
    }

    while(!elimine){
        if( n -> hijo_derecho == NULL ){
            if( n -> hijo_izquierdo != NULL ){
                aux = n -> padre;
               ( aux -> hijo_derecho ) = ( n -> hijo_izquierdo );
               free(n);
            }
            else{
                n -> padre -> hijo_derecho = POS_NULA;
                free(n);
            }
            elimine = TRUE;
        }else
            n = n -> hijo_derecho;
    }

    toRet = n -> entrada;

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
