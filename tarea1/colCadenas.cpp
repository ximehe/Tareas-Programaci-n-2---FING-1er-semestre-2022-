#include "../include/colCadenas.h"
#include "../include/cadena.h"
#include "../include/info.h"
struct _rep_colCadenas
{
  TCadena cads[CANT_CADS];
};

TColCadenas crearColCadenas()
{
  int i = 0;
  TColCadenas arrCadenas = new _rep_colCadenas;
  while (i < CANT_CADS)
  {
    arrCadenas->cads[i] = crearCadena();
    i++;
  }
  return arrCadenas;
}

nat cantidadColCadenas(nat pos, TColCadenas col)
{
  return cantidadEnCadena(col->cads[pos]);
}

bool estaEnColCadenas(nat natural, nat pos, TColCadenas col)
{
  return estaEnCadena(natural, col->cads[pos]);
}

TColCadenas insertarEnColCadenas(nat natural, double real, nat pos, TColCadenas col)
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
