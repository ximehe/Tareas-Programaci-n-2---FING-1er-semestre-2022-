/* 5237782 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/aplicaciones.h"
#include "../include/colCadenas.h"
#include "../include/cadena.h"
#include "../include/cola.h"
#include "../include/pila.h"
#include "../include/info.h"
#include "../include/abb.h"
struct _rep_abb
{
    TInfo elem;
    TAbb izq, der;
};

void rotarDerecha(TAbb &abb)
{
    if ((abb->izq) != NULL)
    {
        TAbb l = abb->izq;
        TAbb x = l->der;
        l->der = abb;
        abb->izq = x;
        abb = l;
    }
}
void rotarIzquierda(TAbb &abb)
{
    if ((abb->der) != NULL)
    {
        TAbb l = abb->der;
        TAbb y = l->izq;
        l->izq = abb;
        abb->der = y;
        abb = l;
    }
}

void auxRotar(nat clave, char tipo[2], TAbb &abb)
{
    if (clave > natInfo(abb->elem))
        auxRotar(clave, tipo, abb->der);
    else
    {
        if (clave < natInfo(abb->elem))
            auxRotar(clave, tipo, abb->izq);
        else
        {

            if ('L' == tipo[0])
            {
                if ('L' == tipo[1])
                    rotarDerecha(abb);
                else
                {
                    if (abb->izq != NULL && abb->izq->der != NULL)
                    {
                        rotarIzquierda(abb->izq);
                        rotarDerecha(abb);
                    }
                }
            }
            else
            {
                if ('R' == tipo[1])
                {
                    rotarIzquierda(abb);
                }
                else
                {
                    if (abb->der != NULL && abb->der->izq != NULL)
                    {
                        rotarDerecha(abb->der);
                        rotarIzquierda(abb);
                    }
                }
            }
        }
    }
}

TAbb rotar(nat clave, char tipo[2], TAbb abb)
{
    if (buscarSubarbol(clave, abb) == NULL)
    {
        return abb;
    }
    else
    {
        auxRotar(clave, tipo, abb);
        return abb;
    }
    // TAbb subAbb = buscarSubarbol(clave, abb);
    // if (subAbb != NULL)
    // {

    //     if ((tipo[0] == 'R') && (tipo[1] == 'R'))
    //     {
    //     }
    //     else if ((tipo[0] == 'L') && (tipo[1] = 'L'))
    //     {
    //     }
    //     else if ((tipo[0] == 'R') && (tipo[1] = 'L'))
    //     {
    //     }
    //     else if ((tipo[0] == 'L') && (tipo[1] = 'R'))
    //     {
    //     }
    // }

    // return abb;
}

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
