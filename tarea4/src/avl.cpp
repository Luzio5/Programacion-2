/*43073854*/

#include "../include/info.h"
#include "../include/avl.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>

// Representación de `avl_t'.
// Se debe definir en avl.cpp.
struct rep_avl {
  info_t dato;
  nat altura;
  nat cantidad;
  rep_avl *izq;
  rep_avl *der;
};

typedef rep_avl *avl_t;

static nat maximo(nat n1, nat n2) {return (n1>=n2) ? n1 : n2;}


/*
  Devuelve un avl_t vacío (sin elementos).
  El tiempo de ejecución es O(1).
 */
avl_t crear_avl(){
  return NULL;
}

/*
  Devuelve `true' si y sólo si `avl' es vacío (no tiene elementos).
  El tiempo de ejecución es O(1).
 */
bool es_vacio_avl(avl_t avl){return avl==NULL;}

/*
  Inserta `i' en `avl' respetando la propiedad de orden definida.
  Precondición: es_vacio_avl(buscar_en_avl(numero_info(i), avl).
  Precondición: numero_info(i) != INT_MAX.
  El tiempo de ejecución es O(log n), donde `n' es la cantidad de elementos
  de `avl'.
*/
static avl_t rotacionsimplederecha (avl_t &avl) {
  avl_t aux = avl->izq;
  avl->izq=aux->der;
  aux->der = avl;
  nat cant = avl->cantidad;
  avl->cantidad = aux->cantidad;
  aux->cantidad = cant;
  avl->altura = maximo(altura_de_avl(avl->izq) , altura_de_avl(avl->der))+1;
  aux->altura = maximo(altura_de_avl(avl->izq) , altura_de_avl(avl))+1;
  return aux;
}

static avl_t rotacionsimpleizquierda (avl_t &avl) {
  avl_t aux = avl->der;
  avl->der=aux->izq;
  aux->izq = avl;
  nat cant = avl->cantidad;
  avl->cantidad = aux->cantidad;
  aux->cantidad = cant;
  avl->altura = maximo(altura_de_avl(avl->izq) , altura_de_avl(avl->der))+1;
  aux->altura = maximo(altura_de_avl(avl->der) , altura_de_avl(avl))+1;
  return aux;
}

static avl_t doblerotacionizquierda (avl_t &avl) {
  avl->der = rotacionsimplederecha(avl->der);
  return rotacionsimpleizquierda(avl);
}

static avl_t doblerotacionderecha (avl_t &avl) {
  avl->izq = rotacionsimpleizquierda(avl->izq);
  return rotacionsimplederecha(avl);
}

void insertar_en_avl(info_t i, avl_t &avl){
  assert (es_vacio_avl(buscar_en_avl(numero_info(i), avl)));
  assert (numero_info(i) != INT_MAX);
  if (avl == NULL) {
    avl = new rep_avl;
    avl->dato = i;
    avl->izq = NULL;
    avl->der = NULL;
    avl->cantidad = 1;
    avl->altura = maximo(altura_de_avl(avl->izq) , altura_de_avl(avl->der))+1;
  } else if (numero_info(i) < numero_info(avl->dato)) {
    insertar_en_avl(i, avl->izq);
    if ((altura_de_avl(avl->izq)) - (altura_de_avl(avl->der)) ==2) {
      if (numero_info(i) < numero_info(avl->izq->dato)) {
        avl= rotacionsimplederecha(avl);
      } else {
        avl = doblerotacionderecha(avl);
      }
    }
    avl->cantidad = cantidad_en_avl(avl) + 1;
    avl->altura = maximo(altura_de_avl(avl->izq) , altura_de_avl(avl->der))+1;
  } else if (numero_info(i) > numero_info(avl->dato)) {
      insertar_en_avl(i, avl->der);
      if(altura_de_avl(avl->der) - (altura_de_avl(avl->izq)) == 2) {
        if (numero_info(i) > numero_info(avl->der->dato)) {
          avl = rotacionsimpleizquierda(avl);
        } else {
          avl = doblerotacionizquierda(avl);
        }
      }
      avl->cantidad = cantidad_en_avl(avl) + 1;
      avl->altura = maximo(altura_de_avl(avl->izq) , altura_de_avl(avl->der))+1;
    }
  }


/*
  Devuelve el subárbol que tiene como raíz al nodo con el elemento cuyo dato
  numérico es `clave'.
  Si ningún nodo cumple esa condición devuelve el árbol vacío.
  El tiempo de ejecución es O(log n), donde `n' es la cantidad de elementos de
  `avl'.
 */
avl_t buscar_en_avl(int clave, avl_t avl){
  avl_t res=NULL;
  while ((avl!=NULL) && (numero_info(raiz_avl(avl))!=clave)) {
    if (numero_info(raiz_avl(avl))<clave) {
      avl=avl->der;
    } else if (numero_info(raiz_avl(avl))>clave) {
      avl=avl->izq;
    }
  }
  if (avl!=NULL) {
    res = avl;
  }
  return res;
}

/*
  Devuelve el elemento asociado a la raíz de `avl'.
  Precondición: ! es_vacio_avl(b).
  El tiempo de ejecución es O(1).
 */
info_t raiz_avl(avl_t avl){
  assert (!es_vacio_avl(avl));
  return (avl->dato);
}

/*
  Devuelve el subárbol izquierdo de `avl'.
  Precondición: ! es_vacio_avl(avl).
  El tiempo de ejecución es O(1).
 */
avl_t izq_avl(avl_t avl){
  assert (!es_vacio_avl(avl));
  return avl->izq;
}

/*
  Devuelve el subárbol derecho de `avl'.
  Precondición: ! es_vacio_avl(avl).
  El tiempo de ejecución es O(1).
 */
avl_t der_avl(avl_t avl){
  assert (!es_vacio_avl(avl));
  return avl->der;
}

/*
  Devuelve la cantidad de elementos en `avl'.
  El tiempo de ejecución es O(1).
 */
nat cantidad_en_avl(avl_t avl){
  if (avl==NULL) {
    return 0;
  } else {
    return 1+cantidad_en_avl(avl->izq)+cantidad_en_avl(avl->der);
  }
}

/*
  Devuelve la altura de  `avl'.
  La altura de un árbol vacío es 0.
  El tiempo de ejecución es O(1).
 */
nat altura_de_avl(avl_t avl){
  if (avl==NULL) {
    return 0;
  } else {
    return 1+maximo(altura_de_avl(avl->izq) , altura_de_avl(avl->der));
  }
}

static info_t *en_orden_rec(info_t *res, nat &tope, avl_t avl) {
  if (!es_vacio_avl(avl)) {
    res = en_orden_rec(res, tope, izq_avl(avl));
    res[tope] = raiz_avl(avl);
    tope++;
    res = en_orden_rec(res, tope, der_avl(avl));
  }
  return res;
}

/*
  Devuelve un arreglo con los elementos de `avl'.
  Los elementos en el arreglo deben estar en orden creciente según los datos
  numericos.
 */
info_t *en_orden_avl(avl_t avl){
  info_t *res;
  if (es_vacio_avl(avl))
    res = NULL;
  else {
    res = new info_t[cantidad_en_avl(avl)];
    nat tope = 0;
    res = en_orden_rec(res, tope, avl);
  }

  return res;
}

/*
  Devuelve un avl_t con los `n' elementos que están en el rango [0 .. n - 1]
  del arreglo `infos'.
  Los elementos están ordenados de manera creciente estricto (creciente y sin
  repetidos) según los datos numércos.
  En cada nodo del árbol resultado la cantidad de elementos de su subárbol
  izquierdo es igual a, o 1 menos que, la cantidad de elementos de su subárbol
  derecho.
  El tiempo de ejecución es O(n).
 */

 static avl_t a2avl_rec(info_t *infos, int inf, int sup) {
   avl_t res;
   if (inf > sup)
     res = NULL;
   else {
     nat medio = (inf + sup) / 2;
     res = new rep_avl;
     res->dato = infos[medio];
     res->izq = a2avl_rec(infos, inf, medio - 1);
     res->der = a2avl_rec(infos, medio+1, sup);
     nat cant = cantidad_en_avl(res);
     res->cantidad = cant;
     res->altura = altura_de_avl(res);
   }
   return res;
 }

avl_t arreglo_a_avl(info_t *infos, nat n){

  return a2avl_rec(infos, 0, n-1);
}


struct avl_ultimo {
  avl_t avl;
  int ultimo;
};
static avl_ultimo avl_min_rec(nat h, nat primero) {
  avl_ultimo res;
  if (h==0) {
    res.avl = NULL;
    res.ultimo = primero-1;
  } else if (h ==1) {
    res.avl = crear_avl();
    info_t nuevo = crear_info(primero,NULL);
    insertar_en_avl(nuevo, res.avl);
    res.ultimo=primero;
  } else {
    avl_t nuevo_avl = new rep_avl;
    nuevo_avl->altura=h;
    avl_ultimo recur_izq=avl_min_rec(h-1,primero);
    nat aux = recur_izq.ultimo+1;
    res.ultimo = maximo(recur_izq.ultimo,aux);
    info_t nuevo = crear_info(aux,NULL);
    nuevo_avl->dato = nuevo;
    nuevo_avl->izq=recur_izq.avl;
    nat primero_der = res.ultimo+1;
    avl_ultimo recur_der=avl_min_rec(h-2, primero_der);
    res.ultimo = maximo(recur_der.ultimo,aux);
    nuevo_avl->der=recur_der.avl;
    nuevo_avl->cantidad=cantidad_en_avl(nuevo_avl);
    res.avl = nuevo_avl;
  }
  return res;
}

/*
  Devuelve un avl_t de altura `h' con `n' nodos, siendo `n' la mínima cantidad
  de elementos que puede tener un avl de altura `h'.
  Los datos numéricos de los elementos van desde 1 hasta `n'.
  El dato de texto de cada elemento es la cadena vacia.
  En ningún nodo puede ocurrir que el subárbol derecho tenga más nodos que el
  subárbol izquierdo.
  El tiempo de ejecución es O(n).
  Ver ejemplos en la letra y en el caso 408.
 */
avl_t avl_min(nat h){
  avl_ultimo res = avl_min_rec(h,1);
  return res.avl;
}

/*
  Imprime los datos numéricos de los nodos de cada nivel de `avl'.
  Imprime una línea por nivel, primero el más profundo y al final el que
  corresponde a la raíz.
  Cada nivel se imprime de izquierda a derecha. Se debe dejar un espacio en
  blanco después de cada número.
  El tiempo de ejecución es O(n), siendo `n' la cantidad de nodos de `avl'.
  Ver ejemplos en la letra y en el caso 404.
 */
static void imprimir_nivel(avl_t avl, nat nivel){
  if (es_vacio_avl(avl)) {
    return;
  } else if (nivel == 1) {
      printf("%d ", numero_info(avl->dato));
  } else {
    imprimir_nivel(avl->izq, nivel-1);
    imprimir_nivel(avl->der, nivel-1);
  }
}

void imprimir_avl(avl_t avl){
  int alt=altura_de_avl(avl);
  int i;
  for (i=alt; i>=1; i--) {
    imprimir_nivel(avl, i);
    printf("\n");
  }
}


/*
  Libera la memoria asignada a `avl' y la de sus elementos.
  El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de
  `avl'.
 */
void liberar_avl(avl_t &avl){
  if (avl !=NULL) {
    liberar_avl(avl->izq);
    liberar_avl(avl->der);
    liberar_info(avl->dato);
    delete avl;
  }
}
