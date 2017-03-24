//
// Created by Andrei Gavrila on 22.03.2017.
//

#ifndef INTELLIGENTREFRIGERATOR_UNDO_H
#define INTELLIGENTREFRIGERATOR_UNDO_H

#include "../controller/controller.h"

typedef struct {
    void (*doFunction)(Controller *, Product *);

    void (*undoFunction)(Controller *, Product *);

    Product *doProduct, *undoProduct;
    Controller *controller;
} Operation;

Operation *operationNew(void (*doFunction)(Controller *, Product *), void (*undoFunction)(Controller *, Product *),
                        Controller *c, Product *doProduct, Product *undoProduct);

void operationDestroy(void *o);

int redoOperation(vector *undoStack, vector *redoStack);

int undoOperation(vector *undoStack, vector *redoStack);


#endif //INTELLIGENTREFRIGERATOR_UNDO_H
