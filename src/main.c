#include <stdio.h>
#include "repository/repository.h"
#include "controller/controller.h"
#include "ui/console.h"

int main() {
    printf("Hello, World!\n");


    Repository *rep = repositoryCreate(productDestroy, productClone);
    Controller *ctrl = controllerCreate(rep);

    controllerAddProduct(ctrl, "Lapte", DAIRY, 2, "2017-03-26");
    controllerAddProduct(ctrl, "Branza", DAIRY, 2, "2017-03-26");
    controllerAddProduct(ctrl, "Sasesc", MEAT, 1, "2017-03-26");
    controllerAddProduct(ctrl, "Pui", MEAT, 2, "2017-03-26");
    controllerAddProduct(ctrl, "Cascaval", DAIRY, 1, "2017-03-26");
    controllerAddProduct(ctrl, "Ciocolata", SWEETS, 2, "2017-03-26");
    controllerAddProduct(ctrl, "Mere", FRUIT, 15, "2017-03-26");
    controllerAddProduct(ctrl, "Struguri", FRUIT, 10, "2017-03-26");
    controllerAddProduct(ctrl, "Unt", DAIRY, 1, "2017-03-26");
    controllerAddProduct(ctrl, "Gem", SWEETS, 1, "2017-03-26");

    Console *c = consoleCreate(ctrl);



    consoleRun(c);

    consoleDestroy(c);
    controllerDestroy(ctrl);
    repositoryDestroy(rep);

    /*
     * TODO: List
     *
     *
     *       check missing specs
     *       add controller tests
     *
     *       new undo???
     *
     * */


    return 0;
}