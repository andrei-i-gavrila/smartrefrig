cmake_minimum_required(VERSION 3.6)
project(intelligentrefrigerator)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES src/main.c src/domain/product.c src/domain/product.h src/repository/repository.c src/repository/repository.h src/domain/vector.c src/domain/vector.h)
add_executable(intelligentrefrigerator ${SOURCE_FILES} src/domain/product.h src/domain/product.c src/domain/product.h src/repository/repository.c src/repository/repository.h src/domain/vector.c src/domain/vector.h)