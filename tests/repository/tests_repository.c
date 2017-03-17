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
//    *a = 2;

    int *b = (int*)malloc(sizeof(int));
//    *b = 32;
    Repository *rep = repositoryCreate();

    repositoryAdd(rep, a);
    repositoryAdd(rep, b);

    assert(2 == *(int *) repositoryGet(rep, 0));
    assert(32 == *(int *) repositoryGet(rep, 1));
    assert(vectorSize(rep->products) == 2);

    repositoryUpdate(rep, 1, a);
    assert(2 == *(int *) repositoryGet(rep, 1));

    repositoryUpdate(rep, 1, b);
    repositoryRemove(rep, 0);
    assert(*(int*)repositoryGet(rep, 0) == 32);
//    printf("helooooooooooooooo");
    fflush(stdout);
    repositoryDestroy(rep, free);
}

void tests_module_repository() {
    runTest("Repository tests", test_repository);
}