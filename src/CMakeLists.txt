cmake_minimum_required(VERSION 3.22.1)
add_executable(main main.c
        america.c
        convert.c
        borda.c
        Welfare_Score.c)
add_library(main_lib main.c)
target_include_directories(main_lib PUBLIC .)
project(P1 C)