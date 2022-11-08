#include "../include/cadena.h"
// los elementos se mantienen entre 0 y cantidad - 1, incluidos
struct _rep_cadena
{
  TInfo elemen;
  TCadena sig;
};

TCadena crearCadena()
{
  TCadena p = NULL;

  return p;
}

nat cantidadEnCadena(TCadena cad)
{

  nat contador = 0;
  if (cad != NULL)
  {
    contador = 1;
    TCadena l = cad;
    while (l->sig != NULL)
    {
      contador += 1;
      l = l->sig;
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
    while ((l != NULL) && (natInfo(l->elemen) != natural))
    {
      l = l->sig;
    }
    return (l != NULL);
  }
}

TCadena insertarAlInicio(nat natural, double real, TCadena cad)
{

  TCadena l = new _rep_cadena;
  l->elemen = crearInfo(natural, real);
  l->sig = cad;
  cad = l;

  return cad;
}

TInfo infoCadena(nat natural, TCadena cad)
{
  TCadena l = cad;
  if (estaEnCadena(natural, cad))
  {
    // recorrer la lista cad y buscar natural en algun componente

    while ((l != NULL) && (natInfo(l->elemen) != natural))
    {
      l = l->sig;
    }
  }
  if (l != NULL)
  {

    return (l->elemen);
  }
  else
  {
    return NULL;
  }
}

TCadena removerDeCadena(nat natural, TCadena cad)
{
  TCadena l = cad;
  if (natInfo(cad->elemen) == natural)
  {
    cad = cad->sig;
    delete (l);
  }
  else
  {
    while ((l != NULL) && (natInfo(l->sig->elemen) != natural))
    {
      l = l->sig;
    }
    TCadena p = l->sig;
    l->sig = p->sig;
    delete (p);
  }

  return cad;
}

void imprimirCadena(TCadena cad)
{
  if ((cantidadEnCadena(cad)) == 0)
  {
    printf("\n");
  }
  else
  {
    TCadena l = cad;
    while (l != NULL)
    {
      imprimirInfo(l->elemen);
      l = l->sig;
    }
    printf("\n");
  }
}
