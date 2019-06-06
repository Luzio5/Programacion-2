/*

  Funciones que usan los tads.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _USO_TADS_H
#define _USO_TADS_H

#define MAX_EXP 40

/*
  Devuelve `true' si y solo si los delimitadores de 'expresion' están
  correctamente balanceaados.
  Los delimitadores de apertura son '<', '(', '{' y '[' y los correspondientes
  delimitadores de cierre son '>', ')', '}' y ']'.
  Los demás caracteres no son considerados delimitadores.
  Los caracteres están desde la posición 0 hasta la n - 1 de `expresion'.
 */
bool es_balanceado(char expresion[MAX_EXP], int n);

#endif
