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

#endif // COLACP_H_INCLUDED
