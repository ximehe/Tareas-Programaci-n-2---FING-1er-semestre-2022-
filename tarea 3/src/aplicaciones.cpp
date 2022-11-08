/* 5237782 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/aplicaciones.h"
#include <string.h>

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
int max(int a, int b)
{
  if (a > b)
    return a;
  else
    return b;
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
  TPalabras resultado = NULL;
  resultado = auxPrefijo(prefijo, subarboles(palabras), resultado, count);
  return resultado;
}
