//
// Created by Andrei Gavrila on 12.03.2017.
//

#include <stddef.h>
#include <stdlib.h>
#include "controller.h"
#include "../domain/undo.h"

Controller *controllerCreate(Repository *rep) {
    Controller *ctrl = malloc(sizeof(Controller));
    ctrl->rep = rep;
    ctrl->undoStack = vectorNew(operationDestroy, NULL);
    ctrl->redoStack = vectorNew(operationDestroy, NULL);

    return ctrl;
}

void controllerDestroy(Controller *ctrl) {
    vectorDestroy(ctrl->redoStack);
    vectorDestroy(ctrl->undoStack);
    free(ctrl);
}

void controllerUpdateProductOperation(Controller *ctrl, Product *p) {
    void *searchAttributes[] = {p->name, &p->category};
    int pid = repositoryFind(ctrl->rep, productSearch, searchAttributes);
    repositoryUpdate(ctrl->rep, pid, p);
}

void controllerAddProductOperation(Controller *ctrl, Product *p) {
    repositoryAdd(ctrl->rep, p);
}

void controllerDeleteProductOperation(Controller *ctrl, Product *p) {
    void *searchAttributes[] = {p->name, &p->category};
    int pid = repositoryFind(ctrl->rep, productSearch, searchAttributes);
    if (repositoryGet(ctrl->rep, pid) == p) {
        repositoryRemove(ctrl->rep, pid);
    } else {
        productDestroy(p);
        repositoryRemove(ctrl->rep, pid);
    }
}

int controllerAddProduct(Controller *ctrl, char *name, category_type type,
                         int quantity, char *date) {
    void *searchAttributes[] = {name, &type};

    int productId = repositoryFind(ctrl->rep, productSearch, searchAttributes);


    if (productId > -1) {
        controllerUpdateProduct(ctrl, name, type, quantity + productGetQuantity(repositoryGet(ctrl->rep, productId)),
                                date);
        return 0;
    }

    Product *p = productNew(name, type, quantity, date);
    Operation *o = operationNew(controllerAddProductOperation, controllerDeleteProductOperation, ctrl, p, p);
    vectorPushBack(ctrl->undoStack, o);
    controllerAddProductOperation(ctrl, p);
    vectorClear(ctrl->redoStack);
    return 1;
}


int controllerDeleteProduct(Controller *ctrl, char *name, category_type type) {
    void *searchAttributes[] = {name, &type};
    int productId = repositoryFind(ctrl->rep, productSearch, searchAttributes);
    if (productId == -1) {
        return 0;
    }

    Product *p = repositoryGet(ctrl->rep, productId);
    Operation *o = operationNew(controllerDeleteProductOperation, controllerAddProductOperation, ctrl, p, p);
    vectorPushBack(ctrl->undoStack, o);
    controllerDeleteProductOperation(ctrl, p);
    vectorClear(ctrl->redoStack);
    return 1;
}

int controllerUpdateProduct(Controller *ctrl, char *name, category_type type, int newQuantity, char *newDate) {
    void *searchAttributes[] = {name, &type};
    int productId = repositoryFind(ctrl->rep, productSearch, searchAttributes);
    if (productId == -1) {
        return 0;
    }

    Product *p = productClone(repositoryGet(ctrl->rep, productId));
    Product *old = productClone(p);

    productSetQuantity(p, newQuantity);
    productSetDate(p, newDate);

    Operation *o = operationNew(controllerUpdateProductOperation, controllerUpdateProductOperation, ctrl, p, old);
    vectorPushBack(ctrl->undoStack, o);
    controllerUpdateProductOperation(ctrl, p);

    vectorClear(ctrl->redoStack);
    productDestroy(old);

    return 1;

}


vector *controllerGetProducts(Controller *ctrl, int (*filter)(void *, void **), void **query,
                              int (*comparator)(const void *, const void *)) {
    vector *ret = vectorFilter(repositoryAll(ctrl->rep), filter, query);
    if (comparator != NULL) {
        vectorSort(ret, comparator);
    }
    return ret;
}

int controllerUndo(Controller *ctrl) {
    return undoOperation(ctrl->undoStack, ctrl->redoStack);
}


int controllerRedo(Controller *ctrl) {
    return redoOperation(ctrl->undoStack, ctrl->redoStack);
}

vector *controllerGetAllProducts(Controller *ctrl) {
    return repositoryAll(ctrl->rep);
}
