//
// Created by Andrei Gavrila on 06.03.2017.
//

#ifndef INTELLIGENTREFRIGERATOR_REPOSITORY_H
#define INTELLIGENTREFRIGERATOR_REPOSITORY_H


#include "vector.h"
#include "domain.h"

typedef struct {
    vector *products;

} Repository;

int find(Repository *rep, char name[20], category_type category);

void add(Repository *rep, Product *p);

void delete(Repository *rep, int i);

void update(Repository *rep, int i, Product *p);

#endif //INTELLIGENTREFRIGERATOR_REPOSITORY_H
