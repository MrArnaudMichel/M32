cmake_minimum_required(VERSION 3.27)
project(M32 C)

set(CMAKE_C_STANDARD 11)

add_executable(M32 code/main.c
        code/structs.h
        code/algo.h
        code/algo.c)
