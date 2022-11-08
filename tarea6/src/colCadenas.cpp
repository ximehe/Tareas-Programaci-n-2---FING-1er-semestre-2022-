//* 5237782 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/aplicaciones.h"
#include "../include/colCadenas.h"
#include "../include/cadena.h"
#include "../include/cola.h"
#include "../include/pila.h"
#include "../include/info.h"
#include "../include/abb.h"

struct _rep_colCadenas
{
  nat cantidad;
  TCadena *cads;
};

TColCadenas crearColCadenas(nat tamanio)
{

  nat i = 0;
  TColCadenas arrCadenas = new _rep_colCadenas;
  arrCadenas->cantidad = tamanio;
  arrCadenas->cads = new TCadena[tamanio];
  while (i < tamanio)
  {
    arrCadenas->cads[i] = crearCadena();
    i++;
  }
  return arrCadenas;
}

void liberarColCadenas(TColCadenas col)
{

  nat i = 0;

  while (i < tamanioColCadenas(col))
  {

    liberarCadena(col->cads[i]);
    i = i + 1;
  }

  delete[] col->cads;
  delete (col);
}

nat tamanioColCadenas(TColCadenas col)
{

  return col->cantidad;
}

TCadena cadenaDeColCadenas(nat pos, TColCadenas col)
{
  return col->cads[pos];
}

nat cantidadColCadenas(nat pos, TColCadenas col)
{
  return cantidadEnCadena(col->cads[pos]);
}

bool estaEnColCadenas(nat natural, nat pos, TColCadenas col)
{
  return estaEnCadena(natural, col->cads[pos]);
}

TColCadenas insertarEnColCadenas(nat natural, double real, nat pos,
                                 TColCadenas col)
{

  col->cads[pos] = insertarAlInicio(natural, real, col->cads[pos]);

  return col;
}

TInfo infoEnColCadenas(nat natural, nat pos, TColCadenas col)
{
  return infoCadena(natural, col->cads[pos]);
}

TColCadenas removerDeColCadenas(nat natural, nat pos, TColCadenas col)
{
  col->cads[pos] = removerDeCadena(natural, col->cads[pos]);
  return col;
}
