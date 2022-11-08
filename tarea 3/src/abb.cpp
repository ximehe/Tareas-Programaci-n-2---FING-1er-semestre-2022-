/* 5237782 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/abb.h"
#include "../include/info.h"

struct _rep_abb
{
    TInfo elem;
    TAbb izq, der;
};

TAbb crearAbb()
{
    TAbb nuevo = NULL;
    return nuevo;
}
void liberarNodo(TAbb abb)
{
    liberarInfo(abb->elem);
    delete (abb);
}
void liberarAbb(TAbb abb)
{
    if (abb != NULL)
    {

        liberarAbb(abb->izq);
        liberarAbb(abb->der);
        liberarNodo(abb);
    }
}

bool esVacioAbb(TAbb abb)
{
    return (abb == NULL);
}

TAbb buscarSubarbol(nat clave, TAbb abb)
{
    if (abb == NULL)
    {
        return NULL;
    }
    else if (natInfo(raiz(abb)) == clave)
    {
        return abb;
    }
    else if (clave < natInfo(raiz(abb)))
    {
        return buscarSubarbol(clave, abb->izq);
    }
    else
    {
        return buscarSubarbol(clave, abb->der);
    }
}

TInfo raiz(TAbb abb)
{
    return abb->elem;
}

TAbb izquierdo(TAbb abb)
{
    return abb->izq;
}

TAbb derecho(TAbb abb)
{
    return abb->der;
}

TInfo menorEnAbb(TAbb abb)
{
    if (abb->izq != NULL)
    {
        return menorEnAbb(abb->izq);
    }
    else
    {
        return abb->elem;
    }
}

TInfo mayorEnAbb(TAbb abb)
{
    if (abb->der != NULL)
    {
        return mayorEnAbb(abb->der);
    }
    else
    {
        return abb->elem;
    }
}

TAbb consAbb(TInfo dato, TAbb izq, TAbb der)
{
    TAbb abb = new _rep_abb;
    abb->elem = dato;
    abb->der = der;
    abb->izq = izq;

    /*
  Devuelve un 'TAbb' con 'dato' en su raÃ­z y subÃ¡rboles izquierdo y
  derecho son 'izq' y 'der' respectivamente.
  El resulrado comparte memoria con los parÃ¡metros.
  Precondiciones:
    - esVacioAbb(izq) || (natInfo(mayorEnAbb(izq)) < natInfo(dato))
    - esVacioAbb(der) || (natInfo(menorEnAbb(der)) > natInfo(dato))
 */
    return abb;
}

TAbb insertarEnAbb(TInfo dato, TAbb abb)
{
    if (abb == NULL)
    {
        TAbb nuevonodo = new _rep_abb;
        nuevonodo->elem = dato;
        nuevonodo->izq = NULL;
        nuevonodo->der = NULL;
        abb = nuevonodo;
    }
    else if (natInfo(dato) < natInfo(abb->elem))
    {
        abb->izq = insertarEnAbb(dato, abb->izq);
    }
    else if (natInfo(dato) > natInfo(abb->elem))
    {
        abb->der = insertarEnAbb(dato, abb->der);
    }

    return abb;
}

TAbb removerDeAbb(nat clave, TAbb abb)
{

    if (abb == NULL)
        return abb;

    if (clave < natInfo(abb->elem))
        abb->izq = removerDeAbb(clave, abb->izq);

    else if (clave > natInfo(abb->elem))
        abb->der = removerDeAbb(clave, abb->der);
    else
    {
        if (abb->izq == NULL)
        {
            TAbb aux = abb->der;
            liberarInfo(abb->elem);
            delete (abb);
            return aux;
        }
        else if (abb->der == NULL)
        {

            TAbb aux = abb->izq;
            liberarInfo(abb->elem);
            delete (abb);
            return aux;
        }
        TInfo aux = mayorEnAbb(abb->izq);
        liberarInfo(abb->elem);
        abb->elem = copiaInfo(aux);
        abb->izq = removerDeAbb(natInfo(aux), izquierdo(abb));
    }
    return abb;
}

/*
Remueve de 'abb' el nodo que contiene el elemento cuyo componente natural
es 'clave'.
Libera la memoria del nodo y del elemento.
Si los dos subÃ¡rboles del nodo a remover son no vacÃ­os, en sustituciÃ³n
del elemento removido debe quedar el que es el mayor (segun la propiedad
de orden definida) en el subÃ¡rbol izquierdo.
Devuelve 'abb'.
PrecondiciÃ³n: ! esVacioAbb(buscarSubarbol(clave, abb))
*/

TAbb copiaAbb(TAbb abb)
{
    if (abb == NULL)
    {
        return NULL;
    }
    else
    {
        TAbb nuevo = new _rep_abb;
        nuevo->elem = copiaInfo(abb->elem);
        nuevo->izq = copiaAbb(abb->izq);
        nuevo->der = copiaAbb(abb->der);
        return nuevo;
    }
}
