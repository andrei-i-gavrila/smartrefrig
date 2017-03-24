//
// Created by Andrei Gavrila on 22.03.2017.
//

#include <stddef.h>
#include <stdlib.h>
#include "undo.h"

Operation *operationNew(void (*doFunction)(Controller *, Product *), void (*undoFunction)(Controller *, Product *),
                        Controller *c, Product *doProduct, Product *undoProduct) {

    Operation *o = malloc(sizeof(Operation));

    o->controller = c;
    o->doFunction = doFunction;
    o->undoFunction = undoFunction;
    o->doProduct = productClone(doProduct);
    o->undoProduct = productClone(undoProduct);

    return o;
}

void operationDestroy(void *o) {
    productDestroy(((Operation *) o)->doProduct);
    productDestroy(((Operation *) o)->undoProduct);

    free(o);
}

void *operationClone(void *o) {
    Operation *op = (Operation*)o;

    return operationNew(op->doFunction, op->undoFunction, op->controller, op->doProduct, op->undoProduct);
}


int redoOperation(vector *undoStack, vector *redoStack) {
    Operation *o = vectorPop(redoStack);
    if (o == NULL) {
        return 0;
    }
    vectorPushBack(undoStack, o);
    o->doFunction(o->controller, productClone(o->doProduct));
    return 1;
}

int undoOperation(vector *undoStack, vector *redoStack) {
    Operation *o = vectorPop(undoStack);
    if (o == NULL) {
        return 0;
    }
    vectorPushBack(redoStack, o);
    o->undoFunction(o->controller, productClone(o->undoProduct));
    return 1;
}

