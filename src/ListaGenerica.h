#ifndef LISTAGENERICA_H_INCLUDED
#define LISTAGENERICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define SUCESSO 1
#define INSUCESSO 0

typedef struct NOG {
  void *Info;
  struct NOG *Prox;
} NOG;

typedef struct {
  NOG *Inicio;
  int NEL;
} ListaGenerica;

ListaGenerica *CriarLG();
void DestruirLG(ListaGenerica *L, void (*DestruirInfo)(void *));
int AddLG(ListaGenerica *L, void *X);
void MostrarLG(ListaGenerica *L, void (*MostrarInfo)(void *));
void *RemoveLG(ListaGenerica *L, void *X, int (*Comparador)(void *, void *));

#endif  // LISTAGENERICA_H_INCLUDED
