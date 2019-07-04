/*43073854*/

#include "../include/avl.h"
#include "../include/pila.h"
#include "../include/cola_avls.h"
#include "../include/info.h"


#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>

// Representación de `cola_avls_t'.
// Se debe definir en cola_avls.cpp

struct Nodo {
  avl_t valor;
  Nodo *sig;
};

struct rep_cola_avls{
  Nodo *primero, *ultimo;
};

// Declaración del tipo `cola_avls_t'
typedef struct rep_cola_avls *cola_avls_t;

/*  Devuelve una cola_avls_t vacía (sin elementos). */
cola_avls_t crear_cola_avls(){
  cola_avls_t cola=new rep_cola_avls;
  cola->primero = cola->ultimo = NULL;
  return cola;
}

/* Encola `avl' en `c'. */
void encolar(avl_t b, cola_avls_t &c){

  Nodo *nuevo = new Nodo;
  nuevo->valor =  b;
  nuevo->sig = NULL;
  if (c->primero == NULL) {
    c->primero = nuevo;
  } else {
    c->ultimo->sig = nuevo;
  }
  c->ultimo=nuevo;
}

/*
  Remueve de `c' el elemento que está en el frente.
  NO libera la memoria del elemento removido.
  Si es_vacia_cola_binarios(c) no hace nada.
 */
void desencolar(cola_avls_t &c){
  assert (es_vacia_cola_avls(c));
  Nodo *temp = c->primero;
  c->primero = c->primero->sig;
  if (c->primero == NULL) {
    c->ultimo = NULL;
  }
  delete temp;
}

/* Libera la memoria asignada a `c', pero NO la de sus elementos. */
void liberar_cola_avls(cola_avls_t &c){
  Nodo *temp;
  while (c->primero !=NULL) {
    temp = c->primero;
    c->primero = c->primero->sig;
    delete temp;
  }
  delete c;
}

/* Devuelve `true' si y sólo si `c' es vacía (no tiene elementos). */
bool es_vacia_cola_avls(cola_avls_t c){return c->primero==NULL;}

/*
  Devuelve el elemento que está en el frente de `c'.
  Precondición: ! es_vacia_cola_binarios(c);
 */
avl_t frente(cola_avls_t c){
  assert (!es_vacia_cola_avls(c));
  return c->primero->valor;
}
