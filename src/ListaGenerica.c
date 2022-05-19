#include "ListaGenerica.h"

ListaGenerica *CriarLG() {
  ListaGenerica *lista = (ListaGenerica *)malloc(sizeof(ListaGenerica));
  if (!lista) return NULL;

  lista->Inicio = NULL;
  lista->NEL = 0;

  return lista;
}

void DestruirLG(ListaGenerica *lista, void (*destruir_info)(void *)) {
  if (!lista) return;

  if (lista->Inicio) {
    NOG *atual = lista->Inicio, *prox = NULL;
    while (atual) {
      prox = atual->Prox;
      destruir_info(atual->Info);
      free(atual);
      atual = prox;
    }
  }

  free(lista);
}

int AddLG(ListaGenerica *lista, void *valor) {
  if (!lista) return INSUCESSO;

  NOG *no = (NOG *)malloc(sizeof(NOG));
  if (!no) return INSUCESSO;

  no->Info = valor;
  no->Prox = NULL;

  if (!lista->Inicio) {
    lista->Inicio = no;
  } else {
    NOG *atual = lista->Inicio;
    while (atual->Prox) {
      atual = atual->Prox;
    }
    atual->Prox = no;
  }

  lista->NEL++;

  return SUCESSO;
}

void *RemoveLG(ListaGenerica *lista, void *valor, int (*f_comparador)(void *, void *)) {
  if (!lista) return NULL;

  NOG *atual = lista->Inicio, *ant = NULL;

  while (atual) {
    if (f_comparador(atual->Info, valor)) {
      if (ant) {
        ant->Prox = atual->Prox;
      } else {
        lista->Inicio = atual->Prox;
      }
      void *info = atual->Info;
      free(atual);
      lista->NEL--;
      return info;
    } else {
      ant = atual;
      atual = atual->Prox;
    }
  }

  return NULL;
}

int RemoveTodosLG(ListaGenerica *lista, void *valor, int (*f_comparador)(void *, void *)) {
  if (!lista) return 0;

  NOG *atual = lista->Inicio, *ant = NULL;
  int contador = 0;

  while (atual) {
    if (f_comparador(atual->Info, valor)) {
      if (ant) {
        ant->Prox = atual->Prox;
      } else {
        lista->Inicio = atual->Prox;
      }
      free(atual->Info);
      free(atual);
      lista->NEL--;
      contador++;
    } else {
      ant = atual;
    }

    atual = atual->Prox;
  }

  return contador;
}

void MostrarLG(ListaGenerica *lista, void (*mostrar_info)(void *)) {
  if (!lista || !lista->NEL) return;

  NOG *atual = lista->Inicio;
  while (atual) {
    mostrar_info(atual->Info);
    atual = atual->Prox;
  }
}
