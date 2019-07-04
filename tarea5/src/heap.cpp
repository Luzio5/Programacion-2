/*43073854*/

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


 #include "../include/cadena.h"
 //#include "../include/binario.h"
 #include "../include/heap.h"
 #include "../include/info.h"

 #include <string.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <assert.h>

// Representación de `heap_t'
// Se debe definir en heap.cpp
struct elem{
  info_t info;
  int pos_padre;
};

struct rep_heap{
  int *mapa;
  int tamanio;
  int max_valor;
  int cont;
  int tope;
  elem *hep;
};
// Declaración del tipo `heap_t_t'
typedef rep_heap *heap_t;

/*Parainsertarun  nuevo  elemento  se  situa  al  final  del  vector(última  hoja  del  árbol)
  y  seasciendehasta  que  cumpla  lapropiedad.
  Paraeliminar la raizse intercambia con el
  último elemento (quese  elimina  en  O(1))  y  sedesciendela  nueva  raiz  hasta  quecumpla
   la propiedad.
*/
/*
  Devuelve un `heap' que puede contener hasta `tamanio' elementos.
  Los datos numéricos pueden estar en el rango 0 .. max_valor.
 */
static nat maximo(nat n1, nat n2) {return (n1>=n2) ? n1 : n2;}

 static int pos_padre(int i) {
   return (i-1)/2;
 }
heap_t crear_heap(nat tamanio, nat max_valor){
  heap_t h = new rep_heap;
  h->tamanio = tamanio;
  h->max_valor = max_valor;
  h->tope=maximo(tamanio,max_valor);
  h->mapa = new int [h->tope];
  for (int i=0; i<h->tope;i++) {
    h->mapa[i]=-1;
  }
  h->cont = 0;
  h->hep = new elem [tamanio];
  for (int i=0; i<h->tamanio;i++) {
    h->hep[i].info=NULL;
    h->hep[i].pos_padre = pos_padre(i);
  }
  return h;
}
static int i_hijo_izq(int padre){ return 2*padre+1;}
static int i_hijo_der(int padre){ return 2*padre+2;}
static int i_padre(int hijo) { return ((hijo-1)/2);}

static bool tiene_hijo_izq(int padre, heap_t h){ return i_hijo_izq(padre)<h->cont;}
static bool tiene_hijo_der(int padre, heap_t h){ return i_hijo_der(padre)<h->cont;}
static bool tiene_padre(int hijo, heap_t h){ return i_padre(hijo)>=0;}

static int hijo_izq(int padre, heap_t h) {return numero_info(h->hep[i_hijo_izq(padre)].info);}
static int hijo_der(int padre, heap_t h){return numero_info(h->hep[i_hijo_der(padre)].info);}
static int padre(int hijo, heap_t h){return numero_info(h->hep[i_padre(hijo)].info);}

static void cambio(int primero, int segundo, heap_t &h) {
  info_t aux=h->hep[primero].info;
  h->mapa[numero_info(h->hep[segundo].info)]=primero;
  h->mapa[numero_info(h->hep[primero].info)]=segundo;
  h->hep[primero].info=h->hep[segundo].info;
  h->hep[segundo].info=aux;
}


static void hepify_abajo(heap_t &h){
  int i=0;
  while (tiene_hijo_izq(i,h)){
    int hijo_pequeno = i_hijo_izq(i);
    if ((tiene_hijo_der(i,h)) && (hijo_der(i,h)<hijo_izq(i,h))) {
      hijo_pequeno=i_hijo_der(i);
    }
    if (numero_info(h->hep[i].info)<numero_info(h->hep[hijo_pequeno].info)) {
      break;
    } else {
      cambio(i,hijo_pequeno,h);
    }
    i=hijo_pequeno;
  }
}

static void hepify_arriba(heap_t &h){
  int i=h->cont-1;
  while (tiene_padre(i,h) && (padre(i,h)>numero_info(h->hep[i].info))) {
    cambio(i_padre(i),i,h);
    i=i_padre(i);
  }
}

static void hepify_par_arriba(heap_t h, int i) {
  while (tiene_padre(i,h) && (padre(i,h)>numero_info(h->hep[i].info))) {
    cambio(i_padre(i),i,h);
    i=i_padre(i);
  }
}


/*
  Si inserta el elemento `i'.
  Precondición: !es_lleno_heap(h) y !hay_valor(v,h) y v <= max_valor(h),
  donde v = numero_info(i).
  El tiempo de ejecución es O(log tamanio).
 */

void insertar_en_heap(info_t i, heap_t &h){
  assert (!es_lleno_heap(h));
  assert (!hay_valor(numero_info(i),h));
  assert (numero_info(i)<=h->max_valor);
  h->hep[h->cont].info=i;
  h->mapa[numero_info(i)]=h->cont;
  h->cont++;
  hepify_arriba(h);
}

/*
  Reduce a v/2 el valor del elemento cuyo valor actual es `v'.
  Precondición: hay_valor(v, h) y !hay_valor(v/2, h).
  No debe quedar memoria inaccesible.
  El tiempo de ejecución es O(log tamanio).
 */

void reducir(nat v, heap_t &h){
  assert(hay_valor(v, h));
  assert(!hay_valor(v/2, h));
  char *frase_copy = new char[strlen(frase_info(h->hep[h->mapa[v]].info)) + 1];
  strcpy(frase_copy, frase_info(h->hep[h->mapa[v]].info));
  int val=v/2;
  info_t nuevo=crear_info(val, frase_copy);
  liberar_info(h->hep[h->mapa[v]].info);
  h->hep[h->mapa[v]].info=nuevo;
  h->mapa[val]=h->mapa[v];
  h->mapa[v]=-1;
  hepify_par_arriba(h,h->mapa[val]);
}

/*
  Elimina de 'h' el elemento de menor valor y libera la memoria que tiene
  asignada.
  Precondición: ! es_vacia_heap(h).
  El tiempo de ejecución es O(log tamanio).
 */

void eliminar_menor(heap_t &h){
  assert(!es_vacia_heap);
  h->mapa[numero_info(h->hep[0].info)]=-1;
  liberar_info(h->hep[0].info);
  h->hep[0].info=NULL;
  h->hep[0].info=h->hep[h->cont-1].info;
  h->hep[h->cont-1].info=NULL;
  h->cont--;
  if (!es_vacio_heap(h)) {
    h->mapa[numero_info(h->hep[0].info)]=0;
  }
  hepify_abajo(h);
}

/*  Libera la menoria asignada a `h' y a sus elementos. */
void liberar_heap(heap_t &h){
  for (int i=0; i<h->cont; i++) {
    liberar_info(h->hep[i].info);
  }
  delete [] h->mapa;
  delete[] h->hep;
  delete h;
}

/*
  Devuelve `true' si y sólo si en `h' no hay elementos.
  El tiempo de ejecución es O(1).
 */
bool es_vacio_heap(heap_t h){
  return h->cont==0;
}

/*
  Devuelve `true' si y sólo si en `h' hay `tamanio' elementos.
  El tiempo de ejecución es O(1).
 */
bool es_lleno_heap(heap_t h){
  return h->cont==h->tamanio;
}

/*
  Devuelve `true' si y sólo si en 'h' hay un elemento con valor `v'.
  El tiempo de ejecución es O(1).
 */
bool hay_valor(nat v, heap_t h){
  return h->mapa[v]!=-1;
}

/*
  Devuelve el elemento de 'h' con menor valor.
  Precondición: ! es_vacio_h(h).
  El tiempo de ejecución es O(1).
 */
info_t menor(heap_t h){
  assert (!es_vacia_heap(h));
  return h->hep[0].info;
}

/*
  Devuelve el máximo valor del rango para los datos numericos, establecido en
  crear_h.
 */
nat max_valor(heap_t h){
return h->max_valor;
}
