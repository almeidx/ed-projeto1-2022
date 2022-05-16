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

// D)	Adicionar dados(registos) a uma tabela, os dados são dados numa string onde o separador é ';' ex:
// Add_Valores_Tabela(T, "123;Joao;965654449")
int Add_Valores_Tabela(TABELA *T, char *dados) {
  REGISTO *registo = CriarLG();
  if (!registo) return INSUCESSO;

  char *dados_clone = (char *)malloc(sizeof(char) * (strlen(dados) + 1));
  strcpy(dados_clone, dados);

  char *token = strtok(dados_clone, ";");
  if (!token) {
    free(registo);
    return INSUCESSO;
  }

  char **dados_holder = (char **)malloc(sizeof(char *) * T->LCampos->NEL);
  int i = 0;

  while (token) {
    dados_holder[i] = (char *)malloc(sizeof(char) * (strlen(token) + 1));
    strcpy(dados_holder[i], token);

    token = strtok(NULL, ";");
    i++;
  }

  // Não podemos usar esta função diretamente no loop acima por causa do strtok
  for (int j = 0; j < T->LCampos->NEL; j++) {
    AddLG(registo, dados_holder[j]);
  }

  AddLG(T->LRegistos, registo);

  free(dados_clone);
  free(dados_holder);

  return SUCESSO;
}

// E)	Adicionar dados(registos) a uma tabela, os dados são dados numa string onde o separador � �;�
int Add_Valores_Tabela_BDados(BDadosCoupe *BD, char *nome_tabela, char *dados) {
  TABELA *T = Pesquisar_Tabela(BD, nome_tabela);
  int res = Add_Valores_Tabela(T, dados);
  return res;
}

// F)	Pesquisar uma Tabela da base de dados
TABELA *Pesquisar_Tabela(BDadosCoupe *BD, char *nome_tabela) {
  NOG *aux = BD->LTabelas->Inicio;
  while (aux) {
    TABELA *T = (TABELA *)aux->Info;
    if (!strcmp(T->NOME_TABELA, nome_tabela)) return T;
    aux = aux->Prox;
  }
  return NULL;
}

// G)	Mostrar uma Tabela
void Mostrar_Tabela_NOME(BDadosCoupe *BD, char *tabela) {
  TABELA *T = Pesquisar_Tabela(BD, tabela);
  if (!T) return;

  Mostrar_Tabela(T);
}

void Mostrar_Lista_Campos(TABELA *T) {
  NOG *aux = T->LCampos->Inicio;
  while (aux) {
    CAMPO *C = (CAMPO *)aux->Info;
    printf("\t\t%s (%s)\n", C->NOME_CAMPO, C->TIPO);
    aux = aux->Prox;
  }
}

void Mostrar_Lista_Registos(TABELA *T) {
  NOG *aux = T->LRegistos->Inicio;
  while (aux) {
    REGISTO *R = (REGISTO *)aux->Info;
    NOG *aux2 = R->Inicio;
    while (aux2) {
      printf("\t\t%s\n", (char *)aux2->Info);
      aux2 = aux2->Prox;
    }
    aux = aux->Prox;
  }
}

void Mostrar_Tabela(TABELA *T) {
  if (!T) return;

  printf("----- TABELA -----\n");
  printf("\tNome: %s\n", T->NOME_TABELA);
  printf("\tCampos:\n");
  Mostrar_Lista_Campos(T);
  printf("\tRegistos:\n");
  Mostrar_Lista_Registos(T);
  printf("------------------\n");
}

// H)	Mostrar toda a base de dados, deverá mostrar todas as Tabelas da BDados.
void Mostrar_BDados(BDadosCoupe *BD) {
  NOG *aux = BD->LTabelas->Inicio;

  printf("----- BASE DE DADOS -----\n");

  while (aux) {
    TABELA *T = (TABELA *)aux->Info;
    Mostrar_Tabela(T);
    aux = aux->Prox;
  }

  printf("-------------------------\n");
}

void Destruir_Campo(void *info) {
  CAMPO *campo = info;
  free(campo);
}

void Destruir_Registo(void *info) {
  free(info);
}

void Destruir_Tabela(void *info) {
  TABELA *T = info;
  if (!T) return;

  DestruirLG(T->LCampos, Destruir_Campo);
  DestruirLG(T->LRegistos, Destruir_Registo);
  free(T);
}

// I)	Libertar toda a memória alocada pela base de dados.
void Destruir_BDados(BDadosCoupe *BD) {
  if (!BD) return;

  DestruirLG(BD->LTabelas, Destruir_Tabela);
  free(BD);
}

long int Memoria_Tabela(TABELA *T) {
  long int memoria = 0;

  memoria += sizeof(TABELA);
  memoria += sizeof(char) * (strlen(T->NOME_TABELA) + 1);

  memoria += sizeof(NOG) * T->LCampos->NEL;
  memoria += sizeof(NOG) * T->LRegistos->NEL;

  NOG *aux = T->LCampos->Inicio;
  while (aux) {
    CAMPO *C = (CAMPO *)aux->Info;
    memoria += sizeof(CAMPO);
    memoria += sizeof(char) * (strlen(C->NOME_CAMPO) + 1);
    memoria += sizeof(char) * (strlen(C->TIPO) + 1);
    aux = aux->Prox;
  }

  NOG *aux2 = T->LRegistos->Inicio;
  while (aux2) {
    REGISTO *R = (REGISTO *)aux2->Info;
    NOG *aux3 = R->Inicio;
    while (aux3) {
      memoria += sizeof(char) * (strlen((char *)aux3->Info) + 1);
      aux3 = aux3->Prox;
    }
    aux2 = aux2->Prox;
  }

  return memoria;
}

// J)	Memória ocupada por toda a base de dados.
long int Memoria_BDados(BDadosCoupe *BD) {
  if (!BD) return -1;

  long int memoria = sizeof(BD);

  memoria += strlen(BD->NOME_BDADOS) + 1;
  memoria += strlen(BD->VERSAO_BDADOS) + 1;
  memoria += sizeof(NOG) * BD->LTabelas->NEL;

  NOG *aux = BD->LTabelas->Inicio;

  while (aux) {
    TABELA *T = (TABELA *)aux->Info;
    memoria += Memoria_Tabela(T);
    aux = aux->Prox;
  }

  return memoria;
}

/*
  Memória geral desperdiçada na base de dados:
  - no nome da base de dados, a string tem um máximo de 51 caracteres (contando com o \0)
  - na versão da base de dados, a string tem um máximo de 51 caracteres
  - no nome da tabela, a string tem um máximo de 51 caracteres

  Memória desperdiçada por cada tabela:
  - no nome do campo, a string tem um máximo de 51 caracteres
  - no tipo do campo, a string tem um máximo de 11 caracteres
  - todos os registos são guardados como strings, porém, no caso de serem numeros (int), poderá haver desperdicio de
    memória no caso de os números serem grandes, por exemplo:
    - 4 000 000 000 pode ser guardado como int, que só ocupa 4 bytes, mas como está a ser guardado numa string, ocupa 12
      bytes. Se fizessemos uma transformação para int, poderiamos salvar 6 bytes.
    O mesmo se aplica para outros tipos de dados.
 */
long int Memoria_Desperdicada_BDados(BDadosCoupe *BD) {
  if (!BD) return -1;

  long int memoria = 0;

  size_t tamanho_aux = strlen(BD->NOME_BDADOS) + 1;
  if (tamanho_aux < MAX_NOME_BDADOS) memoria += MAX_NOME_BDADOS - tamanho_aux;

  tamanho_aux = strlen(BD->VERSAO_BDADOS) + 1;
  if (tamanho_aux < MAX_VERSAO_BDADOS) memoria += MAX_VERSAO_BDADOS - tamanho_aux;

  NOG *tabela = BD->LTabelas->Inicio;
  while (tabela) {
    TABELA *T = tabela->Info;

    tamanho_aux = strlen(T->NOME_TABELA) + 1;
    if (tamanho_aux < MAX_NOME_TABELA) memoria += MAX_NOME_TABELA - tamanho_aux;

    NOG *campo = T->LCampos->Inicio;
    while (campo) {
      CAMPO *C = campo->Info;

      tamanho_aux = strlen(C->NOME_CAMPO) + 1;
      if (tamanho_aux < MAX_NOME_CAMPO) memoria += MAX_NOME_CAMPO - tamanho_aux;

      tamanho_aux = strlen(C->TIPO) + 1;
      if (tamanho_aux < MAX_TIPO) memoria += MAX_TIPO - tamanho_aux;

      campo = campo->Prox;
    }

    NOG *registo = T->LRegistos->Inicio;
    while (registo) {
      REGISTO *R = registo->Info;

      NOG *registo_atual = R->Inicio;
      NOG *campo_atual = T->LCampos->Inicio;
      while (registo_atual) {
        char *info = registo_atual->Info;
        CAMPO *C = campo_atual->Info;

        if (C->TIPO == "INT") {
          tamanho_aux = strlen(info) + 1;
          if (tamanho_aux > sizeof(int)) memoria += sizeof(int) - tamanho_aux;
        }

        registo_atual = registo_atual->Prox;
        campo_atual = campo_atual->Prox;
      }

      registo = registo->Prox;
    }

    tabela = tabela->Prox;
  }

  return memoria;
}

// K)	Exportar/Importar para/de Ficheiro (o retorno destas funções, permite saber se a função foi bem/mal-executada!):
int Exportar_Tabela_BDados_Excel(BDadosCoupe *BD, char *tabela, char *ficheiro_csv) {
  if (!BD || !tabela || !ficheiro_csv) return INSUCESSO;

  TABELA *T = Pesquisar_Tabela(BD, tabela);
  if (!T) return INSUCESSO;

  FILE *f = fopen(ficheiro_csv, "w");
  if (!f) return INSUCESSO;

  NOG *campo = T->LCampos->Inicio;
  while (campo) {
    CAMPO *C = campo->Info;
    if (campo->Prox) {
      fprintf(f, "%s;", C->NOME_CAMPO);
    } else {
      fprintf(f, "%s", C->NOME_CAMPO);
    }
    campo = campo->Prox;
  }

  fprintf(f, "\n");

  NOG *registo = T->LRegistos->Inicio;
  while (registo) {
    REGISTO *R = registo->Info;

    NOG *registo_atual = R->Inicio;
    while (registo_atual) {
      if (registo_atual->Prox) {
        fprintf(f, "%s;", registo_atual->Info);
      } else {
        fprintf(f, "%s", registo_atual->Info);
      }

      registo_atual = registo_atual->Prox;
    }

    fprintf(f, "\n");

    registo = registo->Prox;
  }

  fclose(f);

  return SUCESSO;
}

int Importar_Tabela_BDados_Excel(BDadosCoupe *BD, char *nome_tabela, char *ficheiro_csv) {}

int Exportar_BDados_Excel(BDadosCoupe *BD, char *ficheiro_csv) {
  return SUCESSO;
}

int Importar_BDados_Excel(BDadosCoupe *BD, char *ficheiro_csv) {
  return SUCESSO;
}

int Exportar_BDados_Ficheiro_Binario(BDadosCoupe *BD, char *ficheiro_dat) {
  return SUCESSO;
}

int Importar_BDados_Ficheiro_Binario(BDadosCoupe *BD, char *ficheiro_dat) {
  return SUCESSO;
}

// L)	Apagar o conteúdo de uma Tabela. A Tabela continua a existir na BDados, mas não contém os dados, ou
// seja, os campos continuam, mas os registos são eliminados.
int DELETE_TABLE_DATA(TABELA *T) {
  if (!T) return INSUCESSO;

  DestruirLG(T->LRegistos, Destruir_Registo);
  T->LRegistos = CriarLG();
  if (!T->LRegistos) return INSUCESSO;

  return SUCESSO;
}

int comparar_tabela(void *T1, void *T2) {
  if (!T1 || !T2) return 0;

  TABELA *_T1 = (TABELA *)T1, *_T2 = (TABELA *)T2;

  return strcmp(_T1->NOME_TABELA, _T2->NOME_TABELA) == 0;
}

// M)	Apagar o conteúdo de uma Tabela e remove a tabela da base de dados.
int DROP_TABLE(BDadosCoupe *BD, char *nome_tabela) {
  if (!BD || !nome_tabela) return INSUCESSO;

  TABELA *T = Pesquisar_Tabela(BD, nome_tabela);
  if (!T) return INSUCESSO;

  if (DELETE_TABLE_DATA(T) == INSUCESSO) return INSUCESSO;

  if (RemoveLG(BD->LTabelas, T, comparar_tabela)) return SUCESSO;

  return SUCESSO;
}

// N)	Selecionar (Apresentar no ecran!) da base de dados todos os registos que obedeçam a uma dada condição,
// a função deve retornar o número de registos selecionados. (Ter em atenção o exemplo das aulas teóricas!). Nota:
// esta é certamente a funcionalidade mais usada num sistema de base de dados, por isso se estiver bem otimizada.
// O utilizador agradece!!!!
int SELECT(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *nome_campo,
           char *valor_comparacao) {
  if (!BD || !_tabela || !f_condicao || !nome_campo || !valor_comparacao) return INSUCESSO;

  TABELA *T = Pesquisar_Tabela(BD, _tabela);
  if (!T) return INSUCESSO;

  NOG *registo = T->LRegistos->Inicio;
  int contador = 0;

  while (registo) {
    REGISTO *R = registo->Info;

    NOG *registo_atual = R->Inicio;
    while (registo_atual) {
      if (f_condicao(registo_atual->Info, valor_comparacao)) {
        printf("%s: %s\n", __FUNCTION__, registo_atual->Info);
        contador++;

        break;
      }

      registo_atual = registo_atual->Prox;
    }

    registo = registo->Prox;
  }

  return contador;
}

// O)	Remover todos os registos que obede�am a uma dada condi��o, a fun��o deve retornar o n�mero de registos
// removidos.
int DELETE(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *nome_campo,
           char *valor_comparacao) {
  return SUCESSO;
}

// P)	Atualizar todos os registos da tabela onde o Campo � dado, que obede�am a uma dada condição, a função
// deve retornar o número de registos que foram atualizados.
int UPDATE(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *campo_comp, char *valor_campo_comp,
           char *nome_campo_update, char *valor_campo_update) {
  return SUCESSO;
}
