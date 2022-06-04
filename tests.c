#include "tests.h"
#include "BDadosCoupe.h"

#define FICHEIRO_BDADOS_EXCEL "C:\\Users\\Utilizador\\OneDrive - ESTGV\\ED\\ed-projeto1-2022\\BDados.csv"
#define FICHEIRO_BDADOS_BIN "C:\\Users\\Utilizador\\OneDrive - ESTGV\\ED\\ed-projeto1-2022\\BDados.csv"
#define FICHEIRO_BDADOS_VEICULOS "C:\\Users\\Utilizador\\OneDrive - ESTGV\\ED\\ed-projeto1-2022\\Vehicle_Data.csv"
#define FICHEIRO_BDADOS_REGIONS "C:\\Users\\Utilizador\\OneDrive - ESTGV\\ED\\ed-projeto1-2022\\Regions.csv"

void test_import_regions_excel() {
    BDadosCoupe *BD = Criar_BDados("BDadosCoupe", "1.0");

    // ID_REGION;NAME_REGION
    char nome_tabela[] = "REGIONS";
    TABELA *T = Criar_Tabela(BD, nome_tabela);
    Add_Campo_Tabela(T, "ID_REGION", "INT");
    Add_Campo_Tabela(T, "NAME_REGION", "STRING");

    Importar_BDados_Excel(BD, FICHEIRO_BDADOS_REGIONS);

    Mostrar_BDados(BD);

    Destruir_BDados(BD);
}

void test_import_vehicle_data_excel() {
    BDadosCoupe *BD = Criar_BDados("BDadosCoupe", "1.0");

    // ID_REGION;TIPO_VEICULO;NUMERO;TIMESTAMP;DATA
    char nome_tabela[] = "VEHICLE_DATA";
    TABELA *T = Criar_Tabela(BD, nome_tabela);
    Add_Campo_Tabela(T, "ID_REGION", "INT");
    Add_Campo_Tabela(T, "TIPO_VEICULO", "STRING");
    Add_Campo_Tabela(T, "NUMERO", "INT");
    Add_Campo_Tabela(T, "TIMESTAMP", "STRING");
    Add_Campo_Tabela(T, "DATA", "STRING");

    Importar_BDados_Excel(BD, FICHEIRO_BDADOS_VEICULOS);

    Mostrar_BDados(BD);

    Destruir_BDados(BD);
}

void test_import_bdados_excel() {
    BDadosCoupe *BD = bdados_base();

    Mostrar_BDados(BD);

    Destruir_BDados(BD);
}

void test_export_bdados_excel() {
    BDadosCoupe *BD = Criar_BDados("BD-Banco", "1.0");

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

    char nome_tabela_2[] = "REGIONS";
    TABELA *T2 = Criar_Tabela(BD, nome_tabela_2);
    Add_Campo_Tabela(T2, "ID", "INT");
    Add_Campo_Tabela(T2, "REGION", "STRING");

    Add_Valores_Tabela(T2, "1;Viseu");
    Add_Valores_Tabela(T2, "2;Biseu");
    Add_Valores_Tabela_BDados(BD, nome_tabela_2, "3;Lisboa");

    Mostrar_BDados(BD);

    Exportar_BDados_Excel(BD, FICHEIRO_BDADOS_EXCEL);

    Destruir_BDados(BD);
}

void test_export_bdados_bin() {
    BDadosCoupe *BD = bdados_base();

    Mostrar_BDados(BD);

    Exportar_BDados_Ficheiro_Binario(BD, FICHEIRO_BDADOS_BIN);

    Destruir_BDados(BD);
}

void test_import_bdados_bin() {
    BDadosCoupe *BD = Criar_BDados("BD-Banco", "1.0");

    Importar_BDados_Ficheiro_Binario(BD, FICHEIRO_BDADOS_BIN);

    Mostrar_BDados(BD);

    Destruir_BDados(BD);
}

void test_memoria_bdados() {
    BDadosCoupe *BD = bdados_base();

    printf("Memoria em uso: %ld\n", Memoria_BDados(BD));
    printf("Memoria desperdicada: %ld\n", Memoria_Desperdicada_BDados(BD));

    Destruir_BDados(BD);
}

void test_select() {
    BDadosCoupe *BD = bdados_base();

    Mostrar_BDados(BD);

    printf("SELECT FROM \"PESSOAS\" WHERE \"ID\" = \"24\" amount: %d\n",
           SELECT(BD, "PESSOAS", f_comparacao, "ID", "24"));
    printf("SELECT FROM \"PESSOAS\" WHERE \"NOME\" = \"Joao\" amount: %d\n",
           SELECT(BD, "PESSOAS", f_comparacao, "NOME", "Joao"));

    Destruir_BDados(BD);
}

void test_select_large() {
    BDadosCoupe *BD = bdados_base_large();

//    Mostrar_BDados(BD);

    printf("SELECT FROM \"VEICULOS\" WHERE \"TIMESTAMP\" = \"\"1592589883\"\" amount: %d\n",
           SELECT(BD, "VEICULOS", f_comparacao, "TIMESTAMP", "\"1592589883\""));
    printf("SELECT FROM \"VEICULOS\" WHERE \"TIPO_VEICULO\" = \"\"cars\"\" amount: %d\n",
           SELECT(BD, "VEICULOS", f_comparacao, "TIPO_VEICULO", "\"cars\""));

    Destruir_BDados(BD);
}

void test_delete() {
    BDadosCoupe *BD = bdados_base();

    Mostrar_BDados(BD);

    printf("DELETE FROM \"PESSOAS\" WHERE \"ID\" = \"24\" amount: %d\n",
           DELETE(BD, "PESSOAS", f_comparacao, "ID", "24"));
    printf("DELETE FROM \"PESSOAS\" WHERE \"NOME\" = \"Joao\" amount: %d\n",
           DELETE(BD, "PESSOAS", f_comparacao, "NOME", "Joao"));

    Mostrar_BDados(BD);

    Destruir_BDados(BD);
}

void test_delete_large() {
    BDadosCoupe *BD = bdados_base_large();
//    Mostrar_BDados(BD);

    printf("DELETE FROM \"VEICULOS\" WHERE \"TIMESTAMP\" = \"1592589883\" amount: %d\n",
           DELETE(BD, "VEICULOS", f_comparacao, "TIMESTAMP", "\"1592589883\""));
    printf("DELETE FROM \"VEICULOS\" WHERE \"TIPO_VEICULO\" = \"\"cars\"\" amount: %d\n",
           DELETE(BD, "VEICULOS", f_comparacao, "TIPO_VEICULO", "\"cars\""));

//    Mostrar_BDados(BD);

    Destruir_BDados(BD);
}

void test_update() {
    BDadosCoupe *BD = bdados_base();

    Mostrar_BDados(BD);

    printf("UPDATE \"PESSOAS\" SET \"NOME\" = \"Joao\" WHERE \"ID\" = \"24\" amount: %d\n",
           UPDATE(BD, "PESSOAS", f_comparacao, "ID", "24", "NOME", "Joao"));
    printf("UPDATE \"PESSOAS\" SET \"NOME\" = \"Bomdia\" WHERE \"NOME\" = \"Joao\" amount: %d\n",
           UPDATE(BD, "PESSOAS", f_comparacao, "NOME", "Joao", "NOME", "Bomdia"));

    Mostrar_BDados(BD);

    Destruir_BDados(BD);
}

void test_update_large() {
    BDadosCoupe *BD = bdados_base_large();
//    Mostrar_BDados(BD);

    printf("UPDATE \"VEICULOS\" SET \"TIPO_VEICULO\" = \"\"cars\"\" WHERE \"TIMESTAMP\" = \"1592589883\" amount: %d\n",
           UPDATE(BD, "VEICULOS", f_comparacao, "TIMESTAMP", "\"1592589883\"", "TIPO_VEICULO", "\"cars\""));
    printf("UPDATE \"VEICULOS\" SET \"TIPO_VEICULO\" = \"\"cars\"\" WHERE \"TIPO_VEICULO\" = \"\"bikes\"\" amount: %d\n",
           UPDATE(BD, "VEICULOS", f_comparacao, "TIPO_VEICULO", "\"cars\"", "TIPO_VEICULO", "\"bikes\""));

//    Mostrar_BDados(BD);

    Destruir_BDados(BD);
}

void test_delete_table_data() {
    BDadosCoupe *BD = bdados_base();

    Mostrar_BDados(BD);

    TABELA *T = Pesquisar_Tabela(BD, "PESSOAS");
    DELETE_TABLE_DATA(T);

    Mostrar_BDados(BD);

    Destruir_BDados(BD);
}

void test_drop_table() {
    BDadosCoupe *BD = bdados_base();

    Mostrar_BDados(BD);

    DROP_TABLE(BD, "PESSOAS");

    Mostrar_BDados(BD);

    Destruir_BDados(BD);
}


BDadosCoupe *bdados_base() {
    BDadosCoupe *BD = Criar_BDados("BDadosCoupe", "1.0");

    // ID;NOME
    TABELA *T = Criar_Tabela(BD, "PESSOAS");
    Add_Campo_Tabela(T, "ID", "INT");
    Add_Campo_Tabela(T, "NOME", "STRING");

    // ID;REGION
    TABELA *T2 = Criar_Tabela(BD, "REGIONS");
    Add_Campo_Tabela(T2, "ID", "INT");
    Add_Campo_Tabela(T2, "REGION", "STRING");

    Importar_BDados_Excel(BD, FICHEIRO_BDADOS_EXCEL);

    return BD;
}

BDadosCoupe *bdados_base_large() {
    BDadosCoupe *BD = Criar_BDados("BDadosCoupe", "1.0");

    // ID_REGION;TIPO_VEICULO;NUMERO;TIMESTAMP;DATA
    TABELA *T = Criar_Tabela(BD, "VEICULOS");
    Add_Campo_Tabela(T, "ID_REGION", "INT");
    Add_Campo_Tabela(T, "TIPO_VEICULO", "STRING");
    Add_Campo_Tabela(T, "NUMERO", "INT");
    Add_Campo_Tabela(T, "TIMESTAMP", "INT");
    Add_Campo_Tabela(T, "DATA", "STRING");

    Importar_BDados_Excel(BD, FICHEIRO_BDADOS_VEICULOS);

    return BD;
}

int f_comparacao(char *a, char *b) {
    return strcmp(a, b) == 0;
}
