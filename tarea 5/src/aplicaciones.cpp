/* 5237782 */ // sustituiir con los 7 dígitos de la cédula
#include "../include/aplicaciones.h"
#include "../include/colCadenas.h"
#include "../include/cadena.h"
#include "../include/cola.h"
#include "../include/pila.h"
#include "../include/info.h"
#include "../include/abb.h"
#include "../include/mapping.h"
#include <string.h>
#include <tgmath.h>

int max(int a, int b)
{
  if (a > b)
    return a;
  else
    return b;
}

int auxEsAvl(TAbb abb, bool &estaBalanc)
{
  if (abb == NULL || !estaBalanc)
  {
    return 0;
  }

  int alturaIzq = auxEsAvl(izquierdo(abb), estaBalanc);
  int alturaDer = auxEsAvl(derecho(abb), estaBalanc);

  if (abs(alturaIzq - alturaDer) > 1)
  {
    estaBalanc = false;
  }
  return max(alturaIzq, alturaDer) + 1;
}

bool esAvl(TAbb abb)
{
  bool estaBalanc = true;
  auxEsAvl(abb, estaBalanc);
  return estaBalanc;
}

// // Función recursiva para verificar si un árbol binario dado está balanceado en altura o no
// int auxEsAvl(TAbb abb, bool &estaBalanc)
// {
//   // caso base: el árbol está vacío o no equilibrado
//   if (abb == NULL || !estaBalanc)
//   {
//     return 0;
//   }

//   // obtener la altura del subárbol izquierdo
//   int alturaIzq = auxEsAvl(izquierdo(abb), estaBalanc);

//   // obtener la altura del subárbol derecho
//   int alturaDer = auxEsAvl(derecho(abb), estaBalanc);

//   // el árbol está desequilibrado si la diferencia absoluta entre la altura de
//   // su subárbol izquierdo y derecho es más de 1
//   if (abs(alturaIzq - alturaDer) > 1)
//   {
//     estaBalanc = false;
//   }

//   // devuelve la altura del subárbol enraizado en el nodo actual
//   return max(alturaIzq, alturaDer) + 1;
// }

// // La función principal para verificar si un árbol binario dado tiene balance de altura o no
// bool esAvl(TAbb abb)
// {
//   bool estaBalanc = true;
//   auxEsAvl(abb, estaBalanc);

//   return estaBalanc;

TAbb auxAvlMin(int &contador, int h)
{
  if (h <= 0)
  {
    return crearAbb();
  }
  else
  {
    TAbb izq;
    TAbb der;
    izq = auxAvlMin(contador, h - 1);
    TInfo elemen = crearInfo(contador, 0);
    contador++;
    der = auxAvlMin(contador, h - 2);
    return consAbb(elemen, izq, der);
  }
}
TAbb avlMin(nat h)
{

  int contador = 1;
  TAbb resultado = auxAvlMin(contador, h);
  return resultado;
}

TCadena filtradaOrdenada(TCadena cad, TIterador it)
{
  TCadena resultado = crearCadena();
  if (cad != NULL)
  {
    reiniciarIterador(it);
    nat tamanioCad = cantidadEnCadena(cad);
    TMapping map = crearMap(tamanioCad);

    for (nat i = 0; i < tamanioCad; i++)
    {
      if (esClaveEnMap(natInfo(primeroEnCadena(cad)), map))
      {
        double real = realInfo(primeroEnCadena(cad));
        double real2 = valorEnMap(natInfo(primeroEnCadena(cad)), map);
        double suma = (real + real2);
        desasociarEnMap(natInfo(primeroEnCadena(cad)), map);
        asociarEnMap(natInfo(primeroEnCadena(cad)), suma, map);
      }
      else
      {
        asociarEnMap(natInfo(primeroEnCadena(cad)), realInfo(primeroEnCadena(cad)), map);
      }

      cad = cadenaSiguiente(cad);
    };

    while (estaDefinidaActual(it))
    {
      if (esClaveEnMap(actualEnIterador(it), map))
      {
        resultado = insertarAlFinal(actualEnIterador(it), valorEnMap(actualEnIterador(it), map), resultado);
      }
      avanzarIterador(it);
    }

    liberarMap(map);
  }

  return resultado;
}

bool estaOrdenada(TCadena cad)
{

  if ((cad == NULL) || (cadenaSiguiente(cad) == NULL))
  {
    return true;
  }
  else

  {
    bool desordenado = false;
    nat tope = cantidadEnCadena(cad);
    nat i = 1;
    while ((i != tope) && (desordenado == false))
    {
      if (natInfo(primeroEnCadena(cad)) < natInfo(primeroEnCadena(cadenaSiguiente(cad))))
      {
        cad = cadenaSiguiente(cad);
        i++;
      }
      else
      {
        desordenado = true;
      }
    }

    if (desordenado)
    {

      return false;
    }
    else
    {
      return true;
    }
  }
}

TCadena mezclaCadenas(TCadena cad1, TCadena cad2)
{

  if ((cad1 == NULL) && (cad2 == NULL))
  {
    return crearCadena();
  }
  else if ((cad1 == NULL) && (cad2 != NULL))
  {
    return copiaCadena(cad2);
  }
  else if ((cad1 != NULL) && (cad2 == NULL))
  {
    return copiaCadena(cad1);
  }
  else
  {
    nat aux1 = 0;
    nat aux2 = 0;
    nat largocad1 = cantidadEnCadena(cad1);
    nat largocad2 = cantidadEnCadena(cad2);

    TCadena nuevaCadena = crearCadena();

    while ((aux1 < largocad1) && (aux2 < largocad2))
    {

      if (natInfo(primeroEnCadena(cad1)) < (natInfo(primeroEnCadena(cad2))))
      {

        nuevaCadena = insertarAlFinal(natInfo(primeroEnCadena(cad1)), realInfo(primeroEnCadena(cad1)), nuevaCadena);
        cad1 = cadenaSiguiente(cad1);
        aux1++;
      }
      else if (natInfo(primeroEnCadena(cad1)) == (natInfo(primeroEnCadena(cad2))))
      {
        nuevaCadena = insertarAlFinal(natInfo(primeroEnCadena(cad1)), realInfo(primeroEnCadena(cad1)), nuevaCadena);
        cad1 = cadenaSiguiente(cad1);
        cad2 = cadenaSiguiente(cad2);
        aux1++;
        aux2++;
      }
      else // cad1 > cad2
      {
        nuevaCadena = insertarAlFinal(natInfo(primeroEnCadena(cad2)), realInfo(primeroEnCadena(cad2)), nuevaCadena);
        cad2 = cadenaSiguiente(cad2);
        aux2++;
      }
    }
    if (aux1 == largocad1)
    {
      while (aux2 < largocad2)
      {
        nuevaCadena = insertarAlFinal(natInfo(primeroEnCadena(cad2)), realInfo(primeroEnCadena(cad2)), nuevaCadena);
        cad2 = cadenaSiguiente(cad2);
        aux2++;
      }
    }
    else
    {
      while (aux1 < largocad1)
      {
        nuevaCadena = insertarAlFinal(natInfo(primeroEnCadena(cad1)), realInfo(primeroEnCadena(cad1)), nuevaCadena);
        cad1 = cadenaSiguiente(cad1);
        aux1++;
      }
    }

    return nuevaCadena;
  }
}

TAbb cbAux(TInfo *arreglo, int comienzo, int final)
{
  if (comienzo == final)
  {
    TAbb abb = crearAbb();
    abb = insertarEnAbb(copiaInfo(arreglo[comienzo]), abb);
    return abb;
  }
  else if (comienzo > final)
  {
    return NULL;
  }
  else
  {
    int medio = ((comienzo + final) / 2);
    return consAbb(copiaInfo(arreglo[medio]), cbAux(arreglo, comienzo, medio - 1), cbAux(arreglo, medio + 1, final));
  }
}

TAbb crearBalanceado(TInfo *arreglo, nat n)
{
  TAbb abb = crearAbb();
  int comienzo = 0;
  int final = n - 1;
  if (n != 0)
  {
    abb = cbAux(arreglo, comienzo, final);
  }
  return abb;
}

TAbb unionAbbs(TAbb abb1, TAbb abb2)
{

  TCadena cad1 = linealizacion(abb1);
  TCadena cad2 = linealizacion(abb2);
  TCadena cad3 = mezclaCadenas(cad1, cad2);

  nat tope = cantidadEnCadena(cad3);
  TInfo *arr = new TInfo[tope];
  nat aux;
  for (aux = 0; aux < tope; aux++)
  {
    arr[aux] = copiaInfo(primeroEnCadena(cad3));
    cad3 = cadenaSiguiente(cad3);
  };

  liberarCadena(cad1);
  liberarCadena(cad2);
  liberarCadena(cad3);
  TAbb abb = crearBalanceado(arr, tope);
  for (nat i = 0; i < tope; i++)
  {
    liberarInfo(arr[i]);
  };
  delete[] arr;

  return abb;
}

TCola ordenadaPorModulo(nat p, TCadena cad)
{
  TCola cola = crearCola();
  // crear array de cadenas
  if (cad != NULL)
  {
    TCadena array[p];
    nat cantElems = cantidadEnCadena(cad);
    nat i;
    nat j;
    nat k;
    // for para llenar el arreglo de cadenas
    for (j = 0; j < p; j++)
    {
      array[j] = crearCadena();
    }
    // hacer un for hasta que se hayan pasado todos los elementos
    for (i = 1; i <= cantElems; i++)
    {
      nat resto = ((natInfo(primeroEnCadena(cad))) % p);
      array[resto] = insertarAlFinal(natInfo(primeroEnCadena(cad)), realInfo(primeroEnCadena(cad)), array[resto]);
      cad = cadenaSiguiente(cad);
    }

    for (k = 0; k < p; k++)
    {
      nat t = 0;
      nat z = cantidadEnCadena(array[k]);
      while (t < z)
      {
        cola = encolar(primeroEnCadena(array[k]), cola);
        array[k] = cadenaSiguiente(array[k]);
        t++;
      };
    };

    nat w;
    for (w = 0; w < p; w++)
    {
      liberarCadena(array[w]);
    }
  }

  return cola;
}

TPila menoresQueElResto(TCadena cad, nat cantidad)
{
  nat cantAux = cantidad;
  TPila pilaResult = crearPila();

  while (cantAux != 0)
  {
    if (cantidadEnPila(pilaResult) == 0)
    {
      pilaResult = apilar(primeroEnCadena(cad), pilaResult);
    }
    else
    {
      if (natInfo(primeroEnCadena(cad)) > natInfo(cima(pilaResult)))
      {
        pilaResult = apilar(primeroEnCadena(cad), pilaResult);
      }
      else
      {
        while ((cantidadEnPila(pilaResult)) != 0 && (natInfo(primeroEnCadena(cad)) <= natInfo(cima(pilaResult))))
        {
          pilaResult = desapilar(pilaResult);
        }
        pilaResult = apilar(primeroEnCadena(cad), pilaResult);
      }
      cad = cadenaSiguiente(cad);
      cantAux--;
    }
  }

  return pilaResult;
}

void listcad(TAbb abb, TCadena &cad)
{
  if (abb != NULL)
  {
    listcad(derecho(abb), cad);
    cad = insertarAlInicio(natInfo(raiz(abb)), realInfo(raiz(abb)), cad);
    listcad(izquierdo(abb), cad);
  }
}

TCadena linealizacion(TAbb abb)
{
  TCadena cad = crearCadena();
  listcad(abb, cad);
  return cad;
}

void auxprint(TAbb abb, nat prof)
{
  if (abb != NULL)
  {
    auxprint(derecho(abb), prof + 1);
    for (nat i = 0; i < prof; i++)
      printf("-");
    imprimirInfo(raiz(abb));
    printf("\n");
    auxprint(izquierdo(abb), prof + 1);
  }
}

void imprimirAbb(TAbb abb)
{
  nat prof = 0;
  auxprint(abb, prof);
}

int altura(TAbb abb)
{
  if (abb == NULL)
  {
    return 0;
  }
  else
    return 1 + max(altura(izquierdo(abb)), altura(derecho(abb)));
}
int hojas(TAbb abb)
{
  if (abb == NULL)
    return 0;
  if (izquierdo(abb) == NULL && derecho(abb) == NULL)
    return 1;
  else
    return hojas(izquierdo(abb)) + hojas(derecho(abb));
}
int calculoPot(int base, int potencia)
{
  if (potencia != 0)
    return (base * calculoPot(base, potencia - 1));
  else
    return 1;
}

bool esPerfecto(TAbb abb)
{
  if (abb == NULL)
    return true;

  return (calculoPot(2, (altura(abb) - 1))) == hojas(abb);
}

TAbb menores(double limite, TAbb abb)
{
  TAbb nuevo;
  if (abb == NULL)
  {
    nuevo = NULL;
  }
  else
  {
    TAbb izqui = menores(limite, izquierdo(abb));
    TAbb dere = menores(limite, derecho(abb));

    if (limite > realInfo(raiz(abb)))
    {
      nuevo = consAbb(copiaInfo(raiz(abb)), izqui, dere);
    }
    else if (izqui == NULL)
      nuevo = dere;
    else if (dere == NULL)
      nuevo = izqui;
    else
    {
      TInfo max = copiaInfo(mayorEnAbb(izqui));
      izqui = removerDeAbb(natInfo(mayorEnAbb(izqui)), izqui);
      nuevo = consAbb(max, izqui, dere);
    }
  }
  return nuevo;
}
TIterador iterAuxi(nat elem, nat k, TAbb abb)
{
  if (k != 0)
  {
    TIterador iter;
    if (abb == NULL)
    {
      return NULL;
    }
    else if (natInfo(raiz(abb)) == elem)
    {

      TIterador iter = crearIterador();
      agregarAIterador(natInfo(raiz(abb)), iter);
      return iter;
    }
    else if (elem < natInfo(raiz(abb)))
    {
      TIterador iter = caminoAscendente(elem, k, izquierdo(abb));
      agregarAIterador(natInfo(raiz(abb)), iter);
      return iter;
    }
    else
    {
      TIterador iter = caminoAscendente(elem, k, derecho(abb));
      agregarAIterador(natInfo(raiz(abb)), iter);
      return iter;
    }
    return iter;
  }
  else
    return crearIterador();
}
TIterador caminoAscendente(nat clave, nat k, TAbb abb)
{
  TIterador iter = iterAuxi(clave, k, abb);
  reiniciarIterador(iter);
  TIterador iterFinal = crearIterador();
  for (nat i = 0; i < k && estaDefinidaActual(iter); i++)
  {
    agregarAIterador(actualEnIterador(iter), iterFinal);
    avanzarIterador(iter);
  }
  liberarIterador(iter);
  return iterFinal;
  return iter;
}

void auxPalabras(TPalabras palabras, nat largo, nat indice, ArregloChars arreglo)
{
  if (letra(palabras) == '\0')
  {
    arreglo[indice] = '\0';
    for (nat i = 1; i < indice; i++)
    {

      printf("%c", arreglo[i]);
    }
    printf("\n");
  }
  else
  {
    if (indice <= largo)
    {
      arreglo[indice] = letra(palabras);
      auxPalabras(subarboles(palabras), largo, indice + 1, arreglo);
    }
  }
  if (siguientes(palabras) != NULL)
    auxPalabras(siguientes(palabras), largo, indice, arreglo);
}
void imprimirPalabrasCortas(nat k, TPalabras palabras)
{
  ArregloChars arreglo = new char[k + 2];
  nat count = 0;
  auxPalabras(palabras, k, count, arreglo);
  delete[] arreglo;
}

TPalabras auxPrefijo(ArregloChars arreglo, TPalabras palabras, TPalabras result, nat indice)
{
  if (indice == strlen(arreglo) - 1 && arreglo[indice] == letra(palabras))
  {
    result = palabras;
    return result;
  }
  if (indice < strlen(arreglo) && arreglo[indice] == letra(palabras))
  {

    if (subarboles(palabras) != NULL)
    {
      result = auxPrefijo(arreglo, subarboles(palabras), result, indice + 1);
      return result;
    }
  }
  if (indice < strlen(arreglo) && arreglo[indice] != letra(palabras))
  {
    if (siguientes(palabras) != NULL && indice < strlen(arreglo))
    {
      result = auxPrefijo(arreglo, siguientes(palabras), result, indice);
      return result;
    }

    return result;
  }
  return result;
}

TPalabras buscarFinPrefijo(ArregloChars prefijo, TPalabras palabras)
{
  nat count = 0;
  TPalabras pilaResult = NULL;
  pilaResult = auxPrefijo(prefijo, subarboles(palabras), pilaResult, count);
  return pilaResult;
}

void ayudaIterador(TIterador iter, TIterador nueva)
{
  if (!estaDefinidaActual(iter))
  {
    return;
  }
  nat aux = actualEnIterador(iter);
  avanzarIterador(iter);

  ayudaIterador(iter, nueva);

  agregarAIterador(aux, nueva);
}

TIterador reversoDeIterador(TIterador iter)
{
  TIterador nueva = crearIterador();
  reiniciarIterador(iter);
  if (!estaDefinidaActual(iter))
  {
    return nueva;
  }

  ayudaIterador(iter, nueva);

  return nueva;
}
