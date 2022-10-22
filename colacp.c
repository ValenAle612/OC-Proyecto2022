#include "stdio.h"
#include <stdlib.h>
#include "colacp.h" //cola con prioridad header

/**
    Crea y retorna una cola con prioridad vacía.
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

/**
    Agrega la entrada a la cola.
    -> Retorna verdadero si procede con éxito
    -> Falso, caso contrario.
*/
int cp_insertar(TColaCP cola, TEntrada entr){

    int p, inserte = FALSE;
    TNodo * n, * actual, * aux;

    n = malloc(sizeof(struct nodo));
    (*n) -> entrada = entr;

    actual = cola -> raiz;

    while(!inserte){

        p = cola -> comparador( entr, (*actual) -> entrada); // prioridad p
                        // si tiene hijoizq y no der o si tiene der y no izq hay que balancear?
        switch( p ){//si tiene menor prioridad va en el hizq sino en el der hay que acomodar

            case -1:// entrada entr tiene menor prioridad que la entrada actual
                if( (*actual) -> hijo_izquierdo != NULL && (*actual) -> hijo_derecho != NULL ){

                    actual = (*actual) -> hijo_izquierdo;

                }else{
                    if( (*actual) -> hijo_izquierdo == NULL ){

                        (*actual) -> hijo_izquierdo = n;
                        (*n) -> padre = actual;
                                              //        actual.hi
                    }else{ //tengo que balancear --> n_/         \_actual

                        aux = (*actual) -> hijo_izquierdo;
                        (*aux) -> hijo_derecho = actual;
                        (*aux) -> hijo_izquierdo = n;
                        (*actual) -> padre = aux;
                        (*actual) -> hijo_izquierdo = NULL;

                     }
                }
                break;
            case 0:// entradas actual y entr tienen la misma prioridad

            case 1:// entrada entr tiene mayor prioridad que la entrada actual


        };
    }


}


/**
    Elimina y retorna la entrada con mayor prioridad
    de la cola.
*/
TEntrada cp_eliminar(TColaCP cola){

}

/**
    Retorna la cantidad de entradas de la cola.
*/
int cp_cantidad(TColaCP cola){

}


/**
    Elimina todas las entradas y libera toda la memoria utilizada por la queue.
*/
void cp_destruir(TColaCP cola, void (*fEliminar)(TEntrada) ){

}

