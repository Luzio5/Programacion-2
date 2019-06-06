/*
  Módulo principal de la tarea 1.

  Procesador de comandos que prueba las operaciones declaradas en los .h.

  Lee comandos desde la entrada estándar e imprime en la salida estándar.

  Cada comando ocupa una línea. Empieza con un nombre y opcionalmente tiene
  parámetros.

  El comando con nombre 'Fin' termina la ejecución del programa.
  El comando con nombre '#' representa un comentario.

  La entrada y salida se pueden redirigir a archivos.
  Un ejemplo de ejecución es
  $ ./principal < test/01.in > test/01.sal

  En test/01.in hay dos comandos: el primero es un comentario y el segundo
  es 'Fin'.
  El programa llama a 'crear_pila', entra en el bucle, ejecuta las dos
  iteraciones correspondientes a los comandos y luego de salir del bucle
  llama a 'liberar_pila' y termina.



  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
*/

#include "include/pila.h"
#include "include/mapping.h"
#include "include/uso_tads.h"

#include <stdio.h>
#include <string.h>

#define MAX_PALABRA 32
#define MAX_LINEA 100

// programa principal
int main() {

  pila_t p = crear_pila();
  mapping_t m = crear_map();

  char resto_linea[MAX_LINEA];

  int cont_comandos = 0;
  bool salir = false;
  while (!salir) {
    // mostrar el prompt
    cont_comandos++;
    printf("%u>", cont_comandos);

    // leer el comando
    char nom_comando[MAX_PALABRA];
    scanf("%s", nom_comando);

    // procesar el comando
    if (!strcmp(nom_comando, "Fin")) {
      salir = true;
      printf("Fin.\n");
      // comentario
    } else if (!strcmp(nom_comando, "#")) {
      scanf("%[^\n]", resto_linea);
      printf("# %s.\n", resto_linea);

      // pila
    } else if (!strcmp(nom_comando, "es_vacia_pila")) {
      if (es_vacia_pila(p))
        printf("La pila está vacia. \n");
      else
        printf("La pila no está vacia. \n");

    } else if (!strcmp(nom_comando, "es_llena_pila")) {
      if (es_llena_pila(p))
        printf("La pila está llena. \n");
      else
        printf("La pila no está llena. \n");

    } else if (!strcmp(nom_comando, "apilar")) {
      if (!es_llena_pila(p)) {
        char nuevo;
        scanf(" %c", &nuevo);
        p = apilar(nuevo, p);
        printf("Se apiló %c. \n", nuevo);
      } else {
        printf("La pila está llena. La operación no tuvo efecto. \n");
      }

    } else if (!strcmp(nom_comando, "tope")) {
      if (!es_vacia_pila(p))
        printf("El tope es %c. \n", tope(p));
      else
        printf("La pila está vacia. La operación no tuvo efecto. \n");

    } else if (!strcmp(nom_comando, "desapilar")) {
      if (!es_vacia_pila(p)) {
        p = desapilar(p);
        printf("Se desapiló. \n");
      } else {
        printf("La pila está vacia. La operación no tuvo efecto. \n");
      }

      // mapping

    } else if (!strcmp(nom_comando, "es_lleno_map")) {
      if (es_lleno_map(m))
        printf("El mapping está lleno. \n");
      else
        printf("El mapping no está lleno. \n");

    } else if (!strcmp(nom_comando, "es_clave")) {
      char clave;
      scanf(" %c", &clave);
      if (es_clave(clave, m))
        printf("%c es clave. \n", clave);
      else
        printf("%c no es clave. \n", clave);

    } else if (!strcmp(nom_comando, "asociar")) {
      char clave;
      scanf(" %c", &clave);
      if (!es_clave(clave, m)) {
        char valor;
        scanf(" %c", &valor);
        m = asociar(clave, valor, m);
        printf("Se asoció %c con %c. \n", clave, valor);
      } else
        printf("%c es clave. La operacion no tiene efecto. \n", clave);

    } else if (!strcmp(nom_comando, "valor")) {
      char clave;
      scanf(" %c", &clave);
      if (es_clave(clave, m))
        printf("%c está asociado a %c. \n", clave, valor(clave, m));
      else
        printf("%c no es clave. La operacion no tiene efecto. \n", clave);

    } else if (!strcmp(nom_comando, "desasociar")) {
      char clave;
      scanf(" %c", &clave);
      if (es_clave(clave, m)) {
        m = desasociar(clave, m);
        printf("Se removió la asociación de %c. \n", clave);
      } else
        printf("%c no es clave. La operacion no tiene efecto. \n", clave);

      // uso_tads
    } else if (!strcmp(nom_comando, "es_balanceado")) {
      char expresion[MAX_EXP];
      fgets(expresion, MAX_LINEA + 1, stdin);
      ungetc('\n',stdin);
      //      scanf("%s", expresion);
      int n = strlen(expresion);
      if (es_balanceado(expresion, n))
        printf("Bien balanceados.\n");
      else
        printf("Mal balanceados.\n");

    } else {
      printf("Comando no reconocido.\n");
    } // if
    fgets(resto_linea, MAX_LINEA + 1, stdin);
  } // while

  liberar_pila(p);
  liberar_map(m);

  return 0;
}
