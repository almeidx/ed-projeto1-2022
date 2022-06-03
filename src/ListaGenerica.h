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

/**
 * @brief Cria uma lista genérica
 * @returns A lista criada ou NULL caso a criação falhe
 */
ListaGenerica *CriarLG();

/**
 * @brief Destrói uma lista genérica e liberta toda a memória alocada
 * @param lista A lista a ser destruída
 * @param destruir_info Função que destrói a `Info` de cada elemento da lista
 */
void DestruirLG(ListaGenerica *lista, void (*destruir_info)(void *));

/**
 * @brief Adiciona um elemento a uma lista
 * @param lista Lista a ser manipulada
 * @param valor Valor a ser adicionado
 * @return SUCESSO ou INSUCESSO
 */
int AddLG(ListaGenerica *lista, void *valor);

/**
 * @brief Remove o primeiro elemento de uma lista que satisfaça a função comparadora
 * @param lista Lista a ser manipulada
 * @param valor Valor a ser comparado
 * @param f_comparador Função para comparar a `Info` de cada elemento com `X`
 * @return A `Info` do elemento removido, ou NULL caso nenhum elemento tenha passado a função comparadora
 */
void *RemoveLG(ListaGenerica *lista, void *valor, int (*f_comparador)(void *, void *));

/**
 * @brief Remove todos os items de uma lista que satisfazem a função de comparadora passada
 * @param lista Lista a ser manipulada
 * @param valor Valor a ser comparado
 * @param f_comparador Função para comparar a `Info` de cada elemento com `X`
 * @return A quantidade de elementos removidos
 */
int RemoveTodosLG(ListaGenerica *lista, void *valor, int (*f_comparador)(void *, void *));

/**
 * @brief Mostra todos os items de uma lista
 * @param lista Lista a ser mostrada
 * @param mostrar_info Função para mostrar a `Info` de cada elemento
 */
void MostrarLG(ListaGenerica *lista, void (*mostrar_info)(void *));

#endif  // LISTAGENERICA_H_INCLUDED
