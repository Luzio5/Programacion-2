/*
  Módulo de definición de `mapping_t'.

  `mapping_t' es una mapping de hasta `CAP_MAP' asociaciones de elementos de
   tipo char con elementos de tipo char.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _MAPPIBG_H
#define _MAPPIBG_H

#define CAP_MAP 30

// Declaración del tipo `mapping_t. Es de tipo puntero a `rep_map'.
// struct rep_map es la representación de `mapping_t', definida en mapping.cpp
typedef struct rep_map *mapping_t;

/* Operaciones de mapping_t */

/*
   Devuelve un elemento de tipo `mapping_t' vacío (sin elementos) que puede
   mantener hasta `CAP_MAP' asociaciones.
 */
mapping_t crear_map();

/* Devuelve `true' si y solo si `m' tiene CAP_MAP asociaciones. */
bool es_lleno_map(mapping_t m);

/* Devuelve `true' si y solo si `clave' tiene un valor asociado en `m'. */
bool es_clave(char clave, mapping_t m);

/*
   Devuelve el resultado de agregar en `m' la asociación (clave,valor).
   Precondición: !es_lleno_map(m) && !es_clave(clave, m)
 */
mapping_t asociar(char clave, char valor, mapping_t m);

/*
   Devuelve el valor que en `m' está asociado a `clave'.
   Precondición: es_clave(clave, m)
 */
char valor(char clave, mapping_t m);

/*
   Devuelve el resultado de remover de `m' la asociación de `clave' con su
   valor.
   Precondición: es_clave(clave, m)
 */
mapping_t desasociar(char clave, mapping_t m);

// Operación que extiende el TAD mapping estándar
/* Devuelve `true' si y solo si `valor' está asociado a una clave en `m'. */
bool es_valor(char valor, mapping_t m);

/* Libera la memoria asignada a `m'. */
void liberar_map(mapping_t &m);

#endif
