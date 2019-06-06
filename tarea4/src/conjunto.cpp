/*43073854*/

#include "../include/info.h"
#include "../include/iterador.h"
#include "../include/avl.h"
#include "../include/conjunto.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>


// Declaración del tipo `conjunto_t'
// struct rep_conjunto es la representación de `conjunto_t',
// definida en conjunto.cpp
struct rep_conjunto {
  avl_t arbol;
};
typedef struct rep_conjunto *conjunto_t;

/* Constructoras */

/*
  Devuelve un conjunto_t vacío (sin elementos).
  El tiempo de ejecución es O(1).
 */
conjunto_t crear_conjunto(){
  conjunto_t nuevo = new rep_conjunto;
  nuevo->arbol=crear_avl();
  return nuevo;
}

/*
  Devuelve un conjunto_t cuyo único elemento es `i'.
  El tiempo de ejecución es O(1).
 */
conjunto_t singleton(info_t i){
  conjunto_t res = crear_conjunto();
  avl_t arbol = crear_avl();
  insertar_en_avl(i, arbol);
  res->arbol = arbol;
  return res;
}

/*
  Devuelve un conjunto_t con los elementos que pertenecen a  `c1' o `c2'.
  Si en ambos conjuntos hay un elemento con el mismo dato  numérico en el
  conjunto_t devuelto se debe incluir el que pertenece a `c1'.
  El tiempo de ejecucion es O(n1 + n2 + n.log n), siendo `n1' y `n2' la
  cantidad de elementos de `c1' y `c2' respectivamente y `n' la del conjunto_t
  resultado.
  El conjunto_t devuelto no comparte memoria ni con `c1' no con `c2'.
 */
conjunto_t union_conjunto(conjunto_t c1, conjunto_t c2){
  conjunto_t res = crear_conjunto();
  iterador_t res_iter = crear_iterador();
  avl_t arbol=crear_avl();
  if ((!es_vacio_conjunto(c1)) && (es_vacio_conjunto(c2))) {
    iterador_t iterador = iterador_conjunto(c1);
    while (actual_en_iterador(iterador)) {
      agregar_a_iterador(actual_en_iterador(iterador), res_iter);
      avanzar_iterador(iterador);
    }
    liberar_iterador(iterador);
  } else if ((es_vacio_conjunto(c1)) && (!es_vacio_conjunto(c2))) {
    iterador_t iterador = iterador_conjunto(c2);
    while (esta_definida_actual(iterador)) {
      agregar_a_iterador(actual_en_iterador(iterador), res_iter);
      avanzar_iterador(iterador);
    }
    liberar_iterador(iterador);
  } else if ((!es_vacio_conjunto(c1)) && (!es_vacio_conjunto(c2))) {
    iterador_t iterador1 = iterador_conjunto(c1);
    iterador_t iterador2 = iterador_conjunto(c2);
    reiniciar_iterador(iterador1);
    reiniciar_iterador(iterador2);
    while (esta_definida_actual(iterador1)) {
      agregar_a_iterador(actual_en_iterador(iterador1), res_iter);
      avanzar_iterador(iterador1);
    }
    while (esta_definida_actual(iterador2)) {
      if (es_vacio_avl(buscar_en_avl(numero_info(actual_en_iterador(iterador2)), c1->arbol))) {
        agregar_a_iterador(actual_en_iterador(iterador2), res_iter);
      }
      avanzar_iterador(iterador2);
    }
    liberar_iterador(iterador1);
    liberar_iterador(iterador2);
  }
  //Agrego al avl todos los elementos del iterador que salio de arriba.
  bloquear_iterador(res_iter);
  reiniciar_iterador(res_iter);
  while (esta_definida_actual(res_iter)) {
    info_t agrego = copia_info(actual_en_iterador(res_iter));
    insertar_en_avl(agrego, arbol);
    avanzar_iterador(res_iter);
  }
  res->arbol = arbol;
  liberar_iterador(res_iter);
  return res;
}

/*
  Devuelve un conjunto_t con los elementos de `c1' cuyos datos numéricos no
  pertenecen a `c2'.
  El tiempo de ejecucion es O(n1 + n2 + n.log n), siendo `n1' y `n2' la
  cantidad de elementos de `c1' y `c2' respectivamente y `n' la del conjunto_t
  resultado.
  El conjunto_t devuelto no comparte memoria ni con `c1' no con `c2'.
 */
conjunto_t diferencia(conjunto_t c1, conjunto_t c2){
  conjunto_t res = new rep_conjunto;
  iterador_t res_iter = crear_iterador();
  avl_t arbol=crear_avl();
  if ((!es_vacio_conjunto(c1)) && (es_vacio_conjunto(c2))) { //agrego todos
    iterador_t iterador = iterador_conjunto(c1);
    while (actual_en_iterador(iterador)) {
      agregar_a_iterador(actual_en_iterador(iterador), res_iter);
      avanzar_iterador(iterador);
    }
    liberar_iterador(iterador);
  } else if ((!es_vacio_conjunto(c1)) && (!es_vacio_conjunto(c2))) {
    iterador_t iterador1 = iterador_conjunto(c1);
    reiniciar_iterador(iterador1);
    while (esta_definida_actual(iterador1)) {
      if (!buscar_en_avl(numero_info(actual_en_iterador(iterador1)), c2->arbol)) {
        agregar_a_iterador(actual_en_iterador(iterador1), res_iter);
      }
      avanzar_iterador(iterador1);
    }
    liberar_iterador(iterador1);
  }
  //Agrego al avl todos los elementos del iterador que salio de arriba.
  bloquear_iterador(res_iter);
  reiniciar_iterador(res_iter);
  while (esta_definida_actual(res_iter)) {
    info_t agrego = copia_info(actual_en_iterador(res_iter));
    insertar_en_avl(agrego, arbol);
    avanzar_iterador(res_iter);
  }
  res->arbol = arbol;
  liberar_iterador(res_iter);
  return res;
}

/*
  Libera la memoria asignada a `c' y la de todos sus elementos.
  El tiempo de ejecución es O(n), siendo `n' la cantidad de elementos de `c'.
 */
void liberar_conjunto(conjunto_t &c){
  if (c!=NULL){
    liberar_avl(c->arbol);
    delete c;
  }
}

/*
  Devuelve `true' si y sólo si `info' es un elemento de `c'.
  El tiempo de ejecución es O(log n), siendo `n' es la cantidad de
  elementos de `c'.
 */
bool pertenece_conjunto(info_t info, conjunto_t s){
  bool res = false;
  if (!es_vacio_conjunto(s)) {
    avl_t aux = buscar_en_avl(numero_info(info), s->arbol);
    if ((aux!=NULL) && (son_iguales(info, raiz_avl(aux)))) {
      res = true;
    }
  }
  return res;
}

/*
  Devuelve `true' si y sólo `c' es vacío (no tiene elementos).
  El tiempo de ejecución es O(1).
 */
bool es_vacio_conjunto(conjunto_t c){
  if(c==NULL) {
    printf("%s\n", "me tiran una mierda!!!");
    return true;
  }
  return es_vacio_avl(c->arbol);
}

/*
  Devuelve un conjunto_t con los `n' elementos que están en en el rango
  [0 .. n - 1] del arreglo `infos'.
  Los elementos están ordenados de manera creciente estricto (creciente y sin
  repetidos) según los datos numércos.
  El tiempo de ejecución es O(n).
 */
conjunto_t arreglo_a_conjunto(info_t *infos, nat n){ //esta esta fallando
  conjunto_t res = new rep_conjunto;
  res->arbol = arreglo_a_avl(infos, n);
  return res;
}

/*
  Devuelve un iterador_t de los elementos de `c'.
  En la recorrida del iterador devuelto los datos numéricos aparecerán en orden
  creciente.
  El tiempo de ejecución es O(n), siendo `n' es la cantidad de elementos de `c'.
  El iterador_t resultado NO comparte memoria con `c'.
 */
iterador_t iterador_conjunto(conjunto_t c){
  iterador_t res = crear_iterador();
  info_t *infos = en_orden_avl(c->arbol);
  for (nat i = 0; i<cantidad_en_avl(c->arbol);i++) {
    agregar_a_iterador(infos[i], res);
  }
  bloquear_iterador(res);
  delete[] infos;
  return res;
}
