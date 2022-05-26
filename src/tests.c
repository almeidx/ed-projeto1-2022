#include "BDadosCoupe.c"

void test_import_regions_excel() {
  BDadosCoupe *BD = Criar_BDados("BDadosCoupe", "1.0");

  // ID_REGION;NAME_REGION
  char nome_tabela[] = "REGIONS";
  TABELA *T = Criar_Tabela(BD, nome_tabela);
  Add_Campo_Tabela(T, "ID_REGION", "INT");
  Add_Campo_Tabela(T, "NAME_REGION", "STRING");

  Importar_BDados_Excel(BD, "Regions.csv");

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

  Importar_BDados_Excel(BD, "Vehicle_Data.csv");

  Mostrar_BDados(BD);

  Destruir_BDados(BD);
}

void test_import_bdados_excel() {
  BDadosCoupe *BD = Criar_BDados("BDadosCoupe", "1.0");

  // ID;NOME
  char nome_tabela[] = "PESSOAS";
  TABELA *T = Criar_Tabela(BD, nome_tabela);
  Add_Campo_Tabela(T, "ID", "INT");
  Add_Campo_Tabela(T, "NOME", "STRING");

  // ID;REGION
  char nome_tabela2[] = "REGIONS";
  TABELA *T2 = Criar_Tabela(BD, nome_tabela2);
  Add_Campo_Tabela(T2, "ID", "INT");
  Add_Campo_Tabela(T2, "REGION", "STRING");

  Importar_BDados_Excel(BD, "BDados.csv");

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

  Exportar_BDados_Excel(BD, "BDados.csv");

  Destruir_BDados(BD);
}
