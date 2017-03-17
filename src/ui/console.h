//
// Created by Andrei Gavrila on 16.03.2017.
//

#ifndef INTELLIGENTREFRIGERATOR_CONSOLE_H
#define INTELLIGENTREFRIGERATOR_CONSOLE_H

#include "../controller/controller.h"

typedef struct {
    Controller* ctrl;
} Console;

Console *consoleCreate(Controller *ctrl);

void consoleDestroy(Console *c);

void consoleRun(Console *c);

#endif //INTELLIGENTREFRIGERATOR_CONSOLE_H
