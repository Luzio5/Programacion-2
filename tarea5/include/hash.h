/*
  Módulo de definición de `hash_t'.

  Se define un hash de asociaciones de número a texto.
  La cantidad máxima de asociaciones queda determinada por el parámetro
  `tamanio' pasado en `crear_tabla'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _HASH_H
#define _HASH_H

#include "../include/cadena.h"

// Representación de `hash_t'.
// Se debe definir en hash.cpp.
struct rep_hash;
// Declaración del tipo `hash_t'.
typedef rep_hash *hash_t;

/*
 Crea un hash_t de asociaciones numero->texto.
 Podrá haber hasta `tamanio' asociaciones.
 */
hash_t crear_hash(nat tamanio);

/*
  Inserta en `h' la asociación entre `clave' y `valor'.
  Precondición: !esta_lleno_hash(t) y !existe_asociacion(clave, h).
  El tiempo de ejecución es O(1).
 */
void asociar_en_hash(int clave, char *valor, hash_t &h);

/*
  Sustituye en `h' el anterior valor asociado a `clave' por `valor'.
  Precondición: existe_asociacion(clave, h).
  El tiempo de ejecución es O(1).
 */
void actualizar_hash(int clave, char *valor, hash_t &h);

/*
  Elimina de `h' la asociación entre `clave' y algún valor y libera la menoria
  asignada a mantener esa asociación.
  Precondición: existe_asociacion(clave, h).
  El tiempo de ejecución es O(1) en promedio.
 */
void eliminar_de_hash(int clave, hash_t &h);

/*
  Libera la memoria asignada a `h' y todos sus elementos.
 */
void liberar_hash(hash_t &h);

/*
  Devuelve `true' si y sólo si en `h' hay una asociación entre `clave'
  y algún valor.
  El tiempo de ejecución es O(1) en promedio.
 */
bool existe_asociacion(int clave, hash_t h);

/*
  Devuelve el valor correspondiente a la asociacion de `clave' en `h'.
  Precondición: existe_asociacion(clave, h).
  El tiempo de ejecución es O(1) en promedio.
 */
char *valor_en_hash(int clave, hash_t h);

/*
  Devuelve `true' si y sólo si `h' tiene `tamanio' elementos.
  El tiempo de ejecución es O(1).
 */
bool esta_lleno_hash(hash_t h);

#endif
