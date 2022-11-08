/* 5237782 */ // sustituiir con los 7 dígitos de la cédula

/*
  MÃ³dulo de definiciÃ³n de 'TIterador'.

  Los elementos de tipo 'TIterador' son estructuras para recorrer colecciones
  lineales de elementos de tipo 'nat'.
  Tiene implÃ­cita una posiciÃ³n actual.

  La posiciÃ³n actual no estÃ¡ definida si la colecciÃ³n es vacÃ­a o si se avanza
  cuando la posiciÃ³n  es la Ãºltima.

  El valor de una variable de tipo 'TIterador' no cambia una vez que es asignada.
  Esto significa, dado que son punteros, que la direcciÃ³n de memoria a la que
  apuntan no cambia. SÃ­ puede cambiar el contenido de esa direcciÃ³n.

  SeudocÃ³digo de una recorrida de un iterador:
  reiniciar
  mientras la posiciÃ³n actual estÃ¡ definida
    procesar el elemento definido por la posiciÃ³n actual
    avanzar

  Laboratorio de ProgramaciÃ³n 2.
  InCo-FIng-UDELAR
 */
#include "../include/iterador.h"

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

  /*
  Devuelve un 'TIterador' vacÃ­o (sin elementos) cuya posiciÃ³n actual no estÃ¡
  definida.
 */
}

void liberarIterador(TIterador iter)
{
  TIterador aux = iter;
  // Pregunto si iter tiene solo un elemento en la lista, si es asi, lo borro.
  if (aux->primero == aux->ultimo)
  {
    delete aux;
  }
  else
  { // sino, recorro hasta llegar al penultimo elemento y voy borrando.

    while (iter->actual != iter->ultimo)
    {

      aux = iter;
      iter->actual = iter->actual->sig;
      delete aux;
    }

    // borro el ultimo

    delete iter;
  }
  // Libera la memoria asignada a 'iter'.
}

bool estaDefinidaActual(TIterador iter)
{

  if ((iter->actual == NULL) || (iter->actual = iter->ultimo))
  {
    return false;
  }
  else
  {
    return true;
  }

  /*
  Devuelve 'true' si y solo si la posiciÃ³n actual de 'iter' estÃ¡ definida.
  No se recorre la estructura.
 */

  // La posiciÃ³n actual no estÃ¡ definida si la colecciÃ³n es vacÃ­a o si se avanza
  // cuando la posiciÃ³n  es la Ãºltima.
}

void agregarAIterador(nat elem, TIterador const iter)
{

  nodo *nuevo = new nodo;
  nuevo->elemen = elem;
  nuevo->sig = NULL;
  iter->ultimo->sig = nuevo;
  iter->ultimo = nuevo;
  /*
  Agrega 'elem' al final de 'iter'.
  La posiciÃ³n actual no se modifica.
  No se recorre la estructura.
  No se modifica el valor (direcciÃ³n de memoria) de la variable 'iter'.
 */
}

void reiniciarIterador(TIterador const iter)
{
  if (iter != NULL)
  {
    iter->actual = iter->primero;
  }
  /*
  Mueve la posiciÃ³n actual de 'iter' al primero si y solo si 'iter' tiene
  elementos.
  No se recorre la estructura.
  No se modifica el valor (direcciÃ³n de memoria) de la variable 'iter'.
 */
}

void avanzarIterador(TIterador const iter)
{
  if (iter->actual == iter->ultimo)
  {
    iter->actual->sig = NULL;
  }
  else if (estaDefinidaActual(iter))
  {
    iter->actual = iter->actual->sig;
  }
  /*
  Avanza la posiciÃ³n actual de 'iter' hacia el siguiente si
  estaDefinidaActual(iter).
  En otro caso no tiene efecto.
  Si la posiciÃ³n actual es la Ãºltima posiciÃ³n entonces la posiciÃ³n actual
  queda indefinida.
  No se recorre la estructura.
  No se modifica el valor (direcciÃ³n de memoria) de la variable 'iter'.
 */
}

nat actualEnIterador(TIterador iter)
{

  return iter->actual->elemen;

  /*
  Devuelve el elemento de la posiciÃ³n actual de 'iter'.
  PrecondiciÃ³n: estaDefinidaActual(iter).
  No se recorre la estructura.
 */
}
