#ifndef BDADOSCOUPE_H_INCLUDED
#define BDADOSCOUPE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListaGenerica.h"

#define MAX_NOME_BDADOS 51
#define MAX_VERSAO_BDADOS 51
#define SEPARADOR_TABELA "------------------------------------------"

// Faz com que o Excel consiga ler os dados dos ficheiros exportados
#define DEF_EXCEL_SEPARADOR "sep=;"

// Comentar esta linha para desativar o reporte de tempo de execução das funções SELECT, DELETE, UPDATE
#define DEBUG_TIMINGS
#define FICHEIRO_DEBUG_TIMINGS "C:\\Users\\Utilizador\\OneDrive - ESTGV\\ED\\ed-projeto1-2022\\timings.txt"

// Usamos uma "variadic macro" de modo a não repetir isto 3 vezes
// https://en.wikipedia.org/wiki/Variadic_macro_in_the_C_preprocessor
#define WRITE_TIMING(start, format, ...) clock_t end = clock(); \
    FILE *f = fopen(FICHEIRO_DEBUG_TIMINGS, "a"); \
    if (f) { \
        fprintf(f, format, __FUNCTION__, __VA_ARGS__, (double) (end - start) / CLOCKS_PER_SEC); \
        fclose(f); \
    }

#ifdef DEBUG_TIMINGS

#include <time.h>

#endif

typedef struct {
    char NOME_BDADOS[MAX_NOME_BDADOS];
    char VERSAO_BDADOS[MAX_VERSAO_BDADOS];
    ListaGenerica *LTabelas;
} BDadosCoupe;

#define MAX_NOME_TABELA 51

typedef struct {
    char NOME_TABELA[MAX_NOME_TABELA];
    ListaGenerica *LCampos;
    ListaGenerica *LRegistos;
} TABELA;

#define MAX_NOME_CAMPO 51
#define MAX_TIPO 11

typedef struct {
    char NOME_CAMPO[MAX_NOME_CAMPO];
    char TIPO[MAX_TIPO];
} CAMPO;

#define REGISTO ListaGenerica
#define MAX_LINHA 120

// A) Criar a Base de dados;
BDadosCoupe *Criar_BDados(char *nome_bd, char *versao);

// B) Criar uma Tabela na Base de Dados, a tabela deve ser inserida à lista de tabelas da BD
TABELA *Criar_Tabela(BDadosCoupe *BD, char *nome_tabela);

// C) Adicionar um campo a uma tabela.
int Add_Campo_Tabela(TABELA *T, char *nome_campo, char *tipo_campo);

// D) Adicionar dados(registos) a uma tabela, os dados são dados numa string onde o separador é ";"
// ex: Add_Valores_Tabela(T, "123;Joao;965654449")
int Add_Valores_Tabela(TABELA *T, char *dados);

// E) Adicionar dados(registos) a uma tabela, os dados são dados numa string onde o separador é ";"
int Add_Valores_Tabela_BDados(BDadosCoupe *BD, char *nome_tabela, char *dados);

// F) Pesquisar uma Tabela da base de dados
TABELA *Pesquisar_Tabela(BDadosCoupe *BD, char *nome_tabela);

// G) Mostrar uma Tabela
void Mostrar_Tabela_NOME(BDadosCoupe *BD, char *tabela);

void Mostrar_Tabela(TABELA *T);

// H) Mostrar toda a base de dados, deverá mostrar todas as Tabelas da BDados.
void Mostrar_BDados(BDadosCoupe *BD);

// I) Libertar toda a memória alocada pela base de dados.
void Destruir_BDados(BDadosCoupe *BD);

// J) Memória ocupada por toda a base de dados.
long int Memoria_BDados(BDadosCoupe *BD);

long int Memoria_Desperdicada_BDados(BDadosCoupe *BD);

// K) Exportar/Importar para/de Ficheiro (o retorno destas funções, permite saber se a função foi bem/mal-executada!):
int Exportar_Tabela_BDados_Excel(BDadosCoupe *BD, char *tabela, char *ficheiro_csv);

int Exportar_BDados_Excel(BDadosCoupe *BD, char *ficheiro_csv);

int Importar_BDados_Excel(BDadosCoupe *BD, char *ficheiro_csv);

int Exportar_BDados_Ficheiro_Binario(BDadosCoupe *BD, char *ficheiro_dat);

int Importar_BDados_Ficheiro_Binario(BDadosCoupe *BD, char *ficheiro_dat);

// L) Apagar o conteúdo de uma Tabela. A Tabela continua a existir na BDados, mas não contém os dados, ou seja, os
// campos continuam, mas os registos são eliminados.
int DELETE_TABLE_DATA(TABELA *T);

// M) Apagar o conteúdo de uma Tabela e remove a tabela da base de dados.
int DROP_TABLE(BDadosCoupe *BD, char *nome_tabela);

// N) Selecionar (Apresentar no ecrã!) da base de dados todos os registos que obedeçam a uma dada condição, a função
// deve retornar o número de registos selecionados. (Ter em atenção o exemplo das aulas teóricas!). Nota: esta è
// certamente a funcionalidade mais usada num sistema de base de dados, por isso se estiver bem otimizada. O
// utilizador agradece!!!!
int SELECT(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *nome_campo, char *valor_comparacao);

// O) Remover todos os registos que obedeçam a uma dada condição, a função deve retornar o número de registos removidos.
int DELETE(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *nome_campo, char *valor_comparacao);

// P) Atualizar todos os registos da tabela onde o Campo é dado, que obedeçam a uma dada condição, a função deve
// retornar o número de registos que foram atualizados.
int UPDATE(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *campo_comp, char *valor_campo_comp,
           char *nome_campo_update, char *valor_campo_update);

void Destruir_Tabela(void *info);

void Destruir_Registo(void *info);

void Destruir_Campo(void *info);

/**
 * Escreve os dados de uma tabela num ficheiro csv
 * @param f O ficheiro onde a tabela vai ser exportada
 * @param T A tabela que vai ser exportada
 */
void Escrever_Tabela_Excel(FILE *f, TABELA *T);

/**
 * Compara duas tabelas
 * @param T1 A primeira tabela a comparar
 * @param T2 A segunda tabela a comparar
 * @return 1 se as tabelas forem iguais, 0 se forem diferentes
 */
int comparar_tabela(void *T1, void *T2);

/**
 * Retorna o primeiro campo que tenha o nome dado, e passa o seu indice pela variável indice
 * @param T Tabela a procurar o campo
 * @param nome_campo Nome do campo a procurar
 * @param indice Ponteiro para o indice do campo
 * @return Retorna o campo encontrado, ou NULL se não encontrar
 */
CAMPO *encontrar_indice_campo(TABELA *T, char *nome_campo, int *indice);

/**
 * Compara dois registos
 * @param reg1 O primeiro registo a comparar
 * @param reg2 O segundo registo a comparar
 * @return 1 se os registos forem iguais, 0 se forem diferentes
 */
int comparar_registos(void *reg1, void *reg2);

#endif  // BDADOSCOUPE_H_INCLUDED
