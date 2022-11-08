/* 5237782 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/aplicaciones.h"
#include "../include/colCadenas.h"
#include "../include/cadena.h"
#include "../include/cola.h"
#include "../include/pila.h"
#include "../include/info.h"
#include "../include/abb.h"
#include <stddef.h>
#include "assert.h"

struct Nodo
{
    TInfo elem;
    Nodo *sig;
};

struct _rep_pila
{
    // nat tope;
    // TCadena cad;
    Nodo *primero, *ultimo;
    nat tope;
};

TPila crearPila()
{
    TPila p = new _rep_pila;
    p->primero = NULL;
    p->ultimo = NULL;
    p->tope = 0;
    return p;
}

void liberarPila(TPila p)
{

    Nodo *temp;
    while (p->primero != NULL)
    {
        temp = p->primero;
        p->primero = p->primero->sig;
        delete temp;
    }
    delete p;
    // liberarCadena(p->cad);
    // p->tope = 0;
}

nat cantidadEnPila(TPila p)
{
    return p->tope;
}

TPila apilar(TInfo info, TPila p)
{

    Nodo *nuevo = new Nodo;
    nuevo->elem = copiaInfo(info);
    nuevo->sig = NULL;
    if (p->primero == NULL)
        p->primero = nuevo;
    else
        p->ultimo->sig = nuevo;
    p->ultimo = nuevo;

    p->tope++;

    return p;

    // insertarAlInicio(natInfo(copiaInfo(info)), realInfo(copiaInfo(info)), p->cad);
    // p->tope++;

    // return p;
}

TInfo cima(TPila p)
{
    assert(p->ultimo != NULL);
    return p->ultimo->elem;
    // return primeroEnCadena(p->cad);
}

TPila desapilar(TPila p)
{
    assert(p->ultimo != NULL);
    Nodo *temp = p->ultimo;
    if (p->tope == 1)
    {
        p->ultimo = NULL;
        p->primero = NULL;
        delete temp;
    }
    else if (p->tope > 1)
    {
        Nodo *aux = p->primero;
        while (aux->sig != temp)
        {
            aux = aux->sig;
        }

        p->ultimo = aux;
        aux->sig = NULL;
        delete temp;
    }
    p->tope--;
    return p;
    // removerPrimero(p->cad);
    // p->tope--;
    // return p;
}
