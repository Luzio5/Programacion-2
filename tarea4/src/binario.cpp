/*43073854*/

#include "../include/binario.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/uso_cadena.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct rep_binario {
  info_t dato;
  rep_binario *izq;
  rep_binario *der;
};

typedef rep_binario *binario_t;

/*
  Devuelve un binario_t vacío (sin elementos).
  El tiempo de ejecución es O(1).
 */
binario_t crear_binario() { return NULL; }

/*
  Inserta `i' en `b' respetando la propiedad de orden definida.
  Devuelve `b'.
  Precondición: es_vacio_binario(buscar_subarbol(frase_info(i), b).
  El tiempo de ejecución es O(log n) en promedio, donde `n' es la cantidad de
  elementos de `b'.
 */
binario_t insertar_en_binario(info_t i, binario_t b){
  assert (es_vacio_binario(buscar_subarbol(frase_info(i), b)));
  binario_t aux = b;
  binario_t aux1;
  if (aux==NULL) {
    //la inserto al inicio y queda izq y der Null
    aux = new rep_binario;
    aux->dato = i;
    aux->izq = aux->der = NULL;
  } else {
    //me muevo hasta llegar al lugar donde deberia insertar el elemento y muevo el resto
    if (strcmp(frase_info(i),frase_info(aux->dato))>0) {
      aux1 = insertar_en_binario(i, aux->der);
      aux->der = aux1;
    } else if (strcmp(frase_info(i),frase_info(aux->dato))<0) {
      aux1 = insertar_en_binario(i, aux->izq);
      aux->izq = aux1;
    }
  }
  b = aux;
  return b;
}

/*
  Devuelve el elemento mayor (según la propiedad de orden definida) de `b'.
  Precondición: ! es_vacio_binario(b).
  El tiempo de ejecución es O(log n) en promedio, donde `n' es la cantidad de
  elementos de `b'.
 */
info_t mayor(binario_t b){
  assert (!es_vacio_binario(b));
  binario_t aux = b;
  while (aux->der!=NULL){
    aux=aux->der;
  }
  return aux->dato;
}

/*
  Remueve el nodo en el que se localiza el elemento mayor de `b'
  (libera la memoria  asignada al nodo, pero no la del elemento).
  Devuelve `b'.
  Precondición: ! es_vacio_binario(b).
  El tiempo de ejecución es O(log n) en promedio, donde `n' es la cantidad de
  elementos de `b'.
 */
binario_t remover_mayor(binario_t b) {
  assert (!es_vacio_binario(b));
  if (b->der == NULL) {
    binario_t izq = b->izq;
    delete (b);
    b=izq;
  } else {
    b->der = remover_mayor(b->der);
  }
  return b;
}

/*
  Remueve de `b' el nodo en el que el dato de texto de su elemento es `t'.
  Si los dos subárboles del nodo a remover son no vacíos, en sustitución del
  elemento removido debe quedar el que es el mayor (segun la propiedad de orden
  definida) en el subárbol izquierdo.
  Devuelve `b'.
  Precondición: !es_vacio_binario(buscar_subarbol(frase_info(i), b).
  Libera la memoria del nodo y del elemento.
  El tiempo de ejecución es O(log n) en promedio, donde `n' es la cantidad de
  elementos de `b'.
 */



binario_t remover_de_binario(const char *t, binario_t b){
  assert (!es_vacio_binario(buscar_subarbol(frase_info(i), b)));
  binario_t aux;
  binario_t aux1;
  if (strcmp(t, frase_info(b->dato))==0) {
    if ((b->izq==NULL) && (b->der==NULL)) {
      b = liberar_binario(b);
      b = crear_binario();
    } else if ((b->izq==NULL) && (b->der!=NULL)) {
      aux = b->der;
      b->der=NULL;
      liberar_binario(b);
      b=aux;

    } else if ((b->izq!=NULL) && (b->der==NULL)){
      aux=b->izq;
      b->izq=NULL;
      liberar_binario(b);
      b=aux;
    } else if ((b->izq!=NULL) && (b->der!=NULL)) {
    //me muevo por el subarbol izquierdo lo mas a la derecha que puedo
    aux=b->izq;//el que voy a borrar sin perder el nodo
    binario_t aux2=b->izq;//aux2 es el que quiero meter de raiz
    while (aux2->der!=NULL){
      aux2=aux2->der;
    }
    liberar_info(b->dato);
    info_t nodito = copia_info(aux2->dato);
    b->dato = nodito;
    liberar_info(aux2->dato);
    aux1=remover_mayor(aux);
    b->izq = aux1;
    }
  } else if (strcmp(t,frase_info(b->dato))>0) {
      aux1 = remover_de_binario(t, derecho(b));
      b->der = aux1;
  } else if (strcmp(t,frase_info(b->dato))<0) {
      aux1 = remover_de_binario(t, izquierdo(b));
      b->izq = aux1;
    }
  return b;
}

/*
  Libera la memoria asociada a `b' y todos sus elementos.
  Devuelve `b'.
  El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `b'.
 */
 binario_t liberar_binario(binario_t b) {
   if (b !=NULL) {
     b->izq = liberar_binario(b->izq);
     b->der = liberar_binario(b->der);
     liberar_info(b->dato);
     delete b;
   }
   return b;
 }

/*
  Devuelve `true' si y sólo si `b' es vacío (no tiene elementos).
  El tiempo de ejecución es O(1).
 */
bool es_vacio_binario(binario_t b) {return b == NULL;}


static int absoluto(int n) {return (n>=0) ? (n):(-n);}
static nat maximo(nat n1, nat n2) {return (n1>=n2) ? n1 : n2;}
/*
  Devuelve `true' si y sólo si cada nodo de `b' cumple la condición de balanceo
  AVL. El árbol vacío cumple la condición.
  Un nodo cumple la condición de balanceo AVL si el valor absoluto de la
  diferencia de las alturas de sus subárboles izquierdo y derecho es menor o
  igual a 1.
  Cada nodo se puede visitar una sola vez.
  El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `b'.
 */
static bool reviso_AVL(binario_t b, nat &alt, bool &res) {
  nat iz=0;
  nat de=0;
  if (b!=NULL) {
    bool reviso_AVL_izq = reviso_AVL(b->izq, iz, res);
    if(!reviso_AVL_izq) {
      res = false;
    }
    bool reviso_AVL_der = reviso_AVL(b->der, de, res);
    if (!reviso_AVL_der) {
      res = false;
    }
    if ((res) && ((absoluto(iz-de))<=1)) {
      res = true;
      alt = maximo(iz,de)+1;
    } else {
      res = false;
    }
  }
  return res;
}


bool es_AVL(binario_t b){
  bool res=true;
  nat alt = 0;
  res = reviso_AVL(b,alt, res);
  return res;
}

/*
  Devuelve el elemento asociado a la raíz de `b'.
  Precondición: ! es_vacio_binario(b).
  El tiempo de ejecución es O(1).
 */
info_t raiz(binario_t b){
  assert (! es_vacio_binario(b));
  return b->dato;
}

/*
  Devuelve el subárbol izquierdo de `b'.
  Precondición: ! es_vacio_binario(b).
  El tiempo de ejecución es O(1).
 */
binario_t izquierdo(binario_t b){
  assert(! es_vacio_binario(b));
  return b->izq;
}

/*
  Devuelve el subárbol derecho de `b'.
  Precondición: ! es_vacio_binario(b).
  El tiempo de ejecución es O(1).
 */
binario_t derecho(binario_t b){
  assert(! es_vacio_binario(b));
  return b->der;
}

/*
  Devuelve el subárbol que tiene como raíz al nodo con el elemento cuyo dato de
  texto es `t'.
  Si `t' no pertenece a `b', devuelve el árbol vacío.
  El tiempo de ejecución es O(log n) en promedio, donde `n' es la cantidad de
  elementos de `b'.
 */
 binario_t buscar_subarbol(const char *t, binario_t b) {
   binario_t res;
   if (es_vacio_binario(b))
     res = crear_binario();
   else {
     int comp = strcmp(t, frase_info(raiz(b)));
     if (comp<0)
       res = buscar_subarbol(t, izquierdo(b));
     else if (comp>0)
       res = buscar_subarbol(t, derecho(b));
     else
       res = b;
   }
   return res;
 }



 /*
   Devuelve la altura de `b'.
   La altura de un árbol vacío es 0.
   El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `b'.
  */
  nat altura_binario(binario_t b){
     int alti;
     int altd;
     if (b==NULL) {
       return 0;
     } else {
       alti = altura_binario(b->izq);
       altd = altura_binario(b->der);
       if (alti>altd) {
         return alti+1;
       } else {
         return altd+1;
       }
     }
   }

 /*
   Devuelve la cantidad de elementos de `b'.
   El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `b'.
  */
 nat cantidad_binario(binario_t b){
   if (b == NULL) {
     return 0;
   } else {
   return (1 + cantidad_binario(izquierdo(b)) + cantidad_binario(derecho(b)));
   }
 }

 /*
   Devuelve la suma de los datos numéricos de los últimos `i' elementos
   (considerados según la propiedad de orden de los árboles binario_t)
   de `b' cuyos datos numéericos sean pares.
   Si en `b' hay menos de `i' elementos con dato numérico par devuelve la
   suma de todos los datos numéricos pares de `b'.
   No se deben crear estructuras auxiliares.
   No se deben visitar nuevos nodos después que se hayan encontrado los
   `i' elementos.
   El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `b'.
  */
  static int ultimos_pares(binario_t b, nat i, nat &n, int &res){ // binario que chequeo, i cantidad que quiero sumar, n recorrida, resultado
    if (b!=NULL) {
      ultimos_pares(derecho(b), i, n, res);
      if ((numero_info(b->dato)%2==0) && (n<=i)) {
        res= res+numero_info(b->dato);
        n=n+1;
      }
      ultimos_pares(izquierdo(b), i, n, res);
    }
    return res;
  }

 int suma_ultimos_pares(nat i, binario_t b){
   int res=0;
   nat n = 1;
   res = ultimos_pares(b,i,n,res);
   return res;
 }

 /*
   Devuelve una cadena_t con los elementos de `b' en orden lexicográfico
   creciente según sus datos de texto.
   La cadena_t devuelta no comparte memoria con `b'.
   El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `b'.
  */
static cadena_t agrego_cadena(binario_t b, cadena_t aux){
  if (b==NULL) {
    return aux;
  }
  aux = agrego_cadena(b->izq, aux);
  if (b!=NULL) {
    info_t nodo = copia_info(b->dato);
    aux = insertar_al_final(nodo, aux);
  }
  aux = agrego_cadena(b->der, aux);
  return aux;
}

 cadena_t linealizacion(binario_t b){
    cadena_t res = crear_cadena();
    if (b!=NULL) {
      res = agrego_cadena(b, res);
    }
  return res;
 }

 /*
   Devuelve un árbol balanceado cuyos elementos son los que están contenidos en
   `cad'.
   En esta función se dice que un árbol está balanceado si
   a) es vacío;
   o
   b)
     b1) el sub-árbol izquierdo tiene la misma cantidad de elementos o uno más
       que el  subárbol derecho;
     y
     b2) los subárboles izquierdo y derecho están balanceados.

   DEFINICIÓN ALTERNATIVA DE ÁRBOL BALANCEADO
   En esta función se dice que un árbol esta balanceado si en cada nodo, la
   cantidad de elementos de su subárbol izquierdo es igual a, o 1 más que, la
   cantidad de elementos de su subárbol derecho.

   Precondición: los elementos de `cad' están en orden lexicográfico creciente
   estricto según sus datos de texto.
   El árbol devuelto no comparte memoria con `cad'.
   El tiempo de ejecución es O(n . log n), siendo `n` la cantidad de elementos
   de `cad'.
  */
  static localizador_t medio_cad(cadena_t cad){
    //chequear la long y devolver el medio o medio +1
    nat largo = longitud(cad);
    nat medio;
    if (largo%2==0) {
      medio = (largo/2)+1;
    } else {
      medio = (largo/2)+1;
    }
    localizador_t res = kesimo(medio,cad);
    return res;
  }

  binario_t cadena_a_binario_aux(cadena_t cad, binario_t b) {
    if (!es_vacia_cadena(cad)) {
      //copio e inserto este al binario;
      cadena_t cad_der;
      cadena_t cad_izq;
      localizador_t aux = medio_cad(cad);
      info_t nodo = copia_info(info_cadena(aux,cad));
      b = insertar_en_binario(nodo, b);
      //-----------------------------
      //creo 2 cadenas nuevas, izq y der,
      if (localizador_en_cadena(siguiente(aux,cad), cad)) {
        cad_der = copiar_segmento (siguiente(aux,cad), final_cadena(cad), cad);
      } else {
        cad_der = crear_cadena();
      }
      if (localizador_en_cadena(anterior(aux,cad), cad)) {
        cad_izq = copiar_segmento (inicio_cadena(cad), anterior(aux,cad), cad);
      } else {
        cad_izq = crear_cadena();
      }
      //recursion
      b = cadena_a_binario_aux(cad_der,b);
      liberar_cadena(cad_der);
      b = cadena_a_binario_aux(cad_izq,b);
      liberar_cadena(cad_izq);
    }
    return b;
  }


 binario_t cadena_a_binario(cadena_t cad){
   binario_t b=crear_binario();//genereo para tener mi binario
   b = cadena_a_binario_aux (cad , b);
   return b;
 }

 /*
   Devuelve un árbol con copias de los elementos de `b' que cumplen la condición
   "numero_info(elemento) < clave".
   La estructura del árbol resultado debe ser análoga a la de `b'. Esto
   significa que dados dos nodos `U' y `V' de `b' en los que se cumple la
   condición y tal que `U' es ancestro de `V', en el árbol resultado la copia de
   `U' debe ser ancestro de la copia de `V' cuando sea posible. Esto no siempre
   se puede lograr y al mismo tiempo mantener la propiedad de orden del árbol
   en el caso en el que en un nodo `V' no se cumple la condición y en sus dos
   subárboles hay nodos en los que se cumple. En este caso, la copia del nodo
   cuyo elemento es el mayor (según la propiedad de orden definida) de los que
   cumplen la condición en el subárbol izquierdo de `V' deberá ser ancestro de
   las copias de todos los descendientes de `V' que cumplen la condición.
   (Ver ejemplos en LetraTarea3.pdf).
   El árbol resultado no comparte memoria con `b'. *)
   El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `b'.
  */
  static binario_t copia_recursiva(binario_t b){
    if (b==NULL){
      return NULL;
    }
    info_t nodo = copia_info(b->dato);
    binario_t aux = new rep_binario;
    aux->dato = nodo;
    aux->izq=copia_recursiva(b->izq);
    aux->der=copia_recursiva(b->der);
    return aux;
  }

 static binario_t menores_eliminacion(int clave, binario_t copia, binario_t orig){
   if (orig==NULL) {
     return copia;
   }
     copia = menores_eliminacion(clave, copia, orig->der);
   if (numero_info(orig->dato)>=clave) {
     copia = remover_de_binario(frase_info(orig->dato),copia);
   }
    copia = menores_eliminacion(clave, copia, orig->izq);
   return copia;
 }

 binario_t menores(int clave, binario_t b){
   binario_t copia = copia_recursiva(b);
   copia = menores_eliminacion(clave, copia, b);
   return copia;
 }

 /*
   Devuelve `true' si y solo si en `b' hay un camino desde la raiz hasta una
   hoja que sea compatible con `c'.
   Decimos que una cadena y un camino son compatibles si tienen la misma
   longitud y al recorrer la cadena desde el inicio hasta el final y el camino
   desde la raíz hasta la hoja las frases de los respectivos elementos son
   iguales.
   El tiempo de ejecución es O(log n) en promedio, donde `n' es la cantidad de
   elementos de `b'.
  */
 bool es_camino(cadena_t c, binario_t b){
   binario_t bin_aux = b;
   bool res;
   localizador_t loc_aux=inicio_cadena(c);
    if (es_vacio_binario(b) && es_vacia_cadena(c)) {
      res = true;
    } //else if (altura_binario(b)==1) {
      //res = false;
     else if (!es_vacio_binario(b) && es_vacia_cadena(c)) {
      res = false;
    } else if (es_vacio_binario(b) && !es_vacia_cadena(c)) {
      res = false;
    } else {
      res = true;
      while ((res) && (loc_aux != NULL) && (bin_aux!=NULL)) {
        if (strcmp(frase_info(bin_aux->dato), frase_info(info_cadena(loc_aux,c))) == 0) {
          res = true;
          if (localizador_en_cadena(siguiente(loc_aux,c),c)) {
            loc_aux=siguiente(loc_aux,c);
          } else {
            break;
          }
          if(strcmp(frase_info(bin_aux->dato), frase_info(info_cadena(loc_aux,c)))>0) {
            bin_aux = bin_aux->izq;
          } else {
            bin_aux = bin_aux->der;
          }
        } else {
          res=false;
        }
      }
      if ((loc_aux == final_cadena(c)) && (bin_aux == NULL)) {
        res=false;
      } else if ((res) && (loc_aux == final_cadena(c)) && (bin_aux->izq == NULL) && (bin_aux->der == NULL)) {
        res = true;
      } else {
        res = false;
      }
    }
    return res;
  }

 /*
   Devuelve una cadena_t con los elementos del nivel `l' de 'b'.
   La raíz es el nivel 1.
   La cadena_t resultado debe estar ordenada de manera creciente según las
   frases de sus elementos.
   La cadena_t devuelta no comparte memoria con `b'.
  */

  static cadena_t llegar_a_nivel(binario_t b, nat l, cadena_t res, nat n){ // binario que chequeo, l nivel que quiero mostrar, res cadena a mostrar, n recorrida
    if (b!=NULL) {
      llegar_a_nivel(izquierdo(b), l, res, n+1);
      //voy a meter los que cumplen el nivel adecuado
      if (n==l) {
        info_t nodo = copia_info(b->dato);
        res = insertar_al_final(nodo, res);
      }
      llegar_a_nivel(derecho(b), l, res, n+1);
    }
    return res;
  }
 cadena_t nivel_en_binario(nat l, binario_t b){
   //si b es null devuelvo cadena vacia
   cadena_t res = crear_cadena();
   res = llegar_a_nivel(b, l, res, 1);
   return res;
 }

 /*
   Imprime los elementos de `b', uno por línea, en orden descendente de la
   propiedad de orden de los árboles `binario_t'.
   Antes del elemento imprime una cantidad de guiones igual a su nivel.
   El elemento se imprime según la especificación dada en `info_a_texto'.
   El nivel de la raíz es 0.
   Antes de terminar, se debe imprimir un fin de linea.
   Si es_vacio_binario(b) sólo se imprime el fin de línea.
   El tiempo de ejecución es O(n . log n) en promedio, donde `n' es la cantidad
   de elementos de `b'.
  */

void mostrar_arbol(binario_t b, nat n){
  if (b==NULL) {
    return;
  }
  mostrar_arbol(derecho(b),n+1);
  for (nat i=0;i<n;i++) {
    printf("-");
  }
  printf("(%d,%s)\n", numero_info(b->dato), frase_info(b->dato));
  mostrar_arbol(izquierdo(b),n+1);
}


 void imprimir_binario(binario_t b){
  if (!es_vacio_binario(b)) {
    printf("\n");
    mostrar_arbol(b,0);
  } else {
    printf("\n");
  }
}
