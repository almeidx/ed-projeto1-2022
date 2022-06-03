cmake_minimum_required(VERSION 3.22)
project(ed_projeto1_2022 C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(ed_projeto1_2022
        src/BDadosCoupe.c
        src/ListaGenerica.c
        src/main.c
        src/tests.c src/tests.h)
