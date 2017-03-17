//
// Created by Andrei Gavrila on 07.03.2017.
//

#ifndef INTELLIGENTREFRIGERATOR_TESTS_HELPER_H
#define INTELLIGENTREFRIGERATOR_TESTS_HELPER_H

#include <stdio.h>

void runTest(const char *testName, void (*test)());

void runModule(const char *moduleName, void (*moduleRun)());

#endif //INTELLIGENTREFRIGERATOR_TESTS_HELPER_H
