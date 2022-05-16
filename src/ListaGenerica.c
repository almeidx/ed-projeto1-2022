#include "ListaGenerica.h"

ListaGenerica *CriarLG() {
  ListaGenerica *L = (ListaGenerica *)malloc(sizeof(ListaGenerica));
  if (!L) return NULL;

  L->Inicio = NULL;
  L->NEL = 0;

  return L;
}

void DestruirLG(ListaGenerica *L, void (*DestruirInfo)(void *)) {
  if (!L) return;

  if (L->Inicio) {
    NOG *atual = L->Inicio, *prox = NULL;
    while (atual) {
      prox = atual->Prox;
      DestruirInfo(atual->Info);
      free(atual);
      atual = prox;
    }
  }

  free(L);
}

int AddLG(ListaGenerica *L, void *X) {
  if (!L) return INSUCESSO;

  NOG *no = (NOG *)malloc(sizeof(NOG));
  if (!no) return INSUCESSO;

  no->Info = X;
  no->Prox = NULL;

  if (!L->Inicio) {
    L->Inicio = no;
  } else {
    NOG *atual = L->Inicio;
    while (atual->Prox) {
      atual = atual->Prox;
    }
    atual->Prox = no;
  }

  L->NEL++;

  return SUCESSO;
}

void *RemoveLG(ListaGenerica *L, void *X, int (*Comparador)(void *, void *)) {
  if (!L) return NULL;

  NOG *atual = L->Inicio, *ant = NULL;

  while (atual) {
    if (Comparador(atual->Info, X)) {
      if (ant) {
        ant->Prox = atual->Prox;
      } else {
        L->Inicio = atual->Prox;
      }
      void *info = atual->Info;
      free(atual);
      L->NEL--;
      return info;
    } else {
      ant = atual;
      atual = atual->Prox;
    }
  }

  return NULL;
}

void MostrarLG(ListaGenerica *L, void (*MostrarInfo)(void *)) {
  if (!L) return;

  if (L->Inicio) {
    NOG *atual = L->Inicio;
    while (atual) {
      MostrarInfo(atual->Info);
      atual = atual->Prox;
    }
  }
}
