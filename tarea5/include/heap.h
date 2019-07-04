/*
  Módulo de definición de `heap_t`.

  Se definen los heap en los que los elementos son de tipo `info_t'.

  La cantidad máxima de elementos que puede contener el heap es `tamanio',
  que es un parámetro pasado al crearlo.

  El valor de los elementos que determina el orden es su dato numerico,
  que debe pertenecer al rango 0 .. `max_valor',
  siendo `max_valor' un parámetro de `crear_heap'.

  No puede haber dos elementos con el mismo dato numerico.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _HEAP_H
#define _HEAP_H

#include "info.h"

// Representación de `heap_t'
// Se debe definir en heap.cpp
struct rep_heap;
// Declaración del tipo `heap_t_t'
typedef rep_heap *heap_t;

/*
  Devuelve un `heap' que puede contener hasta `tamanio' elementos.
  Los datos numéricos pueden estar en el rango 0 .. max_valor.
 */
heap_t crear_heap(nat tamanio, nat max_valor);

/*
  Si inserta el elemento `i'.
  Precondición: !es_lleno_heap(h) y !hay_valor(v,h) y v <= max_valor(h),
  donde v = numero_info(i).
  El tiempo de ejecución es O(log tamanio).
 */
void insertar_en_heap(info_t i, heap_t &h);

/*
  Reduce a v/2 el valor del elemento cuyo valor actual es `v'.
  Precondición: hay_valor(v, h) y !hay_valor(v/2, h).
  No debe quedar memoria inaccesible.
  El tiempo de ejecución es O(log tamanio).
 */
void reducir(nat v, heap_t &h);

/*
  Elimina de 'h' el elemento de menor valor y libera la memoria que tiene
  asignada.
  Precondición: ! es_vacia_heap(h).
  El tiempo de ejecución es O(log tamanio).
 */
void eliminar_menor(heap_t &h);

/*  Libera la menoria asignada a `h' y a sus elementos. */
void liberar_heap(heap_t &h);

/*
  Devuelve `true' si y sólo si en `h' no hay elementos.
  El tiempo de ejecución es O(1).
 */
bool es_vacio_heap(heap_t h);

/*
  Devuelve `true' si y sólo si en `h' hay `tamanio' elementos.
  El tiempo de ejecución es O(1).
 */
bool es_lleno_heap(heap_t h);

/*
  Devuelve `true' si y sólo si en 'h' hay un elemento con valor `v'.
  El tiempo de ejecución es O(1).
 */
bool hay_valor(nat v, heap_t h);

/*
  Devuelve el elemento de 'h' con menor valor.
  Precondición: ! es_vacio_h(h).
  El tiempo de ejecución es O(1).
 */
info_t menor(heap_t h);

/*
  Devuelve el máximo valor del rango para los datos numericos, establecido en
  crear_h.
 */
nat max_valor(heap_t h);

#endif
