#include "BDadosCoupe.h"

#include "ListaGenerica.h"

/**
 * \brief Criar_BDados: A) Criar a Base de dados
 *
 * \param nome_bd char* : Nome da Base de Dados
 * \param versao char*  : Versão da Base de Dados
 * \return BDadosCoupe* : Ponteiro para a Base de Dados Criada
 */
BDadosCoupe *Criar_BDados(char *nome_bd, char *versao) {
    if (!nome_bd || !versao) return NULL;

    BDadosCoupe *BD = (BDadosCoupe *) malloc(sizeof(BDadosCoupe));
    if (!BD) return NULL;

    strcpy(BD->NOME_BDADOS, nome_bd);
    strcpy(BD->VERSAO_BDADOS, versao);

    BD->LTabelas = CriarLG();
    if (!BD->LTabelas) {
        free(BD);
        return NULL;
    }

    return BD;
}

/**
 * \brief B) Criar uma Tabela na Base de Dados, a tabela deve ser inserida à lista de tabelas da BD
 *
 * \param BD BDadosCoupe* : Ponteiro para a Base de Dados
 * \param nome_tabela char* : Nome da tabela a Criar
 * \return TABELA*        : Retorna a Tabela Criada
 * \author                : CS, FM & JL
 */
TABELA *Criar_Tabela(BDadosCoupe *BD, char *nome_tabela) {
    if (!BD || !nome_tabela) return NULL;

    TABELA *T = (TABELA *) malloc(sizeof(TABELA));
    if (!T) return NULL;

    strcpy(T->NOME_TABELA, nome_tabela);

    T->LCampos = CriarLG();
    if (!T->LCampos) {
        free(T);
        return NULL;
    }

    T->LRegistos = CriarLG();
    if (!T->LRegistos) {
        free(T->LCampos);
        free(T);
        return NULL;
    }

    int res = AddLG(BD->LTabelas, T);
    if (!res) {
        DestruirLG(T->LCampos, Destruir_Campo);
        DestruirLG(T->LRegistos, Destruir_Registo);
        free(T);
        return NULL;
    }

    return T;
}

/**
 * \brief C)  Adicionar um campo a uma tabela.
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
    if (!T || !nome_campo || !tipo_campo) return INSUCESSO;

    CAMPO *C = (CAMPO *) malloc(sizeof(CAMPO));
    if (!C) return INSUCESSO;

    strcpy(C->NOME_CAMPO, nome_campo);
    strcpy(C->TIPO, tipo_campo);

    return AddLG(T->LCampos, C);
}

// D)	Adicionar dados(registos) a uma tabela, os dados são dados numa string onde o separador é ';' ex:
// Add_Valores_Tabela(T, "123;Joao;965654449")
int Add_Valores_Tabela(TABELA *T, char *dados) {
    if (!T || !dados) return INSUCESSO;

    REGISTO *registo = CriarLG();
    if (!registo) return INSUCESSO;

    char *dados_clone = (char *) malloc(sizeof(char) * (strlen(dados) + 1));
    if (!dados_clone) {
        DestruirLG(registo, Destruir_Registo);
        return INSUCESSO;
    }

    strcpy(dados_clone, dados);

    char *token = strtok(dados_clone, ";");
    if (!token) {
        DestruirLG(registo, Destruir_Registo);
        free(dados_clone);
        return INSUCESSO;
    }

    char **dados_holder = (char **) malloc(sizeof(char *) * T->LCampos->NEL);
    if (!dados_holder) {
        DestruirLG(registo, Destruir_Registo);
        free(dados_clone);
        return INSUCESSO;
    }

    int i = 0;

    while (token) {
        dados_holder[i] = (char *) malloc(sizeof(char) * (strlen(token) + 1));
        if (!dados_holder[i]) {
            DestruirLG(registo, Destruir_Registo);
            free(dados_clone);
            for (int j = 0; j < i; j++) free(dados_holder[j]);
            free(dados_holder);
            return INSUCESSO;
        }

        strcpy(dados_holder[i], token);

        token = strtok(NULL, ";");
        i++;
    }

    // Não podemos usar esta função diretamente no loop acima devido à maneira de como o strtok funciona
    for (int j = 0; j < T->LCampos->NEL; j++) {
        AddLG(registo, dados_holder[j]);
    }

    AddLG(T->LRegistos, registo);

    free(dados_clone);

    return SUCESSO;
}

// E)	Adicionar dados(registos) a uma tabela, os dados são dados numa string onde o separador � �;�
int Add_Valores_Tabela_BDados(BDadosCoupe *BD, char *nome_tabela, char *dados) {
    if (!BD || !nome_tabela || !dados) return INSUCESSO;

    TABELA *T = Pesquisar_Tabela(BD, nome_tabela);
    if (!T) return INSUCESSO;

    return Add_Valores_Tabela(T, dados);
}

// F)	Pesquisar uma Tabela da base de dados
TABELA *Pesquisar_Tabela(BDadosCoupe *BD, char *nome_tabela) {
    if (!BD || !nome_tabela) return NULL;

    NOG *tabela = BD->LTabelas->Inicio;
    while (tabela) {
        TABELA *T = (TABELA *) tabela->Info;
        if (strcmp(T->NOME_TABELA, nome_tabela) == 0) return T;
        tabela = tabela->Prox;
    }

    return NULL;
}

// G)	Mostrar uma Tabela
void Mostrar_Tabela_NOME(BDadosCoupe *BD, char *tabela) {
    if (!BD || !tabela) return;

    TABELA *T = Pesquisar_Tabela(BD, tabela);
    if (!T) return;

    Mostrar_Tabela(T);
}

void Mostrar_Campo(void *campo) {
    if (!campo) return;

    CAMPO *C = (CAMPO *) campo;
    printf("\n\t\t%s (%s)", C->NOME_CAMPO, C->TIPO);
}

void Mostrar_Registo(void *registo) {
    if (!registo) return;

    printf("\t");
    NOG *registo_atual = ((REGISTO *) registo)->Inicio;
    while (registo_atual) {
        printf("\t%s\t", (char *) registo_atual->Info);
        registo_atual = registo_atual->Prox;
    }
    printf("\n");
}

void Mostrar_Tabela(TABELA *T) {
    if (!T) return;

    printf("----- TABELA -----\n");
    printf("\tNome: %s\n", T->NOME_TABELA);
    printf("\tCampos (%d):", T->LCampos->NEL);
    MostrarLG(T->LCampos, Mostrar_Campo);
    printf("\n\tRegistos (%d):\n", T->LRegistos->NEL);
    MostrarLG(T->LRegistos, Mostrar_Registo);
    printf("------------------\n");
}

// H)	Mostrar toda a base de dados, deverá mostrar todas as Tabelas da BDados.
void Mostrar_BDados(BDadosCoupe *BD) {
    if (!BD) return;

    printf("----- BASE DE DADOS -----\n");

    NOG *tabela = BD->LTabelas->Inicio;
    while (tabela) {
        TABELA *T = (TABELA *) tabela->Info;
        Mostrar_Tabela(T);
        tabela = tabela->Prox;
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
    // Nome e os ponteiros para a lista de campos e a de registos
    long int memoria = sizeof(TABELA);

    // Lista de campos e a de registos
    memoria += sizeof(ListaGenerica) * 2;

    // Nós e campos da lista de campos
    memoria += sizeof(NOG) * T->LCampos->NEL;
    memoria += sizeof(CAMPO) * T->LCampos->NEL;

    // Nós e registos da lista de registos
    memoria += sizeof(NOG) * T->LRegistos->NEL;
    memoria += sizeof(REGISTO) * T->LRegistos->NEL;

    NOG *registo = T->LRegistos->Inicio;
    while (registo) {
        REGISTO *R = (REGISTO *) registo->Info;
        NOG *registo_atual = R->Inicio;
        while (registo_atual) {
            memoria += sizeof(char) * (strlen((char *) registo_atual->Info) + 1);
            registo_atual = registo_atual->Prox;
        }
        registo = registo->Prox;
    }

    return memoria;
}

// J)	Memória ocupada por toda a base de dados.
long int Memoria_BDados(BDadosCoupe *BD) {
    if (!BD) return -1;

    // Nome, versão e o ponteiro para a lista de tabelas
    long int memoria = sizeof(BDadosCoupe);

    // Lista de tabelas
    memoria += sizeof(ListaGenerica);

    NOG *tabela = BD->LTabelas->Inicio;
    while (tabela) {
        TABELA *T = (TABELA *) tabela->Info;
        memoria += Memoria_Tabela(T);
        tabela = tabela->Prox;
    }

    return memoria;
}

/*
 * Memória geral desperdiçada na base de dados:
 *  — no nome da base de dados, a string tem um máximo de 51 caracteres (contando com o \0)
 *  — na versão da base de dados, a string tem um máximo de 51 caracteres
 *  — no nome da tabela, a string tem um máximo de 51 caracteres
 *
 * Memória desperdiçada por cada tabela:
 *  — no nome do campo, a string tem um máximo de 51 caracteres
 *  — no tipo do campo, a string tem um máximo de 11 caracteres
 *  — todos os registos são guardados como strings, porém, no caso de serem numeros (int), poderá haver desperdicio de
 *    memória no caso de os números serem grandes, por exemplo:
 *      — 2 000 000 000 pode ser guardado como int, que só ocupa 4 bytes, mas como é guardado numa string,
 *        ocupa 11 bytes. Ou seja, se fizessemos uma transformação para int, poderiamos salvar 7 bytes.
 *      O mesmo se aplica para outros tipos de dados.
 */
long int Memoria_Desperdicada_BDados(BDadosCoupe *BD) {
    if (!BD) return -1;

    long int memoria = 0;

    size_t nome_bdados_len = strlen(BD->NOME_BDADOS) + 1;
    if (nome_bdados_len < MAX_NOME_BDADOS) memoria += MAX_NOME_BDADOS - nome_bdados_len;

    size_t versao_bdados_len = strlen(BD->VERSAO_BDADOS) + 1;
    if (versao_bdados_len < MAX_VERSAO_BDADOS) memoria += MAX_VERSAO_BDADOS - versao_bdados_len;

    NOG *tabela = BD->LTabelas->Inicio;
    while (tabela) {
        TABELA *T = tabela->Info;

        size_t nome_tabela_len = strlen(T->NOME_TABELA) + 1;
        if (nome_tabela_len < MAX_NOME_TABELA) memoria += MAX_NOME_TABELA - nome_tabela_len;

        NOG *campo = T->LCampos->Inicio;
        while (campo) {
            CAMPO *C = campo->Info;

            size_t nome_campo_len = strlen(C->NOME_CAMPO) + 1;
            if (nome_campo_len < MAX_NOME_CAMPO) memoria += MAX_NOME_CAMPO - nome_campo_len;

            size_t tipo_campo_len = strlen(C->TIPO) + 1;
            if (tipo_campo_len < MAX_TIPO) memoria += MAX_TIPO - tipo_campo_len;

            campo = campo->Prox;
        }

        NOG *registo = T->LRegistos->Inicio;
        while (registo) {
            REGISTO *R = registo->Info;

            NOG *registo_atual = R->Inicio, *campo_atual = T->LCampos->Inicio;
            while (registo_atual) {
                char *info = registo_atual->Info;
                CAMPO *C = campo_atual->Info;

                if (strcmp(C->TIPO, "INT") == 0) {
                    size_t info_len = strlen(info) + 1;
                    if (info_len > sizeof(int)) memoria += info_len - sizeof(int);
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

    // Para que o ficheiro seja lido corretamente pelo Excel
    // https://superuser.com/a/420025/1100828
    fprintf(f, DEF_EXCEL_SEPARADOR "\n");

    Escrever_Tabela_Excel(f, T);

    fclose(f);

    return SUCESSO;
}

int Exportar_BDados_Excel(BDadosCoupe *BD, char *ficheiro_csv) {
    if (!BD || !ficheiro_csv) return INSUCESSO;

    FILE *f = fopen(ficheiro_csv, "w");
    if (!f) return INSUCESSO;

    NOG *tabela = BD->LTabelas->Inicio;
    if (!tabela) {
        fclose(f);
        return INSUCESSO;
    }

    // Para que o ficheiro seja lido corretamente pelo Excel
    // https://superuser.com/a/420025/1100828
    fprintf(f, DEF_EXCEL_SEPARADOR "\n");

    while (tabela) {
        TABELA *T = tabela->Info;
        Escrever_Tabela_Excel(f, T);
        tabela = tabela->Prox;
        if (tabela) {  // Se não for o último elemento da lista, inserir o separador
            fprintf(f, SEPARADOR_TABELA "\n");
        }
    }

    fclose(f);
    return SUCESSO;
}

// Função auxiliar utilizada em Exportar_Tabela_BDados_Excel e Exportar_BDados_Excel
void Escrever_Tabela_Excel(FILE *f, TABELA *T) {
    NOG *campo = T->LCampos->Inicio;
    while (campo) {
        CAMPO *C = campo->Info;
        if (campo->Prox) {  // Se não for o último campo, incluir um ';' no fim
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
            if (registo_atual->Prox) {  // Se não for o último registo, incluir um ';' no fim
                fprintf(f, "%s;", registo_atual->Info);
            } else {
                fprintf(f, "%s", registo_atual->Info);
            }
            registo_atual = registo_atual->Prox;
        }

        fprintf(f, "\n");

        registo = registo->Prox;
    }
}

int Importar_BDados_Excel(BDadosCoupe *BD, char *ficheiro_csv) {
    if (!BD || !ficheiro_csv || !BD->LTabelas->NEL) return INSUCESSO;

    FILE *f = fopen(ficheiro_csv, "r");
    if (!f) return INSUCESSO;

    char *linha = (char *) malloc(sizeof(char) * MAX_LINHA), *token, **dados_holder = NULL;
    if (!linha) {
        fclose(f);
        return INSUCESSO;
    }

    NOG *tabela = BD->LTabelas->Inicio;
    TABELA *T = (TABELA *) tabela->Info;
    int n_linha = 0, i, j;
    size_t len;

    while (!feof(f)) {
        fgets(linha, MAX_LINHA, f);

        // Se a linha estiver vazia, ignorar
        if (linha[0] == '\n') continue;

        len = strlen(linha);

        // Remover o \n do fim da linha
        if (len > 0 && linha[len - 1] == '\n') linha[len - 1] = '\0';

        // Ignorar linhas vazias ou a definição do separador para o Excel
        if (len == 1 || strcmp(linha, DEF_EXCEL_SEPARADOR) == 0) continue;

        if (n_linha == 0) {
            n_linha++;
            continue;
        } else if (strcmp(linha, SEPARADOR_TABELA) == 0) {
            n_linha = 0;
            tabela = tabela->Prox;
            if (tabela) T = (TABELA *) tabela->Info;
            continue;
        }

        if (!tabela) break;

        n_linha++;

        token = strtok(linha, ";");
        if (!token) break;

        dados_holder = (char **) malloc(sizeof(char *) * T->LCampos->NEL);
        i = 0;

        while (token) {
            dados_holder[i] = (char *) malloc(sizeof(char) * (strlen(token) + 1));
            strcpy(dados_holder[i], token);

            token = strtok(NULL, ";");
            i++;
        }

        REGISTO *registo = CriarLG();
        if (!registo) {
            for (j = 0; j < i; j++) free(dados_holder[j]);
            free(dados_holder);
            break;
        }

        // Não podemos usar esta função diretamente no loop acima devido à maneira de como o strtok funciona
        for (j = 0; j < i; j++) {
            AddLG(registo, dados_holder[j]);
        }

        AddLG(T->LRegistos, registo);
    }

    free(linha);
    fclose(f);

    return SUCESSO;
}

/**
 * Ordem de escrita:
 *  - número de tabelas
 *  para cada tabela:
 *      - tamanho do nome da tabela
 *      - nome da tabela
 *      - número de campos
 *      para cada campo:
 *          - estrutura inteira do campo
 *      - número de registos
 *      para cada registo:
 *          - número colunas
 *          para cada coluna:
 *              - o tamanho do dado
 *              - o dado
 */
int Exportar_BDados_Ficheiro_Binario(BDadosCoupe *BD, char *ficheiro_dat) {
    if (!BD || !ficheiro_dat) return INSUCESSO;

    FILE *f = fopen(ficheiro_dat, "wb");
    if (!f) return INSUCESSO;

    fwrite(&BD->LTabelas->NEL, sizeof(int), 1, f);

    NOG *tabela = BD->LTabelas->Inicio;
    if (!tabela) {
        fclose(f);
        return INSUCESSO;
    }

    while (tabela) {
        TABELA *T = tabela->Info;

        int nome_tabela_len = strlen(T->NOME_TABELA) + 1;
        fwrite(&nome_tabela_len, sizeof(int), 1, f);
        fwrite(T->NOME_TABELA, sizeof(char), nome_tabela_len, f);

        fwrite(&T->LCampos->NEL, sizeof(int), 1, f);

        NOG *campo = T->LCampos->Inicio;
        while (campo) {
            CAMPO *C = campo->Info;
            fwrite(C, sizeof(CAMPO), 1, f);
            campo = campo->Prox;
        }

        fwrite(&T->LRegistos->NEL, sizeof(int), 1, f);

        NOG *registo = T->LRegistos->Inicio;
        while (registo) {
            REGISTO *R = registo->Info;

            fwrite(&R->NEL, sizeof(int), 1, f);

            NOG *registo_atual = R->Inicio;
            while (registo_atual) {
                int registo_atual_len = strlen(registo_atual->Info) + 1;
                fwrite(&registo_atual_len, sizeof(int), 1, f);
                fwrite(registo_atual->Info, sizeof(char), registo_atual_len, f);

                registo_atual = registo_atual->Prox;
            }

            registo = registo->Prox;
        }

        tabela = tabela->Prox;
    }

    fclose(f);

    return SUCESSO;
}

int Importar_BDados_Ficheiro_Binario(BDadosCoupe *BD, char *ficheiro_dat) {
    if (!BD || !ficheiro_dat) return INSUCESSO;

    FILE *f = fopen(ficheiro_dat, "rb");
    if (!f) return INSUCESSO;

    int n_tabelas;
    fread(&n_tabelas, sizeof(int), 1, f);
    for (int i = 0; i < n_tabelas; i++) {
        int nome_tabela_len;
        fread(&nome_tabela_len, sizeof(int), 1, f);
        char *nome_tabela = (char *) malloc(sizeof(char) * nome_tabela_len);
        fread(nome_tabela, sizeof(char), nome_tabela_len, f);

        TABELA *T = Criar_Tabela(BD, nome_tabela);
        if (!T) {
            free(nome_tabela);
            fclose(f);
            return INSUCESSO;
        }

        int n_campos;
        fread(&n_campos, sizeof(int), 1, f);
        for (int j = 0; j < n_campos; j++) {
            CAMPO C;
            fread(&C, sizeof(CAMPO), 1, f);
            Add_Campo_Tabela(T, C.NOME_CAMPO, C.TIPO);
        }

        int n_registos;
        fread(&n_registos, sizeof(int), 1, f);
        for (int j = 0; j < n_registos; j++) {
            REGISTO *registo = CriarLG();

            int n_registos_1;
            fread(&n_registos_1, sizeof(int), 1, f);
            for (int k = 0; k < n_registos_1; k++) {
                int registo_atual_len;
                fread(&registo_atual_len, sizeof(int), 1, f);

                char *dado = (char *) malloc(sizeof(char) * registo_atual_len);
                if (!dado) {
                    fclose(f);
                    return INSUCESSO;
                }

                fread(dado, sizeof(char), registo_atual_len, f);

                AddLG(registo, dado);
            }

            AddLG(T->LRegistos, registo);
        }
    }

    fclose(f);

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

// M)	Apagar o conteúdo de uma Tabela e remove a tabela da base de dados.
int DROP_TABLE(BDadosCoupe *BD, char *nome_tabela) {
    if (!BD || !nome_tabela) return INSUCESSO;

    TABELA *T = Pesquisar_Tabela(BD, nome_tabela);
    if (!T) return INSUCESSO;

    if (DELETE_TABLE_DATA(T) == INSUCESSO) return INSUCESSO;

    void *data = RemoveLG(BD->LTabelas, T, comparar_tabela);
    if (data) {
        Destruir_Tabela(data);
        return SUCESSO;
    }
    return INSUCESSO;
}

// N)	Selecionar (Apresentar no ecran!) da base de dados todos os registos que obedeçam a uma dada condição,
// a função deve retornar o número de registos selecionados. (Ter em atenção o exemplo das aulas teóricas!). Nota:
// esta é certamente a funcionalidade mais usada num sistema de base de dados, por isso se estiver bem otimizada.
// O utilizador agradece!!!!
int SELECT(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *nome_campo,
           char *valor_comparacao) {
    if (!BD || !_tabela || !f_condicao || !nome_campo || !valor_comparacao) return INSUCESSO;

#ifdef DEBUG_TIMINGS
    clock_t start = clock();
#endif

    TABELA *T = Pesquisar_Tabela(BD, _tabela);
    if (!T) return INSUCESSO;

    int i, contador = 0;
    CAMPO *C = encontrar_indice_campo(T, nome_campo, &i);
    if (!C) return INSUCESSO;

    NOG *registo = T->LRegistos->Inicio;
    while (registo) {
        REGISTO *R = (REGISTO *) registo->Info;

        NOG *registo_atual = R->Inicio;
        for (int j = 0; j <= i; j++) {
            if (j == i) { // Comparar apenas se o campo for o que se pretende comparar
                if (f_condicao((char *) registo_atual->Info, valor_comparacao)) {
                    // Registo foi encontrado, apresentar no ecrã
                    printf("[%s]: ", __FUNCTION__);

                    int k = 0;
                    NOG *reg = R->Inicio;
                    while (reg) {
                        if (k == 0) { // Só incluir barra no início se não for o primeiro campo
                            printf("%s", (char *) reg->Info);
                            k++;
                        } else {
                            printf(" | %s", (char *) reg->Info);
                        }
                        reg = reg->Prox;
                    }

                    printf("\n");
                    contador++;
                }

                break;
            }

            registo_atual = registo_atual->Prox;
        }

        registo = registo->Prox;
    }

#ifdef DEBUG_TIMINGS
    WRITE_TIMING(start, "%s (tabela: %s, campo: %s, valor: %s, qnt: %d): %f\n", _tabela, nome_campo, valor_comparacao,
                 contador);
#endif

    return contador;
}

// O)	Remover todos os registos que obedeçam a uma dada condição, a função deve retornar o número de registos
// removidos.
int DELETE(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *nome_campo,
           char *valor_comparacao) {
    if (!BD || !_tabela || !f_condicao || !nome_campo || !valor_comparacao) return INSUCESSO;

#ifdef DEBUG_TIMINGS
    clock_t start = clock();
#endif

    TABELA *T = Pesquisar_Tabela(BD, _tabela);
    if (!T) return INSUCESSO;

    int i, contador = 0, linha_removida = 0;
    CAMPO *C = encontrar_indice_campo(T, nome_campo, &i);
    if (!C) return INSUCESSO;

    NOG *registo = T->LRegistos->Inicio;
    while (registo) {
        REGISTO *R = (REGISTO *) registo->Info;

        NOG *registo_atual = R->Inicio;
        for (int j = 0; j <= i; j++) {
            if (j == i) { // Se for o campo pretendido, comparar o seu valor
                if (f_condicao((char *) registo_atual->Info, valor_comparacao)) {
                    NOG *prox = registo->Prox;

                    // Remover o registo inteiro da lista de registos
                    void *data = RemoveLG(T->LRegistos, registo->Info, comparar_registos);
                    if (data) {
                        free(data);
                        contador++;
                        registo = prox;
                        linha_removida = 1;
                    }
                }

                break;
            }

            registo_atual = registo_atual->Prox;
        }

        if (linha_removida) { // Para que não tente acessar o próximo registo novamente, pois já foi feito anteriormente
            linha_removida = 0;
            continue;
        }

        registo = registo->Prox;
    }

#ifdef DEBUG_TIMINGS
    WRITE_TIMING(start, "%s (tabela: %s, campo: %s, valor: %s, qnt: %d): %f\n", _tabela, nome_campo, valor_comparacao,
                 contador);
#endif

    return contador;
}

// P)	Atualizar todos os registos da tabela onde o Campo � dado, que obedeçam a uma dada condição, a função
// deve retornar o número de registos que foram atualizados.
int UPDATE(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *campo_comp, char *valor_campo_comp,
           char *nome_campo_update, char *valor_campo_update) {
    if (!BD || !_tabela || !f_condicao || !campo_comp || !valor_campo_comp || !nome_campo_update ||
        !valor_campo_update)
        return INSUCESSO;

#ifdef DEBUG_TIMINGS
    clock_t start = clock();
#endif

    TABELA *T = Pesquisar_Tabela(BD, _tabela);
    if (!T) return INSUCESSO;

    int i_comp, i_update, contador = 0;
    CAMPO *C_comp = encontrar_indice_campo(T, campo_comp, &i_comp),
            *C_update = encontrar_indice_campo(T, nome_campo_update, &i_update);
    if (!C_comp || !C_update) return INSUCESSO;

    size_t campo_update_len = sizeof(char) * (strlen(valor_campo_update) + 1);

    NOG *registo = T->LRegistos->Inicio;
    while (registo) {
        REGISTO *R = (REGISTO *) registo->Info;

        NOG *registo_atual = R->Inicio;
        for (int j = 0; j <= i_comp; j++) {
            if (j == i_comp) { // Se for o campo de comparação
                // E se o valor do campo de comparação for igual ao valor de comparação
                if (f_condicao((char *) registo_atual->Info, valor_campo_comp)) {
                    NOG *registo_atual_update = R->Inicio;
                    for (int k = 0; k <= i_update; k++) {
                        if (k == i_update) { // Se for o campo de update, atualiza o valor
                            // Apenas atualizar o valor se for diferente
                            if (strcmp((char *) registo_atual_update->Info, valor_campo_update) != 0) {
                                free(registo_atual_update->Info);
                                registo_atual_update->Info = (char *) malloc(campo_update_len);
                                strcpy((char *) registo_atual_update->Info, valor_campo_update);
                                contador++;
                            }

                            break;
                        }

                        registo_atual_update = registo_atual_update->Prox;
                    }
                }

                break;
            }

            registo_atual = registo_atual->Prox;
        }

        registo = registo->Prox;
    }

#ifdef DEBUG_TIMINGS
    WRITE_TIMING(start,
                 "%s (tabela: %s, campo comp: %s, valor comp: %s, campo update: %s, valor novo: %s, qnt: %d): %f\n",
                 _tabela,
                 campo_comp,
                 valor_campo_comp,
                 nome_campo_update,
                 valor_campo_update,
                 contador);
#endif

    return contador;
}

// Função auxiliar utilizada na função DROP_TABLE
int comparar_tabela(void *T1, void *T2) {
    if (!T1 || !T2) return 0;
    return strcmp(((TABELA *) T1)->NOME_TABELA, ((TABELA *) T2)->NOME_TABELA) == 0;
}

// Função auxiliar utilizada na função SELECT
CAMPO *encontrar_indice_campo(TABELA *T, char *nome_campo, int *indice) {
    NOG *campo = T->LCampos->Inicio;
    for (*indice = 0; *indice < T->LCampos->NEL; (*indice)++) {
        CAMPO *C = (CAMPO *) campo->Info;
        if (strcmp(C->NOME_CAMPO, nome_campo) == 0) return C;
        campo = campo->Prox;
    }
    return NULL;
}

// Função auxiliar utilizada na função DELETE
int comparar_registos(void *reg1, void *reg2) {
    if (!reg1 || !reg2) return 0;

    REGISTO *R1 = (REGISTO *) reg1, *R2 = (REGISTO *) reg2;
    if (R1->NEL != R2->NEL) return 0;

    NOG *registo_atual = R1->Inicio, *registo_atual2 = R2->Inicio;
    while (registo_atual) {
        if (strcmp((char *) registo_atual->Info, (char *) registo_atual2->Info) != 0) return 0;
        registo_atual = registo_atual->Prox;
        registo_atual2 = registo_atual2->Prox;
    }

    return 1;
}
