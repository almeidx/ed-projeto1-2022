#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "BDadosCoupe.c"
#include "tests.c"

int condicao(char *, char *);

/*
  Uma Base de dados Relacional é formada por tabelas, onde cada tabela tem as várias colunas (campos) e os registos
  (informação), um registo é uma coleção de dados. As tabelas podem ter relacionamentos entre elas (mas esta parte
  será dada nas disciplinas de base de dados do 2ºano do curso).
*/
int main() {
  // printf("Template do projecto BDadosCoupe para os alunos!\n");

  // // printf("Memória em uso: %ld\n", Memoria_BDados(BD));
  // // printf("Memória desperdiçada: %ld\n", Memoria_Desperdicada_BDados(BD));

  // // Exportar_Tabela_BDados_Excel(BD, nome_tabela, "BDados.csv");

  // int n;

  // // clock_t begin = clock();

  // // n = SELECT(BD, "CLIENTES", condicao, "NOME", "Joana");

  // // clock_t end = clock();
  // // double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  // // printf("SELECT amount: %d\n", n);
  // // printf("SELECT time spent: %f\n", time_spent);

  // // clock_t begin = clock();

  // // n = DELETE(BD, "CLIENTES", condicao, "NOME", "Joana");

  // // clock_t end = clock();
  // // double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  // // printf("DELETE amount: %d\n", n);
  // // printf("DELETE time spent: %f\n", time_spent);

  // UPDATE(BD, "CLIENTES", condicao, "NOME", "Joana", "CLIENTES", "Jaquim");

  // // DELETE_TABLE_DATA(T);

  // // DROP_TABLE(BD, nome_tabela);

  // // printf("Memória em uso depois de apagar: %ld\n", Memoria_BDados(BD));

  // Destruir_BDados(BD);

  // test_import_regions_excel();

  // test_import_vehicle_data_excel();

  // test_import_bdados_excel();

  test_export_bdados_excel();

  return 0;
}

int condicao(char *nome1, char *nome2) {
  return strcmp(nome1, nome2) == 0;
}
