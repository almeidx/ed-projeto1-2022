#ifndef TESTS_H_INCLUDED
#define TESTS_H_INCLUDED

#include "BDadosCoupe.h"

void test_import_regions_excel();

void test_import_vehicle_data_excel();

void test_import_bdados_excel();

void test_export_bdados_excel();

void test_export_bdados_bin();

void test_import_bdados_bin();

void test_memoria_bdados();

void test_select();

void test_select_large();

void test_delete();

void test_delete_large();

void test_update();

void test_update_large();

BDadosCoupe *bdados_base();

BDadosCoupe *bdados_base_large();

int f_comparacao(char *a, char *b);

#endif //TESTS_H_INCLUDED
