/* 5237782 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/colCadenas.h"

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

void liberarColCadenas(TColCadenas col)
{
  // int i = 0;

  // while (i < CANT_CADS)
  // {
  //   liberarCadena(col->cads[i]);
  //   i = i + 1;
  // }
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
