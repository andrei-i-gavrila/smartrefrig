//
// Created by Andrei Gavrila on 24.03.2017.
//


#include <assert.h>
#include <string.h>
#include "../../src/repository/repository.h"
#include "../../src/controller/controller.h"
#include "../framework/testsHelper.h"

void test_controller_add() {
    Repository *rep = repositoryCreate(productDestroy, productClone);

    Controller *c = controllerCreate(rep);

    controllerAddProduct(c, "hello", FRUIT, 200, "2001-12-12");

    assert(vectorSize(repositoryAll(c->rep)) == 1);
    assert(vectorSize(c->undoStack) == 1);
    assert(strcmp("hello", productGetName(repositoryGet(c->rep, 0))) == 0);

    controllerDestroy(c);
    repositoryDestroy(rep);
}

void test_controller_update() {
    Repository *rep = repositoryCreate(productDestroy, productClone);
    Controller *c = controllerCreate(rep);
    controllerAddProduct(c, "hello", FRUIT, 200, "2001-12-12");

    assert(vectorSize(c->undoStack) == 1);
    Product *prev = repositoryGet(c->rep, 0);

    controllerUpdateProduct(c, "hello", FRUIT, 2, "2000-02-02");
    assert(vectorSize(c->undoStack) == 2);

    assert(productGetQuantity(repositoryGet(rep, 0)) == 2);

    assert(prev != repositoryGet(c->rep, 0));

    controllerDestroy(c);
    repositoryDestroy(rep);
}

void test_controller_filter_sort() {
    Repository *rep = repositoryCreate(productDestroy, productClone);
    Controller *c = controllerCreate(rep);
    controllerAddProduct(c, "hello", FRUIT, 200, "2001-12-12");
    controllerAddProduct(c, "hehe", FRUIT, 2, "2001-12-12");
    controllerAddProduct(c, "maca", FRUIT, 200, "2001-12-12");

    char *name = "he";
    void *filters[] = {name};
    vector *fil = controllerGetProducts(c, productNameContains, filters, productSortQuantityAsc);

    assert(vectorSize(fil) == 2);
    assert(strcmp(productGetName(vectorGet(fil, 0)), "hehe") == 0);
    assert(productGetQuantity(vectorGet(fil, 0)) < productGetQuantity(vectorGet(fil, 1)));

    controllerDestroy(c);
    repositoryDestroy(rep);
    vectorDestroy(fil);
}

void test_controller_undo_redo() {
    Repository *rep = repositoryCreate(productDestroy, productClone);
    Controller *c = controllerCreate(rep);
    controllerAddProduct(c, "hello", FRUIT, 200, "2001-12-12");
    controllerAddProduct(c, "hehe", FRUIT, 2, "2001-12-12");
    controllerAddProduct(c, "maca", FRUIT, 200, "2001-12-12");

    assert(controllerUndo(c) == 1);
    assert(vectorSize(controllerGetAllProducts(c)) == 2);
    assert(vectorSize(c->redoStack) == 1);

    controllerAddProduct(c, "asd", FRUIT, 2, "2001-12-12");
    assert(vectorSize(c->redoStack) == 0);

    controllerUndo(c);
    controllerRedo(c);
    assert(vectorSize(controllerGetAllProducts(c)) == 3);
    assert(controllerRedo(c) == 0);

    controllerUndo(c);
    controllerUndo(c);
    assert(controllerUndo(c) == 1);
    assert(controllerUndo(c) == 0);



    controllerDestroy(c);
    repositoryDestroy(rep);
};


void tests_module_controller() {
    runTest("Controller add", test_controller_add);
    runTest("Controller update", test_controller_update);
    runTest("Controller filter sort", test_controller_filter_sort);
    runTest("Controller undo redo", test_controller_undo_redo);
}
