cmake_minimum_required(VERSION 3.22.1)
add_executable(main main.c
        valgsystemer/america.c
        logiske-funktioner/convert.c
        valgsystemer/borda.c
        logiske-funktioner/welfare_score.c
        logiske-funktioner/calculate_winner.c
        h-filer/welfare_score.h)
add_library(main_lib main.c)
target_include_directories(main_lib PUBLIC .)
project(P1 C)