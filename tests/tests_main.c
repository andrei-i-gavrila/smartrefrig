//
// Created by Andrei Gavrila on 06.03.2017.
//


#include "utils/tests_vector.c"
#include "domain/tests_product.c"
#include "repository/tests_repository.c"

int main() {
    runModule("Vector", tests_module_vector);
    runModule("Product", tests_module_product);
    runModule("Repository", tests_module_repository);
    return 0;
}