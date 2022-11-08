/* 5237782 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/mapping.h"
#include "../include/aplicaciones.h"
#include "../include/colCadenas.h"
#include "../include/cadena.h"
#include "../include/cola.h"
#include "../include/pila.h"
#include "../include/info.h"
#include "../include/abb.h"

struct _rep_mapping
{
    TColCadenas lista;
    nat cantAsoc;
};

TMapping crearMap(nat M)
{
    TMapping map = new _rep_mapping;
    map->cantAsoc = 0;
    map->lista = crearColCadenas(M);
    return map;
}

void liberarMap(TMapping map)
{

    liberarColCadenas(map->lista);
    delete map;
}

TMapping asociarEnMap(nat clave, double valor, TMapping map)
{
    map->lista = insertarEnColCadenas(clave, valor, clave % tamanioColCadenas(map->lista), map->lista);
    map->cantAsoc++;

    return map;
}

TMapping desasociarEnMap(nat clave, TMapping map)
{

    map->lista = removerDeColCadenas(clave, clave % tamanioColCadenas(map->lista), map->lista);
    map->cantAsoc--;
    return map;
}

bool esClaveEnMap(nat clave, TMapping map)
{
    return estaEnColCadenas(clave, clave % tamanioColCadenas(map->lista), map->lista);
}

double valorEnMap(nat clave, TMapping map)
{

    return realInfo(infoEnColCadenas(clave, clave % tamanioColCadenas(map->lista), map->lista));
}

bool estaLlenoMap(TMapping map)
{
    return (tamanioColCadenas(map->lista) == map->cantAsoc);
}
