//
// Created by Andrei Gavrila on 06.03.2017.
//

#include <string.h>
#include "repository.h"

int find(Repository *rep, char *name, category_type category) {
    for (int i = 0; i < size(rep->products); i++) {
        if (rep->products->elements[i]->category == category) {
            if (strcmp(name, rep->products->elements[i]->name) == 0) {
                return i;
            }
        }
    }
    return -1;
}

void add(Repository *rep, Product *p) {
    push_back(rep->products, p);
}

void remove(Repository *rep, int i) {
    delete(rep->products, i);
}

void update(Repository *rep, int i, Product *p) {
    set(rep->products, i, p);
}
