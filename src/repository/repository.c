//
// Created by Andrei Gavrila on 06.03.2017.
//

#include <wchar.h>
#include <stdlib.h>
#include "repository.h"

vector *repositoryAll(Repository *rep) {
    return rep->products;
}

void *repositoryGet(Repository *rep, int id) {
    return vectorGet(rep->products, id);
}

void repositoryAdd(Repository *rep, void *p) {
    vectorPushBack(rep->products, p);
}

void repositoryRemove(Repository *rep, int i) {
    vectorDelete(rep->products, i);
}

void repositoryUpdate(Repository *rep, int i, void *p) {
    vectorSet(rep->products, i, p);
}

int repositoryFind(Repository *rep, int (*searchFunction)(void *, void **), void **searchAttributes) {

    for (int i = 0; i < rep->products->n; i++) {
        if (searchFunction(vectorGet(rep->products, i), searchAttributes)) {
            return i;
        }
    }

    return -1;
}

Repository *repositoryCreate() {
    Repository *rep = malloc(sizeof(Repository));
    rep->products =  vectorNew();

    return rep;
}

void repositoryDestroy(Repository *rep, void (*dataDestructor)(void *)) {
    vectorDestroy(rep->products, dataDestructor);
    free(rep);
}
