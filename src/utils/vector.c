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
    if (v->destructor != NULL) {
        v->destructor(vectorGet(v, i));
    }

    for (; i < (v->n) - 1; i++) {
        v->elements[i] = v->elements[i + 1];
    }
    v->elements[--v->n] = NULL;
    return 1;
}

vector *vectorNew(void (*destructor)(void *), void *(*cloner)(void *)) {
    vector *v = (vector *) malloc(sizeof(vector));
    if (v == NULL) {
        return NULL;
    }
    v->n = 0;
    v->capacity = 0;
    v->elements = NULL;
    v->destructor = destructor;
    v->cloner = cloner;
    return v;
}

void vectorDestroy(vector *v) {
    for (int i = 0; i < v->capacity; i++) {
        if (v->elements[i] != NULL && v->destructor != NULL) {
            v->destructor(v->elements[i]);
        }
    }
    free(v->elements);
    free(v);
}

vector *vectorFilter(vector *v, int (*comparator)(void *, void **), void **filters) {
    vector *result = vectorNew(v->destructor, v->cloner);

    for (int i = 0; i < vectorSize(v); i++) {
        if (comparator(vectorGet(v, i), filters)) {
            vectorPushBack(result, v->cloner == NULL ? vectorGet(v, i) : v->cloner(vectorGet(v, i)));
        }
    }

    return result;
}

void vectorSort(vector *v, __compar_fn_t comparator) {
    qsort(v->elements, (size_t) vectorSize(v), sizeof(void *), comparator);
}

vector *vectorClone(vector *v) {

    if (v == NULL) {
        return NULL;
    }

    vector *new = vectorNew(v->destructor, v->cloner);

    for (int i = 0; i < vectorSize(v); i++) {
        vectorPushBack(new, v->cloner == NULL ? vectorGet(v, i) : v->cloner(vectorGet(v, i)));
    }

    return new;
}

void *vectorPop(vector *v) {
    if (vectorSize(v) == 0) {
        return NULL;
    }

    void *top = vectorGet(v, vectorSize(v) - 1);

    vectorSet(v, v->n-1, NULL);
    v->n--;
    return top;
}

void vectorClear(vector *v) {
    for (int i = vectorSize(v) - 1; i >= 0; i--) {
        vectorDelete(v, i);
    }
}
