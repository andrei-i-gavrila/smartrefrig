//
// Created by Andrei Gavrila on 07.03.2017.
//

#ifndef TESTS_TESTS_VECTOR
#define TESTS_TESTS_VECTOR

#include "../framework/testsHelper.h"
#include "../../src/utils/vector.h"
#include <assert.h>
#include <stdlib.h>

void test_vector_init() {
    vector *v = vectorNew();
    assert(v->capacity == 0);
    assert(vectorSize(v) == 0);
    vectorDestroy(v, free);
}

void test_vector_resize() {
    vector *v = vectorNew();
    int res = vectorResize(v, 10);
    assert(v->capacity == 10);
    assert(vectorSize(v) == 0);
    assert(res == 1);
    vectorDestroy(v, free);
}

void test_vector_auto_resize() {
    vector *v = vectorNew();
    vectorPushBack(v, NULL);
    assert(v->capacity == 1);
    vectorPushBack(v, NULL);
    assert(v->capacity == 2);
    vectorPushBack(v, NULL);
    assert(v->capacity == 4);
    assert(vectorSize(v) == 3);
    vectorDestroy(v, free);
}

void test_vector_get_push_back() {
    int *p = malloc(sizeof(int));
    *p = 2;
    vector *v = vectorNew();
    vectorPushBack(v, p);
    assert(*p == *(int*)vectorGet(v, 0));
    int *q = malloc(sizeof(int));
    *q = 3;
    vectorPushBack(v, q);
    assert(*q == *(int*) vectorGet(v, 1));
    vectorDestroy(v, free);
}


void test_vector_delete() {
    vector *v = vectorNew();

    int *p = malloc(sizeof(int));
    *p = 2;
    int *q = malloc(sizeof(int));
    *q = 3;
    vectorPushBack(v, p);
    vectorPushBack(v, q);
    vectorPushBack(v, p);
    vectorDelete(v, 2);
    assert(vectorSize(v) == 2);
    assert(vectorGet(v, 2) == NULL);
    assert(*(int*)vectorGet(v, 1) == *q);
    vectorDestroy(v, free);
}


void tests_module_vector() {
    runTest("Vector init", test_vector_init);
    runTest("Vector vectorResize", test_vector_resize);
    runTest("Vector auto vectorResize", test_vector_auto_resize);
    runTest("Vector vectorGet and vectorPushBack", test_vector_get_push_back);
    runTest("Vector vectorDelete", test_vector_delete);
}


#endif