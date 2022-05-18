#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "BDadosCoupe.c"

int condicao(char *, char *);

/*
  Uma Base de dados Relacional é formada por tabelas, onde cada tabela tem as várias colunas (campos) e os registos
  (informação), um registo é uma coleção de dados. As tabelas podem ter relacionamentos entre elas (mas esta parte
  será dada nas disciplinas de base de dados do 2ºano do curso).
*/
int main() {
  printf("Template do projecto BDadosCoupe para os alunos!\n");
  BDadosCoupe *BD = Criar_BDados("BD-Banco", "Versao 1.0");

  char nome_tabela[] = "CLIENTES";
  TABELA *T = Criar_Tabela(BD, nome_tabela);
  Add_Campo_Tabela(T, "ID", "INT");
  Add_Campo_Tabela(T, "NOME", "STRING");

  Add_Valores_Tabela(T, "23;Joao");
  Add_Valores_Tabela(T, "24;Maria");
  Add_Valores_Tabela_BDados(BD, nome_tabela, "25;Tone");
  Add_Valores_Tabela_BDados(BD, nome_tabela, "26;Joana");
  Add_Valores_Tabela_BDados(BD, nome_tabela, "26666666666666666666666666666;Joana");
  Add_Valores_Tabela_BDados(BD, nome_tabela, "333;Joao");
  Add_Valores_Tabela_BDados(BD, nome_tabela, "3334;Joao");

  Mostrar_BDados(BD);

  // printf("Memória em uso: %ld\n", Memoria_BDados(BD));
  // printf("Memória desperdiçada: %ld\n", Memoria_Desperdicada_BDados(BD));

  Exportar_Tabela_BDados_Excel(BD, nome_tabela, "BDados.csv");

  int n;

  // clock_t begin = clock();

  // n = SELECT(BD, "CLIENTES", condicao, "NOME", "Joana");

  // clock_t end = clock();
  // double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  // printf("SELECT amount: %d\n", n);
  // printf("SELECT time spent: %f\n", time_spent);

  printf("DELETE amount: %d\n", DELETE(BD, "CLIENTES", condicao, "NOME", "Joana"));

  // DELETE(BD, "CLIENTES", condicao, "NOME", "Joao");

  // DELETE_TABLE_DATA(T);

  // DROP_TABLE(BD, nome_tabela);

  Mostrar_BDados(BD);

  printf("Memória em uso depois de apagar: %ld\n", Memoria_BDados(BD));

  Destruir_BDados(BD);

  return 0;
}

int condicao(char *nome1, char *nome2) {
  return strcmp(nome1, nome2) == 0;
}
