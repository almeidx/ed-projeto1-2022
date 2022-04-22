#include "BDadosCoupe.h"

#include "ListaGenerica.c"

/** \brief Criar_BDados: A) Criar a Base de dados
 *
 * \param nome_bd char* : Nome da Base de Dados
 * \param versao char*  : Versão da Base de Dados
 * \return BDadosCoupe* : Ponteiro para a Base de Dados Criada
 *
 */
BDadosCoupe *Criar_BDados(char *nome_bd, char *versao) {
  BDadosCoupe *BD = (BDadosCoupe *)malloc(sizeof(BDadosCoupe));
  strcpy(BD->NOME_BDADOS, nome_bd);
  strcpy(BD->VERSAO_BDADOS, versao);
  BD->LTabelas = CriarLG();
  return BD;
}

/** \brief B) Criar uma Tabela na Base de Dados,
 * a tabela deve ser inserida à lista de tabelas da BD
 *
 * \param BD BDadosCoupe* : Ponteiro para a Base de Dados
 * \param nome_tabela char* : Nome da tabela a Criar
 * \return TABELA*        : Retorna a Tabela Criada
 * \author                : CS, FM & JL
 */
TABELA *Criar_Tabela(BDadosCoupe *BD, char *nome_tabela) {
  TABELA *T = (TABELA *)malloc(sizeof(TABELA));
  strcpy(T->NOME_TABELA, nome_tabela);
  T->LCampos = CriarLG();
  T->LRegistos = CriarLG();
  AddLG(BD->LTabelas, T);
  return T;
}

/** \brief C)  Adicionar um campo a uma tabela.
 *
 * \param T TABELA* : Ponteiro para a tabela
 * \param nome_campo char* : Nome do campo
 * \param tipo_campo char* : Tipo do Campo (INT, STRING, CHAR, FLOAT)
 * \return int             : SUCESSO/INSUCESSO
 * \author                 : CS, FM & JL              :
 * \version                : Versao 1.0
 * \date                   : 23/04/2022
 */
int Add_Campo_Tabela(TABELA *T, char *nome_campo, char *tipo_campo) {
  CAMPO *C = (CAMPO *)malloc(sizeof(CAMPO));
  if (!C) return INSUCESSO;
  strcpy(C->NOME_CAMPO, nome_campo);
  strcpy(C->TIPO, tipo_campo);
  int res = AddLG(T->LCampos, C);
  return res;
}

// D)	Adicionar dados(registos) a uma tabela, os dados s�o dados numa string onde o separador � �;�m ex:
// Add_Valores_Tabela(T, �123;Joao;965654449�)
int Add_Valores_Tabela(TABELA *T, char *dados) {
  return SUCESSO;
}

// E)	Adicionar dados(registos) a uma tabela, os dados s�o dados numa string onde o separador � �;�
int Add_Valores_Tabela_BDados(BDadosCoupe *BD, char *nome_tabela, char *dados) {
  TABELA *T = Pesquisar_Tabela(BD, nome_tabela);
  int res = Add_Valores_Tabela(T, dados);
  return res;
}
// F)	Pesquisar uma Tabela da base de dados
TABELA *Pesquisar_Tabela(BDadosCoupe *BD, char *nome_tabela) {
  return NULL;
}

// G)	Mostrar uma Tabela
void Mostrar_Tabela_NOME(BDadosCoupe *BD, char *tabela) {}

void Mostrar_Tabela(TABELA *T) {}

// H)	Mostrar toda a base de dados, dever� mostrar todas as Tabelas da BDados.
void Mostrar_BDados(BDadosCoupe *BD) {}

// I)	Libertar toda a mem�ria alocada pela base de dados.
void Destruir_BDados(BDadosCoupe *BD) {}

// J)	Mem�ria ocupada por toda a base de dados.
long int Memoria_BDados(BDadosCoupe *BD) {
  return -1;
}

long int Memoria_Desperdicada_BDados(BDadosCoupe *BD) {
  return -1;
}

// K)	Exportar/Importar para/de Ficheiro (o retorno destas fun��es, permite saber se a fun��o foi bem/mal-executada!):
int Exportar_Tabela_BDados_Excel(BDadosCoupe *BD, char *tabela, char *ficheir_csv) {
  return SUCESSO;
}

int Exportar_BDados_Excel(BDadosCoupe *BD, char *ficheir_csv) {
  return SUCESSO;
}

int Importar_BDados_Excel(BDadosCoupe *BD, char *ficheir_csv) {
  return SUCESSO;
}

int Exportar_BDados_Ficheiro_Binario(BDadosCoupe *BD, char *fich_dat) {
  return SUCESSO;
}

int Importar_BDados_Ficheiro_Binario(BDadosCoupe *BD, char *fich_dat) {
  return SUCESSO;
}

// L)	Apagar o conte�do de uma Tabela. A Tabela continua a existir na BDados, mas n�o cont�m os dados, ou seja, os
// campos continuam, mas os registos s�o eliminados.
int DELETE_TABLE_DATA(TABELA *T) {
  return SUCESSO;
}

// M)	Apagar o conte�do de uma Tabela e remove a tabela da base de dados.
int DROP_TABLE(BDadosCoupe *BD, char *nome_tabela) {
  return SUCESSO;
}

// N)	Selecionar (Apresentar no ecran!) da base de dados todos os registos que obede�am a uma dada condição, a função
// deve retornar o número de registos selecionados. (Ter em atenção o exemplo das aulas te�ricas!). Nota: esta é
// certamente a funcionalidade mais usada num sistema de base de dados, por isso se estiver bem otimizada. O
// utilizador agradece!!!!
int SELECT(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *nome_campo,
           char *valor_comparacao) {
  return SUCESSO;
}

// O)	Remover todos os registos que obede�am a uma dada condi��o, a fun��o deve retornar o n�mero de registos
// removidos.
int DELETE(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *nome_campo,
           char *valor_comparacao) {
  return SUCESSO;
}

// P)	Atualizar todos os registos da tabela onde o Campo � dado, que obede�am a uma dada condi��o, a fun��o deve
// retornar o n�mero de registos que foram atualizados.
int UPDATE(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *campo_comp, char *valor_campo_comp,
           char *nome_campo_update, char *valor_campo_update) {
  return SUCESSO;
}
