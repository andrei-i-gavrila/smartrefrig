//
// Created by Andrei Gavrila on 12.03.2017.
//

#include <stddef.h>
#include <stdlib.h>
#include "controller.h"
#include <string.h>

void controllerAddProduct(Controller *ctrl, char *name, category_type type, int quantity,
                          char *date) {
    void *searchAttributes[] = {name, &type};
    int productId = repositoryFind(ctrl->rep, productSearch, searchAttributes);
    Product *p;
    if (productId == -1) {
        p = productNew(name, type, quantity, date);
        repositoryAdd(ctrl->rep, p);
        return;
    }

    p = repositoryGet(ctrl->rep, productId);
    productSetQuantity(p, productGetQuantity(p) + quantity);
    repositoryUpdate(ctrl->rep, productId, p);
}

void controllerDeleteProduct(Controller *ctrl, char *name, category_type type) {
    void *searchAttributes[] = {name, &type};
    int productId = repositoryFind(ctrl->rep, productSearch, searchAttributes);
    if (productId != -1) {
        Product *p = repositoryGet(ctrl->rep, productId);
        repositoryRemove(ctrl->rep, productId);
        productDestroy(p);
    }
}

void controllerUpdateProduct(Controller *ctrl, char *name, category_type type, int newQuantity, char *newDate) {
    void *searchAttributes[] = {name, &type};
    int productId = repositoryFind(ctrl->rep, productSearch, searchAttributes);
    if (productId != -1) {
        Product *p = repositoryGet(ctrl->rep, productId);
        productSetQuantity(p, newQuantity);
        productSetDate(p, newDate);
        repositoryUpdate(ctrl->rep, productId, p);
    }
}

vector *controllerGetAllProducts(Controller *ctrl) {
    return repositoryAll(ctrl->rep);
}

Controller *controllerCreate(Repository *rep) {
    Controller *ctrl = malloc(sizeof(Controller));
    ctrl->rep = rep;
    return ctrl;
}

void controllerDestroy(Controller *ctrl) {
    free(ctrl);
}

vector *controllerGetProducts(Controller *ctrl, char *query) {

    void *filters[] = {query};
    vector *ret;
    if (strcmp(query, "\n") == 0) {
        ret = repositoryAll(ctrl->rep);
    } else {
        ret = vectorFilter(repositoryAll(ctrl->rep), productNameContains, filters);
    }

    vectorSort(ret, productSortQuantity);

    return ret;
}

vector *controllerGetProductsFiltered(Controller *ctrl, int (*filter)(void *, void **), void **filters) {
    return vectorFilter(controllerGetAllProducts(ctrl), filter, filters);
}