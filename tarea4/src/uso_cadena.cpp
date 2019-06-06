/*4307385*/
/*El módulo declara dos conceptos, denominados cadena_t y localizador_t . Con cadena_t se implemen-
tan cadenas doblemente enlazadas de elementos de info_t con una cabecera con punteros al inicio y al
final. El tipo localizador_t es un puntero a un nodo de una cadena, o no es válido, en cuyo caso su valor
es NULL . Con el uso de los localizadores se pueden realizar algunas operaciones de manera eficiente (sin
tener que hacer un recorrido de la cadena).*/

#include "../include/cadena.h"
#include "../include/info.h"

#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>



/*
  Devuelve `true' si y sólo si en `cad' hay un elemento cuyo dato numérico es
  `i'.
 */
bool pertenece(int i, cadena_t cad){
  bool todo_ok=false;
  if (es_vacia_cadena(cad)) {
    todo_ok = false;
  } else {
    localizador_t aux = inicio_cadena(cad);
    while ((siguiente(aux, cad)!=NULL) && ((numero_info(info_cadena(aux, cad)))!=i)) {
      aux = siguiente(aux, cad);
    }
    if (numero_info(info_cadena(aux, cad))==i) {
      todo_ok= true;
    }
  }
  return todo_ok;
}

/*  Devuelve la cantidad de elementos de `cad'. */
nat longitud(cadena_t cad){
  nat res;
  if (es_vacia_cadena(cad)) {
    res = 0;
  } else {
    localizador_t aux= inicio_cadena(cad);
    res = 0;
    while (aux != NULL) {
      res ++;
      aux = siguiente(aux, cad);
    }
  }
  return res;
}

/*
  Devuelve `true' si y sólo si `cad' está ordenada de forma no decreciente
  (= creciente de manera no estricta) según los datos numéricos de sus
  elementos.
  Si es_vacia_cadena (cad) devuelve `true'.
 */
bool esta_ordenada(cadena_t cad){
  bool res=false;
  if (es_vacia_cadena(cad)) {
    res = true;
  } else if (longitud(cad) == 1) {
    res = true;
  } else if (longitud (cad) !=1){
      localizador_t aux = inicio_cadena(cad);
    while ((siguiente(aux,cad) != NULL) && ((numero_info(info_cadena(aux,cad))) <= (numero_info(info_cadena(siguiente(aux, cad), cad))))) {
        aux = siguiente(aux, cad);
      }
      if (siguiente(aux, cad) == NULL) {
        res = true;
      } else {
        res = false;
      }
  }
  return res;
}

/*
  Devuelve una cadena_t con todos los elementos de `c1' y `c2' ordenada de
  manera  creciente segun sus datos numéricos.
  Si hay elementos cuyos datos numéricos son iguales los elementos de `c1'
  quedan antes de los de `c2'.
  La cadena_t resultado no comparte memoria ni con `c1' ni con `c2'.
  Precondición: esta_ordenada (c1) y esta_ordenada (c2).
 */
cadena_t mezcla(cadena_t c1, cadena_t c2){
  assert(esta_ordenada(c1) && esta_ordenada(c2));
  cadena_t cad_res;
  if (es_vacia_cadena(c1) && es_vacia_cadena(c2)) {
    cad_res = crear_cadena();
  } else if (!es_vacia_cadena(c1) && es_vacia_cadena(c2)) {
    cad_res = copiar_segmento(inicio_cadena(c1), final_cadena(c1), c1);
  } else if (es_vacia_cadena(c1) && !es_vacia_cadena(c2)){
    cad_res = copiar_segmento(inicio_cadena(c2), final_cadena(c2), c2);
  } else if (!es_vacia_cadena(c1) && !es_vacia_cadena(c2)) {
    localizador_t sigue1 = inicio_cadena(c1);
    localizador_t sigue2 = inicio_cadena(c2);
    if (longitud(c1) == 1) {
      if ((numero_info(info_cadena(sigue1,c1)))<=(numero_info(info_cadena(sigue2,c2)))) {
        cad_res = copiar_segmento(sigue1, sigue1, c1);
        cadena_t segunda_parte=copiar_segmento(sigue2, final_cadena(c2), c2);
        insertar_segmento_despues (segunda_parte, final_cadena(cad_res), cad_res);
        liberar_cadena(segunda_parte);
      } else {
        while ((siguiente(sigue2, c2) != NULL ) && ((numero_info(info_cadena(sigue1,c1)))>(numero_info(info_cadena(siguiente(sigue2,c2),c2))))) {
          sigue2 = siguiente(sigue2, c2);
        }
        if (siguiente(sigue2,c2) == NULL){
          //inserto al final toda la cadena
          cad_res = copiar_segmento(inicio_cadena(c2), final_cadena(c2), c2);
          cadena_t segunda_parte=copiar_segmento(inicio_cadena(c1), final_cadena(c1), c1);
          insertar_segmento_despues (segunda_parte, final_cadena(cad_res), cad_res);
          liberar_cadena (segunda_parte);
        } else {
          cad_res = copiar_segmento(inicio_cadena(c2), sigue2, c2);
          cadena_t segunda_parte=copiar_segmento(sigue1, sigue1, c1);
          insertar_segmento_despues (segunda_parte, final_cadena(cad_res), cad_res);
          liberar_cadena (segunda_parte);
          cadena_t restante=copiar_segmento(siguiente(sigue2,c2), final_cadena(c2), c2);
          insertar_segmento_despues (restante, final_cadena(cad_res), cad_res);
          liberar_cadena (restante);
        }
      }
      } else if (longitud(c2) == 1) {
      if ((numero_info(info_cadena(sigue2,c2)))<=(numero_info(info_cadena(siguiente(sigue1,c1),c1)))) {
        cad_res = copiar_segmento(sigue2, sigue2, c2);
        cadena_t segunda_parte=copiar_segmento(sigue1, final_cadena(c1), c1);
        insertar_segmento_despues (segunda_parte, final_cadena(cad_res), cad_res);
        liberar_cadena(segunda_parte);
        } else {
        while ((siguiente(sigue1, c1) != NULL ) && ((numero_info(info_cadena(sigue2,c2)))>(numero_info(info_cadena(sigue1,c1))))) {
          sigue1 = siguiente(sigue1,c1);
        }
        if (siguiente(sigue1,c1) == NULL){
          //inserto al final toda la cadena
          cad_res = copiar_segmento(inicio_cadena(c1), final_cadena(c1), c1);
          cadena_t segunda_parte=copiar_segmento(inicio_cadena(c2), final_cadena(c2), c2);
          insertar_segmento_despues (segunda_parte, final_cadena(cad_res), cad_res);
          liberar_cadena (segunda_parte);
        } else {
          cad_res = copiar_segmento(inicio_cadena(c1), sigue1, c1);
          cadena_t segunda_parte=copiar_segmento(sigue2, sigue2, c2);
          insertar_segmento_despues (segunda_parte, final_cadena(cad_res), cad_res);
          liberar_cadena (segunda_parte);
          cadena_t restante=copiar_segmento(siguiente(sigue1,c1), final_cadena(c1), c1);
          insertar_segmento_despues (restante, final_cadena(cad_res), cad_res);
          liberar_cadena (restante);
        }
      }
      }else {
        cad_res = crear_cadena();
        while (sigue1 != NULL && sigue2 !=NULL) {
          if ((numero_info(info_cadena(sigue1,c1)))<=(numero_info(info_cadena(sigue2,c2)))) {
            info_t p_datos=copia_info(info_cadena(sigue1,c1));
            insertar_al_final(p_datos, cad_res);
            sigue1=siguiente(sigue1, c1);
          } else {
            info_t p_datos=copia_info(info_cadena(sigue2,c2));
            insertar_al_final(p_datos, cad_res);
            sigue2=siguiente(sigue2, c2);
          }
        }
        if (sigue1==NULL && sigue2!=NULL) {
          cadena_t c2_copia = copiar_segmento(sigue2, final_cadena(c2), c2);
          insertar_segmento_despues (c2_copia, final_cadena(cad_res), cad_res);
          liberar_cadena (c2_copia);
        } else if (sigue1!=NULL && sigue2==NULL){
          cadena_t c1_copia = copiar_segmento(sigue1, final_cadena(c1), c1);
          insertar_segmento_despues (c1_copia, final_cadena(cad_res), cad_res);
          liberar_cadena(c1_copia);
        }
      }
    }
    return cad_res;
  }




/*
  Devuelve el resultado de concatenar `c2' después de `c1'.
  La cadena_t resultado no comparte memoria ni con `c1' ni con `c2'.
 */
cadena_t concatenar(cadena_t c1, cadena_t c2){
  cadena_t cad_res;
  if (!es_vacia_cadena(c1) && !es_vacia_cadena(c2)) {
    cadena_t c2_copia = copiar_segmento(inicio_cadena(c2), final_cadena(c2), c2);
    cadena_t c1_copia = copiar_segmento(inicio_cadena(c1), final_cadena(c1), c1);
    cad_res =crear_cadena();
    insertar_segmento_despues (c1_copia, inicio_cadena(cad_res), cad_res);
    liberar_cadena(c1_copia);
    localizador_t aux = final_cadena(cad_res);
    insertar_segmento_despues (c2_copia, aux, cad_res);
    liberar_cadena(c2_copia);
  } else if (es_vacia_cadena(c1) && !es_vacia_cadena(c2)) {
    cad_res = copiar_segmento(inicio_cadena(c2), final_cadena(c2), c2);
  } else if (!es_vacia_cadena(c1) && es_vacia_cadena(c2)) {
    cad_res = copiar_segmento(inicio_cadena(c1), final_cadena(c1), c1);
  } else if (es_vacia_cadena(c1)&& es_vacia_cadena(c2)) {
    cad_res=crear_cadena();
  }
  return cad_res;
}

/*
  Se ordena `cad' de manera creciente según los datos numéricos de sus
  elementos.
  Devuelve `cad'.
  No se debe obtener ni devolver memoria de manera dinámica.
  Si es_vacia_cadena (cad) no hace nada.
 */
cadena_t ordenar(cadena_t cad) {
  if (!es_vacia_cadena(cad)) {
    if (longitud(cad) !=1) {
      localizador_t aux = inicio_cadena(cad);  //lo uso para ir armando la cadena y saber donde estoy parado
      localizador_t buscador;
      while (!esta_ordenada(cad) && (siguiente(aux,cad) != NULL)) {
        buscador = menor_en_cadena (aux, cad);
        if (aux == buscador) {
          aux = siguiente(aux, cad);
        } else {  //cuando son diferentes aux y buscador
          intercambiar(aux, buscador, cad);
          aux=buscador;
          aux = siguiente(aux, cad);
        }
      }
    } //este else es del if longitud !=1. si es 1 no hago nada
  } // este else es de mi cadena vacia que simplemente retorna cadena vacia
  return cad;
}

/*
  Cambia todas las ocurrencias de `original' por `nuevo' en los elementos
   de `cad'. No debe quedar memoria inaccesible.
  Devuelve `cad'.
 */
cadena_t cambiar_todos(int original, int nuevo, cadena_t cad){

  if (!es_vacia_cadena(cad)) {
    localizador_t aux = inicio_cadena(cad);
    while (aux!=NULL) {
      if (numero_info(info_cadena(aux,cad))==original) {
        localizador_t aux_a_borrar = aux;
        char *frase_copy = new char[strlen(frase_info(info_cadena(aux,cad))) + 1];
        strcpy(frase_copy, frase_info(info_cadena(aux,cad)));
        info_t nueva_infot=crear_info(nuevo, frase_copy);
        insertar_antes(nueva_infot, aux, cad);
        aux = anterior(aux, cad);
        remover_de_cadena(aux_a_borrar, cad);
        aux = siguiente(aux, cad);
      } else {
        aux = siguiente (aux, cad);
      }
    }
  }
  return cad;
}
