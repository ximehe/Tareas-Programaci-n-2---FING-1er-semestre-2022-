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

    Nodo *primero;
    nat tope;
};

TPila crearPila()
{
    TPila p = new _rep_pila;
    p->primero = NULL;
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
        liberarInfo(temp->elem);
        delete temp;
    }
    delete p;
}

nat cantidadEnPila(TPila p)
{
    return p->tope;
}

TPila apilar(TInfo info, TPila p)
{
    Nodo *nuevo = new Nodo;
    nuevo->elem = copiaInfo(info);
    nuevo->sig = p->primero;
    p->primero = nuevo;
    p->tope++;
    return p;
}

TInfo cima(TPila p)
{
    return p->primero->elem;
}

TPila desapilar(TPila p)
{
    Nodo *aux = p->primero;
    p->primero = p->primero->sig;
    liberarInfo(aux->elem);
    delete aux;
    p->tope--;
    return p;
}
