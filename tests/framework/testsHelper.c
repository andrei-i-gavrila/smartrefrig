//
// Created by Andrei Gavrila on 07.03.2017.
//

#include "testsHelper.h"
#include <time.h>
void runTest(const char *testName, void (*test)()) {
    static int numTest = 1;
    printf("=================================\n");
    printf("Running test #%d: %s!\n", numTest, testName);
    fflush(stdout);
    clock_t start = clock();
    test();
    printf("Success! Test #%d took %f\n", numTest, (double)(clock()-start)/CLOCKS_PER_SEC);
    printf("=================================\n\n");
    numTest++;
    fflush(stdout);

}

void runModule(const char *moduleName, void (*moduleRun)()) {
    static int numModule = 1;
    printf("#################################\n");
    printf("Running test module #%d: %s!\n", numModule, moduleName);
    fflush(stdout);
    clock_t start = clock();
    moduleRun();
    printf("Module took %f\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    printf("#################################\n\n");
    numModule++;
    fflush(stdout);
}
