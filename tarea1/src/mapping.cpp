/*
  Módulo de implementación de `mapping_t'.

  Se implementa struct rep_mapping como un arreglo con tope.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/mapping.h"


#include <assert.h>

struct asociacion_t {
  char clave;
  char valor;
};

struct rep_map {
  // el rango del arreglo es desde 0 hasta CAPACIDAD - 1
  asociacion_t datos[CAP_MAP];
  // cantidad indica la cantidad de elementos
  //                = posición donde se insertaria el nuevo
  int cantidad;
};

/* Función auxiliar. La palabra reservada 'static' establece que el ámbito de
   la función es solo este archivo. */
/* Devuelve el indice en (*m).datos donde está clave, o -1 si no está. */
static int buscar(char clave, mapping_t m) {
  int i = (*m).cantidad - 1;
  while (i >= 0) {
    if ((*m).datos[i].clave == clave)
      break;
    else
      i--;
  }
  return i;
}

mapping_t crear_map() {
  mapping_t m = new rep_map;
  (*m).cantidad = 0;
  return m;
}

void liberar_map(mapping_t &m) { delete m; }

                                                                               

bool es_lleno_map(mapping_t m) { return (*m).cantidad == CAP_MAP; };

bool es_clave(char clave, mapping_t m) { return buscar(clave, m) != -1; }

bool es_valor(char valor, mapping_t m) {
  int i = (*m).cantidad - 1;
  while (i >= 0) {
    if ((*m).datos[i].valor == valor)
      break;
    else
      i--;
  }
  return i >= 0;
}

mapping_t asociar(char clave, char valor, mapping_t m) {
  assert(!es_lleno_map(m) && !es_clave(clave, m));
  (*m).datos[(*m).cantidad].clave = clave;
  (*m).datos[(*m).cantidad].valor = valor;
  (*m).cantidad++;
  return m;
}

char valor(char clave, mapping_t m) {
  assert(es_clave(clave, m));
  return (*m).datos[buscar(clave, m)].valor;
}

mapping_t desasociar(char clave, mapping_t m) {
  assert(es_clave(clave, m));
  for (int i = buscar(clave, m); i < (*m).cantidad - 1; i++)
    (*m).datos[i] = (*m).datos[i + 1];

  (*m).cantidad--;
  return m;
}
