#ifndef COLACP_H_INCLUDED
#define COLACP_H_INCLUDED

#define FALSE 0 //valor l�gico falso
#define TRUE 1 //valor l�gico verdadero
#define CCP_NO_INI 2 //Intento de acceso inv�lido sobre ColaCP sin inicializar
#define POS_NULA NULL //Posici�n nula
#define ELE_NULO NULL //Elemento nulo

typedef void * TClave;
typedef void * TValor;

typedef struct entrada {
    TClave clave;
    TValor valor;
} * TEntrada;

typedef struct nodo {
    TEntrada entrada;
    struct nodo * padre;
    struct nodo * hijo_izquierdo;
    struct nodo * hijo_derecho;
} * TNodo;

typedef struct cola_con_prioridad {
    int cantidad_elementos;
    TNodo raiz;
    int (*comparador)(TEntrada, TEntrada);
} * TColaCP;


// ---------------------------------------------------------------------------------------------
// Definici�n de prototipos y documentaci�n de las funciones.
// ---------------------------------------------------------------------------------------------

/**
  * Crea y retorna una cola con prioridad vac�a.
  */
extern TColaCP crear_cola_cp(int (*f)(TEntrada, TEntrada));

/**
  * Agrega la entrada a la cola.
  * -> Retorna verdadero si procede con �xito
  * -> Falso, caso contrario.
*/
extern int cp_insertar(TColaCP cola, TEntrada entr);

/**
  * Elimina y retorna la entrada con mayor prioridad
  * de la cola.
*/
extern TEntrada cp_eliminar(TColaCP cola);

/**
  * Retorna la cantidad de entradas de la cola.
*/
extern int cp_cantidad(TColaCP cola);


/**
  * Elimina todas las entradas y
  * libera toda la memoria utilizada por la cola.
*/
extern void cp_destruir(TColaCP cola, void (*fEliminar)(TEntrada) );

#endif // COLACP_H_INCLUDED
