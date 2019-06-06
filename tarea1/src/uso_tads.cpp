/* Implementacion a entregar para programacion 2 */

#include "../include/uso_tads.h"
#include "../include/pila.h"
#include "../include/mapping.h"
#include <stdio.h>


static mapping_t construr_map() {
  mapping_t parejas = crear_map();
  parejas = asociar('<', '>', parejas);
  parejas = asociar('(', ')', parejas);
  parejas = asociar('{', '}', parejas);
  parejas = asociar('[', ']', parejas);
  return parejas;
}


bool es_balanceado(char expresion[MAX_EXP], int n){

  bool balanceado=false;
  int k=0;
  pila_t pila = crear_pila();
  mapping_t parejas=construr_map();



  for (k=0; k<n; k++) {
    //si el primero que agrego a mi pila vacia es de cierre que rompa desde el vamos
    if ((es_vacia_pila(pila)) && (es_valor(expresion[k], parejas))) {
      break;
    }
//Lo primero que hago es generar el mapping y la pila
    if (es_clave(expresion[k], parejas)) {
      balanceado=false;
      if (not (es_llena_pila(pila))) {
        pila = apilar(expresion[k], pila);
      }
      //preguntar si tiene que hacer algo al encontrar que tiene la pila llena
    } else if ((es_valor(expresion[k], parejas))) {
      if (!es_vacia_pila(pila)) {
        if (valor(tope(pila), parejas) == expresion[k]) {
          pila = desapilar(pila);
        }
      } else if (es_vacia_pila(pila)){
        balanceado = false;
        pila = apilar(expresion[k], pila);
      }
    }

  }
  if ((es_vacia_pila(pila)) && (!(es_valor(expresion[k], parejas)))) {   //este control se puede hacer una unica vez al final para ser eficientes
    balanceado = true;
  }


  //libero y destruyo el mapa
  parejas = desasociar('<', parejas);
  parejas = desasociar('(', parejas);
  parejas = desasociar('{', parejas);
  parejas = desasociar('[', parejas);
  liberar_map (parejas);

  //libero y destruyo la pila
  while (!es_vacia_pila(pila)) {
    pila = desapilar(pila);
  }
  liberar_pila(pila);

  return balanceado;
}
