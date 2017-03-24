//
// Created by Andrei Gavrila on 13.03.2017.
//

#include <assert.h>
#include <stdlib.h>
#include "../../src/repository/repository.h"
#include "../framework/testsHelper.h"

void test_repository() {


//    int *a = NULL;
    int *a = (int*)malloc(sizeof(int));
    *a = 2;

    int *b = (int*)malloc(sizeof(int));
    *b = 32;
    Repository *rep = repositoryCreate(free, NULL);

    repositoryAdd(rep, a);
    repositoryAdd(rep, b);

    assert(2 == *(int *) repositoryGet(rep, 0));
    assert(32 == *(int *) repositoryGet(rep, 1));
    assert(vectorSize(rep->products) == 2);

    repositoryRemove(rep, 0);
    assert(*(int*)repositoryGet(rep, 0) == 32);
    fflush(stdout);
    repositoryDestroy(rep);
}

void tests_module_repository() {
    runTest("Repository tests", test_repository);
}