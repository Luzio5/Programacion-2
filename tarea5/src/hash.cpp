/*43073854*/

/*
  Módulo de definición de `hash_t'.

  Se define un hash de asociaciones de número a texto.
  La cantidad máxima de asociaciones queda determinada por el parámetro
  `tamanio' pasado en `crear_tabla'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/cadena.h"
#include "../include/binario.h"
#include "../include/info.h"
#include "../include/hash.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>//PAra ver si anda con los negativos

// Representación de `hash_t'.
// Se debe definir en hash.cpp.
struct bucket{
  cadena_t cad;
};

struct rep_hash {
  bucket *buckets;
  nat tamanio;
  nat elem;//AGREGO esto poara chequear si esta lleno o no
};

// Declaración del tipo `hash_t'.
typedef rep_hash *hash_t;

/*
 Crea un hash_t de asociaciones numero->texto.
 Podrá haber hasta `tamanio' asociaciones.
 */
hash_t crear_hash(nat tamanio){
  hash_t hash = new rep_hash;
  hash->buckets = new bucket[937];//uso 937 como primo
  hash->tamanio = tamanio;
  hash->elem=0;
  for (nat i=0; i<937; i++) {
    hash->buckets[i].cad = crear_cadena();
  }
  return hash;
}

/*
  Inserta en `h' la asociación entre `clave' y `valor'.
  Precondición: !esta_lleno_hash(t) y !existe_asociacion(clave, h).
  El tiempo de ejecución es O(1).
 */
static int func_eval(int clave, hash_t h) { //asocia clave a un lugar en el hash
  int res;
  if (clave>=0){
    res=clave%937;
  } else {
    res=(clave*(-23))%937;
  }
  return res;
}

//static info_t par_val_cla(char *valor, )

void asociar_en_hash(int clave, char *valor, hash_t &h){
  assert(!esta_lleno_hash(h));
  assert(!existe_asociacion(clave, h));
  info_t nuevo =crear_info(clave, valor); //deberia tener memoria propia
  int bin = 0;
  bin = func_eval(clave,h);
  h->buckets[bin].cad=insertar_al_final(nuevo,h->buckets[bin].cad);
  h->elem = h->elem+1;
}

/*
  Sustituye en `h' el anterior valor asociado a `clave' por `valor'.
  Precondición: existe_asociacion(clave, h).
  El tiempo de ejecución es O(1).
 */
void actualizar_hash(int clave, char *valor, hash_t &h){
  assert(existe_asociacion(clave, h));
  int bin= func_eval(clave,h);
  info_t nuevo = crear_info(clave, valor);
  h->buckets[bin].cad=insertar_al_final(nuevo,h->buckets[bin].cad);
  localizador_t bin_borrar = siguiente_clave(clave, inicio_cadena(h->buckets[bin].cad), h->buckets[bin].cad);
  h->buckets[bin].cad=remover_de_cadena(bin_borrar, h->buckets[bin].cad);
}

/*
  Elimina de `h' la asociación entre `clave' y algún valor y libera la menoria
  asignada a mantener esa asociación.
  Precondición: existe_asociacion(clave, h).
  El tiempo de ejecución es O(1) en promedio.
 */
void eliminar_de_hash(int clave, hash_t &h){
  assert(existe_asociacion(clave, h));
  int bin= func_eval(clave,h);
  localizador_t bin_borrar = siguiente_clave(clave, inicio_cadena(h->buckets[bin].cad), h->buckets[bin].cad);
  h->buckets[bin].cad=remover_de_cadena(bin_borrar, h->buckets[bin].cad);
  h->elem=h->elem-1;
}

/*
  Libera la memoria asignada a `h' y todos sus elementos.
 */
void liberar_hash(hash_t &h){
  for (nat i=0; i<937; i++) {
    h->buckets[i].cad = liberar_cadena(h->buckets[i].cad);
  }
  delete[] h->buckets;
  delete h;
}

/*
  Devuelve `true' si y sólo si en `h' hay una asociación entre `clave'
  y algún valor.
  El tiempo de ejecución es O(1) en promedio.
 */
bool existe_asociacion(int clave, hash_t h){
  int bin = func_eval(clave,h);
  bool res=false;
  if (!es_vacia_cadena(h->buckets[bin].cad)) {
    res = true;
  }
  return res;
}
/*
  Devuelve el valor correspondiente a la asociacion de `clave' en `h'.
  Precondición: existe_asociacion(clave, h).
  El tiempo de ejecución es O(1) en promedio.
 */
char *valor_en_hash(int clave, hash_t h){
  assert(existe_asociacion(clave,h));
  int bin = func_eval(clave,h);
  return frase_info(info_cadena(inicio_cadena(h->buckets[bin].cad), h->buckets[bin].cad));
}

/*
  Devuelve `true' si y sólo si `h' tiene `tamanio' elementos.
  El tiempo de ejecución es O(1).
 */
bool esta_lleno_hash(hash_t h){
  bool res=false;
  if (h->elem == h->tamanio){
    res=true;
  }
  return res;
}
