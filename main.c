#include "tests.h"

int main() {
    test_import_regions_excel();

    test_import_vehicle_data_excel();

    test_import_bdados_excel();

    test_export_bdados_excel();

    test_export_bdados_bin();
    test_import_bdados_bin();

    test_memoria_bdados();

    test_select();
    test_select_large();

    test_delete();
    test_delete_large();

    test_update();
    test_update_large();

    test_delete_table_data();
    test_drop_table();

    return 0;
}
