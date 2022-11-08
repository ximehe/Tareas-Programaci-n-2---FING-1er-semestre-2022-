/* 5237782 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/colaDePrioridad.h"
#include "../include/aplicaciones.h"
#include "../include/colCadenas.h"
#include "../include/cadena.h"
#include "../include/cola.h"
#include "../include/pila.h"
#include "../include/info.h"
#include "../include/abb.h"

// heap: la raiz tiene que ser más chica que sus dos hijos, sus hijos tienen que cumplir la misma propiedad
//  NO es un arbol, es un arreglo, pero graficamente es más facil verlo como un arbol
// Para cualquier elemento en la posición i del arreglo,
// el hijo izquierdo está en la posición 2*i, el hijo
// derecho en la posición siguiente: 2*i+1 y el padre
// está en la posición i / 2
//
//
//
struct _rep_colaDePrioridad
{
  TInfo *heap;
  nat tope;
  nat tamanio;
  nat *posiciones;
  bool prioridad;
};

nat posIzq(nat i)
{
  return 2 * i;
}

nat posDer(nat i)
{
  return (2 * i) + 1;
}

nat posPadre(nat i)
{
  return i / 2;
}

bool tieneHijoIzq(TColaDePrioridad cp, nat i)
{
  return (posIzq(i) <= cp->tope);
}
bool tieneHijoDer(TColaDePrioridad cp, nat i)
{
  return (posDer(i) <= cp->tope);
}
bool tienePadre(nat i)
{
  return (i != 1);
}

void filtradoAscendente(TColaDePrioridad &cp, nat pos)
{
  TInfo swap = cp->heap[pos];
  if (cp->prioridad == true)
  {
    while (pos != 1 && realInfo(cp->heap[posPadre(pos)]) > realInfo(swap))
    {
      cp->heap[pos] = cp->heap[posPadre(pos)];
      cp->posiciones[natInfo(cp->heap[posPadre(pos)])] = pos;
      pos = posPadre(pos);
    }
  }
  else if (cp->prioridad == false)
  {
    while (pos != 1 && realInfo(cp->heap[posPadre(pos)]) < realInfo(swap))
    {
      cp->heap[pos] = cp->heap[posPadre(pos)];
      cp->posiciones[natInfo(cp->heap[posPadre(pos)])] = pos;
      pos = posPadre(pos);
    }
  }

  cp->heap[pos] = swap;
  cp->posiciones[natInfo(swap)] = pos;
}

void filtradoDescendente(TColaDePrioridad &cp, nat pos)
{

  if (cp->prioridad == true)
  {
    TInfo swap = cp->heap[pos];
    while (tieneHijoIzq(cp, pos))
    {
      nat p_hijo = posIzq(pos);
      if ((p_hijo + 1 <= cp->tope) && (realInfo(cp->heap[(p_hijo)]) > realInfo(cp->heap[(p_hijo) + 1])))
      {
        p_hijo = p_hijo + 1;
      }

      if (realInfo(swap) > realInfo(cp->heap[p_hijo]))
      {
        cp->heap[pos] = cp->heap[p_hijo];
        cp->posiciones[natInfo(cp->heap[p_hijo])] = pos;
        pos = p_hijo;
      }
      else
        break;
      cp->heap[pos] = swap;
      cp->posiciones[natInfo(swap)] = pos;
    }
  }
  else if (cp->prioridad == false)
  {
    TInfo swap = cp->heap[pos];
    while (tieneHijoIzq(cp, pos))
    {
      nat p_hijo = posIzq(pos);
      if ((p_hijo + 1 <= cp->tope) && (realInfo(cp->heap[(p_hijo)]) < realInfo(cp->heap[(p_hijo) + 1])))
      {
        p_hijo = p_hijo + 1;
      }

      if (realInfo(swap) < realInfo(cp->heap[p_hijo]))
      {
        cp->heap[pos] = cp->heap[p_hijo];
        cp->posiciones[natInfo(cp->heap[p_hijo])] = pos;
        pos = p_hijo;
      }
      else
        break;
      cp->heap[pos] = swap;
      cp->posiciones[natInfo(swap)] = pos;
    }
  }
}

TColaDePrioridad crearCP(nat N)
{
  TColaDePrioridad cp = new _rep_colaDePrioridad;
  cp->tope = 0;
  cp->tamanio = N;
  cp->posiciones = new nat[N + 1];
  cp->heap = new TInfo[N + 1];
  cp->prioridad = true;
  for (nat i = 0; i < N + 1; i++)
  {
    cp->posiciones[i] = 0;
  }
  for (nat j = 0; j < N + 1; j++)
  {
    cp->heap[j] = NULL;
  }
  return cp;
}

TColaDePrioridad invertirPrioridad(TColaDePrioridad cp)
{
  cp->prioridad = !(cp->prioridad);

  for (nat i = 1; i <= cp->tope; i++)
    filtradoAscendente(cp, i);

  return cp;
}

void liberarCP(TColaDePrioridad cp)
{
  for (nat j = 1; j <= cp->tope; j++)
  {
    liberarInfo(cp->heap[j]);
  }
  delete[] cp->heap;
  delete[] cp->posiciones;
  delete cp;
}

TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp)
{

  if (estaEnCP(elem, cp))
  {
    nat pos = cp->posiciones[elem];
    double valorAnt = realInfo(cp->heap[pos]);
    liberarInfo(cp->heap[pos]);
    cp->heap[pos] = crearInfo(elem, valor);
    if (valor > valorAnt)
    {
      filtradoDescendente(cp, pos);
    }
    else
    {
      filtradoAscendente(cp, pos);
    }
  }
  else if ((elem >= 1) && (elem <= cp->tamanio) && (cp->tope < cp->tamanio))
  {
    cp->tope++;
    cp->heap[cp->tope] = crearInfo(elem, valor);
    cp->posiciones[elem] = cp->tope;
    filtradoAscendente(cp, cp->tope);
  }

  // else if (estaVaciaCP(cp))
  // {
  //   cp->tope++;
  //   cp->heap[cp->tope] = crearInfo(elem, valor);
  //   cp->posiciones[elem] = cp->tope;
  // }

  return cp;
}

bool estaVaciaCP(TColaDePrioridad cp)
{
  return (cp->tope == 0);
}

nat prioritario(TColaDePrioridad cp)
{
  return natInfo(cp->heap[1]);
}

TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp)
{
  if (cp->tope > 0)
  {
    cp->posiciones[natInfo(cp->heap[1])] = 0;
    liberarInfo(cp->heap[1]);
    cp->tope--;

    if (cp->tope > 0)
    {
      cp->heap[1] = cp->heap[(cp->tope) + 1];
      cp->posiciones[natInfo(cp->heap[1])] = 1;
      if (cp->tope > 1)
      {
        filtradoDescendente(cp, 1);
      }
    }
  }
  return cp;
}

bool estaEnCP(nat elem, TColaDePrioridad cp)
{
  if ((elem > 0) && (elem <= cp->tamanio))
  {
    return (cp->posiciones[elem] != 0);
  }
  return false;
}

double prioridad(nat elem, TColaDePrioridad cp)
{
  return realInfo(cp->heap[cp->posiciones[elem]]);
}
