/*
  Módulo de definición de `pila_t'.

  `pila_t' es una pila de hasta `CAP_PILA' elementos de tipo char.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _PILA_H
#define _PILA_H

#define CAP_PILA 50

// Declaración del tipo `pila_t. Es de tipo puntero a `rep_pila'.
// struct rep_pila es la representación de `pila_t', definida en pila.cpp
typedef struct rep_pila *pila_t;

/* Operaciones de pila_t */

/*
  Devuelve un elemento de tipo `pila_t' vacío (sin elementos) que puede
  mantener hasta `CAP_PILA\' elementos.
 */
pila_t crear_pila();

/* Devuelve `true' si y solo si `p' no tiene elementos. */
bool es_vacia_pila(pila_t p);

/* Devuelve `true' si y solo si `p' tiene `CAP_PILA' elementos. */
bool es_llena_pila(pila_t p);

/*
   Devulve el resultado de apilar `nuevo' en `p'.
   Precondición: ! es_llena_pila(p).
 */
pila_t apilar(char nuevo, pila_t p);

/*
   Devuelve el tope de `p'.
   Precondición: ! es_vacia_pila(p).
 */
char tope(pila_t p);

/*
   Devulve el resultado de desapilar el tope de `p'.
   Precondición: ! es_vacia_pila(p).
 */
pila_t desapilar(pila_t p);

/* Libera la memoria asignada a `p'. */
void liberar_pila(pila_t &p);

#endif
