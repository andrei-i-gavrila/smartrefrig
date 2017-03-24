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
    vector *v = vectorNew(free, NULL);
    assert(v->destructor == free);
    assert(v->cloner == NULL);
    assert(v->capacity == 0);
    assert(vectorSize(v) == 0);
    vectorDestroy(v);
}

void test_vector_resize() {
    vector *v = vectorNew(NULL, NULL);
    int res = vectorResize(v, 10);
    assert(v->capacity == 10);
    assert(vectorSize(v) == 0);
    assert(res == 1);
    vectorDestroy(v);
}

void test_vector_auto_resize() {
    vector *v = vectorNew(NULL, NULL);
    vectorPushBack(v, NULL);
    assert(v->capacity == 1);
    vectorPushBack(v, NULL);
    assert(v->capacity == 2);
    vectorPushBack(v, NULL);
    assert(v->capacity == 4);
    assert(vectorSize(v) == 3);
    vectorDestroy(v);
}

void test_vector_get_push_back() {
    int *p = malloc(sizeof(int));
    *p = 2;
    vector *v = vectorNew(free, NULL);
    vectorPushBack(v, p);
    assert(*p == *(int *) vectorGet(v, 0));
    int *q = malloc(sizeof(int));
    *q = 3;
    vectorPushBack(v, q);
    assert(*q == *(int *) vectorGet(v, 1));
    vectorDestroy(v);
}


void test_vector_delete() {
    vector *v = vectorNew(free, NULL);

    int *p = malloc(sizeof(int));
    *p = 2;
    int *q = malloc(sizeof(int));
    *q = 3;
    int *r = malloc(sizeof(int));
    *r = 4;
    vectorPushBack(v, p);
    vectorPushBack(v, q);
    vectorPushBack(v, r);
    vectorDelete(v, 1);
    assert(vectorSize(v) == 2);
    assert(vectorGet(v, 2) == NULL);
    assert(*(int *) vectorGet(v, 1) == *r);
    vectorDestroy(v);
}

void test_vector_pop() {
    vector *v = vectorNew(free, NULL);
    int *p = malloc(sizeof(int));
    int *q = malloc(sizeof(int));
    int *r = malloc(sizeof(int));

    *p = 1;
    *q = 2;
    *r = 3;

    vectorPushBack(v, p);
    vectorPushBack(v, q);
    vectorPushBack(v, r);
    assert(vectorSize(v) == 3);

    int *popped = vectorPop(v);

    assert(*popped == *r);
    assert(vectorSize(v) == 2);
    vectorPop(v);
    vectorPop(v);
    assert(vectorPop(v) == NULL);
    free(p);
    free(q);
    free(r);
    vectorDestroy(v);
}


int test_vector_filter_function(void *p, void **filters) {
    return *(int *) p & 1;
}

void *test_vector_cloner(void *i) {
    int *cloned = malloc(sizeof(int));
    *cloned = *(int *) i;
    return cloned;
}

void test_vector_filter() {
    vector *v = vectorNew(free, test_vector_cloner);
    int *p = malloc(sizeof(int));
    int *q = malloc(sizeof(int));
    int *r = malloc(sizeof(int));

    *p = 1;
    *q = 2;
    *r = 3;

    vectorPushBack(v, p);
    vectorPushBack(v, q);
    vectorPushBack(v, r);

    vector *filtered = vectorFilter(v, test_vector_filter_function, NULL);

    assert(vectorSize(v) == 3);
    assert(vectorSize(filtered) == 2);
    assert(vectorGet(filtered, 0) != p);
    assert(*(int *) vectorGet(filtered, 0) == *p);

    vectorDestroy(v);
    vectorDestroy(filtered);
}

int test_vector_sorter(const void *a, const void *b) {
    return (**(int **) b) - (**(int **) a);
}

void test_vector_sort() {
    vector *v = vectorNew(free, NULL);
    int *p = malloc(sizeof(int));
    int *q = malloc(sizeof(int));
    int *r = malloc(sizeof(int));

    *p = 1;
    *q = 2;
    *r = 3;

    vectorPushBack(v, p);
    vectorPushBack(v, q);
    vectorPushBack(v, r);

    vectorSort(v, test_vector_sorter);

    for (int i = 0; i < vectorSize(v) - 1; i++) {
        assert(*(int *) vectorGet(v, i) > *(int *) vectorGet(v, i + 1));
    }
    vectorDestroy(v);
}

void test_vector_clone() {
    vector *v = vectorNew(free, test_vector_cloner);
    int *p = malloc(sizeof(int));
    int *q = malloc(sizeof(int));
    int *r = malloc(sizeof(int));

    *p = 1;
    *q = 2;
    *r = 3;

    vectorPushBack(v, p);
    vectorPushBack(v, q);
    vectorPushBack(v, r);

    vector *cloned = vectorClone(v);

    assert(cloned != v);
    assert(vectorSize(v) == vectorSize(cloned));
    for (int i = 0; i < vectorSize(v); i++) {
        assert(vectorGet(v, i) != vectorGet(cloned, i));
        assert(*(int*)vectorGet(v, i) == *(int*)vectorGet(cloned, i));
    }

    vectorDestroy(v);
    vectorDestroy(cloned);
}

void test_vector_clear() {
    vector *v = vectorNew(free, test_vector_cloner);
    int *p = malloc(sizeof(int));
    int *q = malloc(sizeof(int));
    int *r = malloc(sizeof(int));

    *p = 1;
    *q = 2;
    *r = 3;

    vectorPushBack(v, p);
    vectorPushBack(v, q);
    vectorPushBack(v, r);

    vectorClear(v);
    assert(vectorSize(v) == 0);
    vectorDestroy(v);
}

void tests_module_vector() {
    runTest("Vector init", test_vector_init);
    runTest("Vector vectorResize", test_vector_resize);
    runTest("Vector auto vectorResize", test_vector_auto_resize);
    runTest("Vector vectorGet and vectorPushBack", test_vector_get_push_back);
    runTest("Vector vectorDelete", test_vector_delete);
    runTest("Vector pop", test_vector_pop);
    runTest("Vector filter", test_vector_filter);
    runTest("Vector sort", test_vector_sort);
    runTest("Vector clone", test_vector_clone);
    runTest("Vector clear", test_vector_clear);

}


#endif