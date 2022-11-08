/* 5237782 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/cola.h"
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

struct _rep_cola
{
    Nodo *primero, *ultimo;
    nat tope;
};

TCola crearCola()
{
    TCola c = new _rep_cola;
    c->primero = c->ultimo = NULL;
    c->tope = 0;
    return c;
}

void liberarCola(TCola c)
{

    Nodo *temp;
    while (c->primero != NULL)
    {
        temp = c->primero;
        c->primero = c->primero->sig;
        liberarInfo(temp->elem);
        delete temp;
    }
    delete c;
}

nat cantidadEnCola(TCola c)
{
    return c->tope;
}

TCola encolar(TInfo info, TCola c)
{

    Nodo *nuevo = new Nodo;
    nuevo->elem = copiaInfo(info);
    nuevo->sig = NULL;
    if (c->primero == NULL)
        c->primero = nuevo;
    else
        c->ultimo->sig = nuevo;
    c->ultimo = nuevo;

    c->tope++;

    return c;
}

TInfo frente(TCola c)
{
    assert(c->primero != NULL);
    return c->primero->elem;
}

TCola desencolar(TCola c)
{
    assert(c->primero != NULL);
    Nodo *temp = c->primero;
    c->primero = c->primero->sig;
    if (c->primero == NULL)
        c->ultimo = NULL;
    liberarInfo(temp->elem);
    delete temp;
    c->tope--;

    return c;
}
