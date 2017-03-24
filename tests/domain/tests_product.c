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
    char date[11];
    productGetDate(p, date);
    assert(strcmp("2017-03-10", date) == 0);
    assert(20 == productGetQuantity(p));
    assert(productGetCategory(p) == DAIRY);

    productSetDate(p, "2000=12=12");
    productSetName(p, "haha");
    productSetQuantity(p, 11);
    productSetCategory(p, MEAT);

    assert(strcmp("haha", productGetName(p)) == 0);
    productGetDate(p, date);
    assert(strcmp("2000=12=12", date) != 0);
    assert(11 == productGetQuantity(p));
    assert(productGetCategory(p) == MEAT);

    productDestroy(p);
}


void tests_module_product() {
    runTest("Test product create", test_product);
}