#include "ListaGenerica.h"

ListaGenerica *CriarLG() {
  ListaGenerica *L = (ListaGenerica *)malloc(sizeof(ListaGenerica));
  L->Inicio = NULL;
  L->NEL = 0;
  return L;
}

void DestuirLG(ListaGenerica *L, void (*func)(void *)) {}

int AddLG(ListaGenerica *L, void *X) {
  return INSUCESSO;
}

void MostrarLG(ListaGenerica *L, void (*fshow)(void *)) {}
