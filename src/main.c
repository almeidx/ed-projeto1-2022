#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "BDadosCoupe.h"
#include "tests.h"

int condicao(char *, char *);

int main() {
    // printf("Template do projecto BDadosCoupe para os alunos!\n");

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

//    test_export_bdados_bin();
    // test_import_bdados_bin();

    //    test_memoria_bdados();

    //     FILE *f = fopen("C:\\Users\\Utilizador\\OneDrive - ESTGV\\ED\\ed-projeto1-2022\\src\\BDados.dat", "rb");
    //     int a;
    //     fread(&a, sizeof(int), 1, f);
    //
    //     int b;
    //     fread(&b, sizeof(int), 1, f);
    //     char *z = (char *)malloc(sizeof(char) * 100);
    //     fread(z, sizeof(char), b, f);
    //
    //     int c;
    //     fread(&c, sizeof(int), 1, f);
    //
    //     int d;
    //     fread(&d, sizeof(int), 1, f);
    //     char *y = (char *)malloc(sizeof(char) * 100);
    //     fread(y, sizeof(char), d, f);
    //
    //     int e;
    //     fread(&e, sizeof(int), 1, f);
    //     char *w = (char *)malloc(sizeof(char) * 100);
    //     fread(w, sizeof(char), e, f);
    //
    //     int g;
    //     fread(&g, sizeof(int), 1, f);
    //     char *u = (char *)malloc(sizeof(char) * 100);
    //     fread(u, sizeof(char), g, f);
    //
    //     int h;
    //     fread(&h, sizeof(int), 1, f);
    //     char *v = (char *)malloc(sizeof(char) * 100);
    //     fread(v, sizeof(char), h, f);
    //
    //     int i;
    //     fread(&i, sizeof(int), 1, f);

    return 0;
}

int condicao(char *nome1, char *nome2) {
    return strcmp(nome1, nome2) == 0;
}
