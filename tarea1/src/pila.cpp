
/*
  Módulo de implementación de `pila_t'.

  Se implementa struct rep_pila como un arreglo con tope.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/pila.h"

#include <stdlib.h> // NULL
#include <assert.h>

struct rep_pila {
  // el rango del arreglo es desde 0 hasta CAP_PILA - 1
  char datos[CAP_PILA];
  // cantidad indica la cantidad de elementos
  //                = posición donde se insertaria el nuevo
  int cantidad;
};

pila_t crear_pila() {
  pila_t p = new rep_pila;
  (*p).cantidad = 0;
  return p;
}

void liberar_pila(pila_t &p) { delete p; }

                                                                               
bool es_vacia_pila(pila_t p) { return (*p).cantidad == 0; }

bool es_llena_pila(pila_t p) { return (*p).cantidad == CAP_PILA; }

pila_t apilar(char nuevo, pila_t p) {
  assert(!es_llena_pila(p));
  (*p).datos[(*p).cantidad] = nuevo;
  (*p).cantidad++;
  return p;
}

char tope(pila_t p) {
  assert(!es_vacia_pila(p));
  return (*p).datos[(*p).cantidad - 1];
}

pila_t desapilar(pila_t p) {
  assert(!es_vacia_pila(p));
  (*p).cantidad--;
  return p;
}

