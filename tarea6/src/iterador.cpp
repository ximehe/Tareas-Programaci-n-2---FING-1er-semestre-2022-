/* 5237782 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/aplicaciones.h"
#include "../include/colCadenas.h"
#include "../include/cadena.h"
#include "../include/cola.h"
#include "../include/pila.h"
#include "../include/info.h"
#include "../include/abb.h"
#include "../include/utils.h"

struct nodo
{
    nat elemen;
    nodo *sig;
};

struct _rep_iterador
{
    nodo *primero;
    nodo *actual;
    nodo *ultimo;
};

TIterador crearIterador()
{
    _rep_iterador *cabezal = new _rep_iterador;
    cabezal->primero = NULL;
    cabezal->actual = NULL;
    cabezal->ultimo = NULL;
    return cabezal;
}

void liberarIterador(TIterador iter)
{

    // Pregunto si iter tiene solo un elemento en la lista, si es asi, lo borro.
    if (iter->primero == iter->ultimo)
    {
        delete (iter->ultimo);
        delete (iter);
    }
    else

    { // sino, recorro hasta llegar al penultimo elemento y voy borrando.
        nodo *aux;
        reiniciarIterador(iter);
        while (iter->actual != iter->ultimo)
        {

            aux = iter->actual;
            iter->actual = iter->actual->sig;
            delete (aux);
        }

        // borro el ultimo

        delete (iter->actual);
        delete (iter);
    }
}

bool estaDefinidaActual(TIterador iter)
{

    if (iter->actual == NULL)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void agregarAIterador(nat elem, TIterador const iter)
{
    nodo *nuevo = new nodo;
    nuevo->elemen = elem;

    if (iter->primero == NULL)
    {
        iter->primero = nuevo;
        iter->ultimo = nuevo;
        nuevo->sig = NULL;
    }
    else
    {
        iter->ultimo->sig = nuevo;
        iter->ultimo = nuevo;
        nuevo->sig = NULL;
    }
}

void reiniciarIterador(TIterador const iter)
{
    if (iter != NULL)
    {
        iter->actual = iter->primero;
    }
}

void avanzarIterador(TIterador const iter)
{
    if (iter->actual == iter->ultimo)
    {
        iter->actual = NULL;
    }
    else if (estaDefinidaActual(iter))
    {
        iter->actual = iter->actual->sig;
    }
}

nat actualEnIterador(TIterador iter)
{

    return iter->actual->elemen;
}