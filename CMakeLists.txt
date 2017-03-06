cmake_minimum_required(VERSION 3.6)
project(intelligentrefrigerator)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c domain.c domain.h repository.c repository.h vector.c vector.h)
add_executable(intelligentrefrigerator ${SOURCE_FILES} domain.h domain.c domain.h repository.c repository.h vector.c vector.h)