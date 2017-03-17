//
// Created by Andrei Gavrila on 14.03.2017.
//

#include <assert.h>
#include "../framework/testsHelper.h"
#include "../../src/domain/product.h"
#include <string.h>

void test_product() {
    Product *p = productNew("Feta", DAIRY, 20, "2017-03-10");

    assert(strcmp("Feta", productGetName(p)) == 0);
    assert(strncmp("2017-03-10", productGetDate(p), 10) == 0);
    assert(20 == productGetQuantity(p));
    assert(productGetCategory(p) == DAIRY);

    productSetName(p, "haha");
    productSetDate(p, "1234=12=12");
    productSetQuantity(p, 11);
    productSetCategory(p, MEAT);

    assert(strcmp("haha", productGetName(p)) == 0);
    assert(strncmp("1234=12=12", productGetDate(p), 10) == 0);
    assert(11 == productGetQuantity(p));
    assert(productGetCategory(p) == MEAT);

    productDestroy(p);
}


void tests_module_product() {
    runTest("Test product create", test_product);
}