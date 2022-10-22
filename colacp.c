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

    int p, inserte = FALSE, cant_elem;
    TNodo n, actual, aux;

    n = malloc(sizeof(struct nodo));
    n -> entrada = entr;

    if(cola -> raiz == POS_NULA){
        cola -> raiz = n;
        cola -> cantidad_elementos = 1;

        inserte = TRUE;
    }else
        actual = cola -> raiz;

    while(!inserte && (entr == ELE_NULO || entr -> clave == ELE_NULO)){//chequeo que sea una entrada válida tambn

        if( actual -> entrada == ELE_NULO )
            break;

        p = cola -> comparador( entr, actual -> entrada); // prioridad p
                        // si tiene hijoizq y no der o si tiene der y no izq hay que balancear?
        switch( p ){//si tiene menor prioridad va en el hizq sino en el der hay que acomodar

            case -1:// entrada entr tiene menor prioridad que la entrada actual
                if( actual -> hijo_izquierdo != POS_NULA && actual -> hijo_derecho != POS_NULA ){
                    actual = actual -> hijo_izquierdo;
                }else{
                    if( actual -> hijo_izquierdo == POS_NULA ){


                        (actual -> hijo_izquierdo) = n;
                        n -> padre = actual;

                        cant_elem = cola -> cantidad_elementos;
                        cola -> cantidad_elementos = cant_elem + 1;

                        inserte = TRUE;
                                              //        actual.hi
                    }else{ //tengo que balancear --> n_/         \_actual

                        aux = actual -> hijo_izquierdo;
                        aux -> hijo_derecho = actual;
                        aux -> hijo_izquierdo = n;
                        actual -> padre = aux;
                        actual -> hijo_izquierdo = NULL;

                        cant_elem = cola -> cantidad_elementos;
                        cola -> cantidad_elementos = cant_elem + 1;

                        inserte = TRUE;

                     }
                }
                break;
            case 0:// entradas actual y entr tienen la misma prioridad, actualizo el valor de la entrada
                 (actual -> entrada -> valor) = (entr -> valor);
                 inserte = TRUE;
                 break;
            case 1:// entrada entr tiene mayor prioridad que la entrada actual
                if( actual -> hijo_izquierdo != POS_NULA && actual -> hijo_derecho != POS_NULA ){
                    actual = actual -> hijo_derecho;
                }else{
                    if( actual -> hijo_izquierdo != POS_NULA ){ // && (*actual) -> hijo_derecho == NULL ){
                        actual -> hijo_derecho = n;
                        n -> padre = actual;

                        cant_elem = cola -> cantidad_elementos;
                        cola -> cantidad_elementos = cant_elem + 1;

                        inserte = TRUE;
                                            //               n
                    }else{//tengo que balancear -->  actual_/    pq n tiene mayor prioridad que el nodo actual

                        aux = actual -> padre;
                        n -> padre = aux;
                        n -> hijo_izquierdo = actual;
                        actual -> padre = n;

                        cant_elem = cola -> cantidad_elementos;
                        cola -> cantidad_elementos = cant_elem + 1;

                        inserte = TRUE;
                    }
                }
                break;

        };
    }

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
