
typedef struct cola_con_prioridad {
    int cantidad_elementos;
    TNodo raiz;
    int (*comparador)(TEntrada, TEntrada);
} * TColaCP;

typedef struct nodo {
    TEntrada entrada;
    struct nodo * padre;
    struct nodo * hijo_izquierdo;
    struct nodo * hijo_derecho;
} * TNodo;

typedef struct entrada {
    TClave clave;
    TValor valor;
} * TEntrada;

typedef void * TClave;
typedef void * TValor;

/**
    Crea y retorna una cola con prioridad vacía.
*/
TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada)){

}


int f( TEntrada te1 , TEntrada te2){

}

/**
    Agrega la entrada a la cola.
    -> Retorna verdadero si procede con éxito
    -> Falso, caso contrario.
*/
int cp_insertar(TColaCP cola, TEntrada entr){

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

