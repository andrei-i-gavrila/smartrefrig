//
// Created by Andrei Gavrila on 06.03.2017.
//

#include "vector.h"
#include <stdlib.h>

void resize(vector *v) {
    unsigned oldSize = v->max_size*sizeof(Product*);
    v = realloc(v, 2*oldSize);
    v->max_size = 2*oldSize;
}

void push_back(vector *v, Product *p) {
    v->elements[v->n] = p;
    v->n++;

    if (v->n == v->max_size) {
        resize(v);
    }
}

Product *get(vector *v, int i) {
    return v->elements[i];
}

void set(vector *v, int i, Product *p) {
    v->elements[i] = p;
}

int size(vector *v) {
    return v->n;
}
