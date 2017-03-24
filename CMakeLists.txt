cmake_minimum_required(VERSION 3.6)
project(intelligentrefrigerator)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES src/domain/product.c src/domain/product.h src/repository/repository.c src/repository/repository.h src/utils/vector.c src/utils/vector.h src/controller/controller.c src/controller/controller.h src/domain/undo.c src/domain/undo.h)

add_executable(intelligentrefrigerator src/main.c ${SOURCE_FILES} src/ui/console.c src/ui/console.h)
add_executable(intelligentrefrigerator_tests ${SOURCE_FILES} tests/tests_main.c tests/framework/testsHelper.c tests/framework/testsHelper.h)