/* 5237782 */ // sustituiir con los 7 dígitos de la cédula
#include "../include/aplicaciones.h"
#include "../include/colCadenas.h"
#include "../include/cadena.h"
#include "../include/cola.h"
#include "../include/pila.h"
#include "../include/info.h"
#include "../include/abb.h"

struct _rep_cadena
{
    TInfo elemen;
    TCadena sig, ant;
};

TCadena crearCadena()
{
    TCadena p = NULL;
    return p;
}

void liberarCadena(TCadena cad)
{
    TCadena aux = cad;
    if (cad == NULL)
    {
    }
    else if (aux == aux->sig)
    {
        liberarInfo(aux->elemen);

        delete (cad);
    }
    else if ((aux != NULL) && (cad != aux->sig))
    {
        aux = aux->sig;

        while (aux != cad)
        {
            TCadena aux2 = aux;
            aux = aux->sig;
            liberarInfo(aux2->elemen);
            delete (aux2);
        }

        liberarInfo(cad->elemen);
        delete (cad);
    }
}

nat cantidadEnCadena(TCadena cad)
{
    nat contador = 0;
    if (cad != NULL)
    {
        contador = 1;
        TCadena l = cad;

        if (l->sig != cad)
        {

            while (l != cad->ant)
            {

                contador++;
                l = l->sig;
            }
        }
    }
    return contador;
}

bool estaEnCadena(nat natural, TCadena cad)
{
    TCadena l = cad;
    if (l == NULL)
    {
        return false;
    }
    else
    {
        if (l->sig != cad)
        {
            while ((l != cad->ant) && (natInfo(l->elemen) != natural))
            {
                l = l->sig;
            }

            if (l != cad->ant)
            {

                return true;
            }
            else if ((l == cad->ant) && (natInfo(l->elemen) == natural))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {

            if (natInfo(l->elemen) == natural)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

TCadena insertarAlInicio(nat natural, double real, TCadena cad)
{
    TCadena l = new _rep_cadena;
    l->elemen = crearInfo(natural, real);

    if (cad == NULL)
    {

        l->sig = l;
        l->ant = l;
        cad = l;
    }
    else
    {
        l->sig = cad;
        cad->ant->sig = l;
        l->ant = cad->ant;
        l->sig->ant = l;
        cad = l;
    }

    return cad;
}

TInfo infoCadena(nat natural, TCadena cad)
{
    TCadena l = cad;

    if (l == l->sig)
    {
        return (l->elemen);
    }
    else
    {

        while ((l != cad->ant) && (natInfo(l->elemen) != natural))
        {
            l = l->sig;
        }

        if (natInfo(l->elemen) == natural)
        {
            return (l->elemen);
        }
        else
        {
            return ((cad->ant)->elemen);
        }
    }
}

TInfo primeroEnCadena(TCadena cad)
{

    return (cad->elemen);
}

TCadena cadenaSiguiente(TCadena cad)
{
    if ((cad == NULL) || (cad == cad->ant))
    {
        return cad;
    }
    else
    {
        TCadena aux = cad;

        aux = cad->sig;
        return aux;
    }
}

TCadena removerDeCadena(nat natural, TCadena cad)
{
    TCadena l = cad;

    if (l == l->ant)
    {

        liberarInfo(l->elemen);
        delete (l);
        cad = NULL;
    }
    else
    {
        while (natInfo(l->elemen) != natural)
        {
            l = l->sig;
        }

        l->sig->ant = l->ant;
        l->ant->sig = l->sig;
        if (cad == l)
        {
            cad = l->sig;
        }

        liberarInfo(l->elemen);
        delete (l);
    }

    return cad;
}

void imprimirCadena(TCadena cad)
{

    if (cad == NULL)
    {
        printf("\n");
    }
    else
    {
        TCadena l = cad;
        nat i = 1;
        nat cantCad = cantidadEnCadena(cad);
        while (i <= cantCad)
        {
            imprimirInfo(l->elemen);
            l = l->sig;
            i += 1;
        }
        printf("\n");
    }
}

TCadena insertarAlFinal(nat natural, double real, TCadena cad)
{
    TCadena nueva = crearCadena();
    nueva = cadenaSiguiente(insertarAlInicio(natural, real, cad));
    return nueva;
}

TCadena removerPrimero(TCadena cad)
{
    nat nuevo = natInfo(primeroEnCadena(cad));
    cad = removerDeCadena(nuevo, cad);
    return cad;
}

TCadena copiaCadena(TCadena cad)
{
    TCadena nueva = crearCadena();
    if (cad == NULL)
    {
        return nueva;
    }
    TInfo primeroInf = primeroEnCadena(cad);
    TCadena aux = cad;

    do
    {
        nueva =
            insertarAlFinal(natInfo(primeroEnCadena(aux)), realInfo(primeroEnCadena(aux)), nueva);
        aux = cadenaSiguiente(aux);

    } while (primeroInf != primeroEnCadena(aux));

    return nueva;
}
