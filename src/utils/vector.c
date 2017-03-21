//
// Created by Andrei Gavrila on 06.03.2017.
//

#include "vector.h"
#include <stdlib.h>
#include <memory.h>


int vectorResize(vector *v, unsigned newSize) {
    if (v == NULL) {
        return 0;
    }

    void **newElements = realloc(v->elements, newSize * sizeof(void *));
    if (newSize > v->capacity) {
//        memset(newElements + v->capacity, 0, (newSize - v->capacity + 1) * sizeof(void *));
        for (int i = v->capacity; i < newSize; i++) {
            newElements[i] = NULL;
        }
    }
    if (newElements == NULL) {
        return 0;
    }

    v->elements = newElements;


    if (newSize < v->capacity) {
        v->n = newSize;
    }
    v->capacity = newSize;
    return 1;
}

int vectorPushBack(vector *v, void *p) {
    if (v == NULL) {
        return 0;
    }

    if (v->n == v->capacity) {
        if (vectorResize(v, v->capacity ? 2 * v->capacity : 1) == 0) {
            return 0;
        }
    }

    v->elements[v->n] = p;
    v->n++;
    return 1;
}

void *vectorGet(vector *v, int i) {
    if (i >= v->n || i < 0) {
        return NULL;
    }
    return v->elements[i];
}

int vectorSet(vector *v, int i, void *p) {
    if (v == NULL) {
        return 0;
    }

    if (i >= v->n || i < 0) {
        return 0;
    }

    v->elements[i] = p;
    return 1;
}

int vectorSize(vector *v) {
    if (v == NULL) {
        return -1;
    }

    return v->n;
}

int vectorDelete(vector *v, int i) {
    if (v == NULL) {
        return 0;
    }

    if (i >= v->n || i < 0) {
        return 0;
    }
    void *aux = v->elements[i];
    for (; i < (v->n) - 1; i++) {
        v->elements[i] = v->elements[i + 1];
    }
    v->elements[--v->n] = aux;
    return 1;
}

vector *vectorNew() {
    vector *v = (vector *) malloc(sizeof(vector));
    if (v == NULL) {
        return NULL;
    }
    v->n = 0;
    v->capacity = 0;
    v->elements = NULL;
    return v;
}

void vectorDestroy(vector *v, void (*dataDestructor)(void *)) {
    for (int i = 0; i < v->capacity; i++) {
        if (v->elements[i] != NULL) {
            dataDestructor(v->elements[i]);
        }
    }
    free(v->elements);
    free(v);
}

vector *vectorFilter(vector *v, int (*comparator)(void *, void **), void **filters) {
    vector *result = vectorNew();

    for (int i = 0; i < vectorSize(v); i++) {
        if (comparator(vectorGet(v, i), filters)) {
            vectorPushBack(result, vectorGet(v, i));
        }
    }

    return result;
}

void vectorSort(vector *v, int (*comparator)(void *, void *)) {
    qsort(v->elements, vectorSize(v), sizeof(void *), comparator);
}
