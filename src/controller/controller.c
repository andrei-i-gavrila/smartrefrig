//
// Created by Andrei Gavrila on 12.03.2017.
//

#include <stddef.h>
#include <stdlib.h>
#include "controller.h"
#include <string.h>

Controller *controllerCreate(Repository *rep) {
    Controller *ctrl = malloc(sizeof(Controller));
    ctrl->rep = rep;
    return ctrl;
}

void controllerDestroy(Controller *ctrl) {
    free(ctrl);
}

int controllerAddProduct(Controller *ctrl, char *name, category_type type, int quantity,
                         char *date) {
    void *searchAttributes[] = {name, &type};

    Product *p;
    int productId = repositoryFind(ctrl->rep, productSearch, searchAttributes);

    if (productId > -1) {
        p = repositoryGet(ctrl->rep, productId);

        productSetQuantity(p, productGetQuantity(p) + quantity);
        repositoryUpdate(ctrl->rep, productId, p);

        return 0;
    }

    p = productNew(name, type, quantity, date);
    repositoryAdd(ctrl->rep, p);

    return 1;
}

int controllerDeleteProduct(Controller *ctrl, char *name, category_type type) {
    void *searchAttributes[] = {name, &type};
    int productId = repositoryFind(ctrl->rep, productSearch, searchAttributes);
    if (productId == -1) {
        return 0;
    }

    Product *p = repositoryGet(ctrl->rep, productId);
    repositoryRemove(ctrl->rep, productId);
    productDestroy(p);

    return 1;
}

int controllerUpdateProduct(Controller *ctrl, char *name, category_type type, int newQuantity, char *newDate) {
    void *searchAttributes[] = {name, &type};
    int productId = repositoryFind(ctrl->rep, productSearch, searchAttributes);
    if (productId == -1) {
        return 0;
    }
    Product *p = repositoryGet(ctrl->rep, productId);
    productSetQuantity(p, newQuantity);
    productSetDate(p, newDate);
    repositoryUpdate(ctrl->rep, productId, p);

    return 1;

}

vector *controllerGetAllProducts(Controller *ctrl) {
    return repositoryAll(ctrl->rep);
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