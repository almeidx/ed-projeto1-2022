#include <stdio.h>
#include <stdlib.h>

#include "BDadosCoupe.c"

/*
  Uma Base de dados Relacional é formada por tabelas, onde cada tabela tem as várias colunas (campos) e os registos
  (informação), um registo é uma coleção de dados. As tabelas podem ter relacionamentos entre elas (mas esta parte
  será dada nas disciplinas de base de dados do 2ºano do curso).
*/
int main() {
  printf("Template do projecto BDadosCoupe para os alunos!\n");
  BDadosCoupe *BD = Criar_BDados("BD-Banco", "Versao 1.0");

  TABELA *T = Criar_Tabela(BD, "CLIENTES");
  Add_Campo_Tabela(T, "ID", "INT");
  Add_Campo_Tabela(T, "NOME", "STRING");
  Add_Valores_Tabela(T, "23;Joao");
  Add_Valores_Tabela_BDados(BD, "CLIENTES", "23;Joao");

  Mostrar_BDados(BD);

  Destruir_BDados(BD);
  return 0;
}
