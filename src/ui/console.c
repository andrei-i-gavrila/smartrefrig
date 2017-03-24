//
// Created by Andrei Gavrila on 16.03.2017.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "console.h"

Console *consoleCreate(Controller *ctrl) {
    Console *c = malloc(sizeof(Console));
    c->ctrl = ctrl;
    return c;
}

void consoleDestroy(Console *c) {
    free(c);
}

void waitForKey() {
    printf("Press any key...");
    while (getchar() != '\n');
    getchar();
}

int readCommand(int n) {
    int command = n;
    int i = 0;
    do {
        printf(">>> ");

        if(scanf(" %d", &command) != 1) {
            printf("Enter only a number!\n");
            waitForKey();
        }
        i++;
        if (i == 10) {
            return 0;
        }

    } while (command >= n || command < 0);
    return command;
}

int printOptions() {
    const int n = 9;
    char *options[] = {
            "0. Exit!",
            "1. Add a product!",
            "2. Update a product!",
            "3. Delete some products!",
            "4. Search products!",
            "5. List category!",
            "6. Undo last operation",
            "7. Redo last operation",
            "8. List by category descending",
    };

    for (int i = 0; i < n; i++) {
        printf("%s\n", options[i]);
    }
    return n;
}

void clearScreen() {
    for (int i = 0; i < 20; i++) {
        printf("\n");
    }
}

category_type readCategory(int undefined) {
    printf("Categories: DAIRY, MEAT, SWEETS, FRUITS\n");
    while (1) {
        printf("Enter the first letter: ");
        char cat;
        scanf(" %c", &cat);

        switch (cat) {
            case 'd':
            case 'D':
                return DAIRY;
            case 'm':
            case 'M':
                return MEAT;
            case 's':
            case 'S':
                return SWEETS;
            case 'f':
            case 'F':
                return FRUIT;
            default:
                if (undefined == 0) {
                    return UNDEFINED_CATEGORY;
                }
                printf("Invalid category!\n");
        }
    }
}

void removeTrailingNewline(char *s) {
    char *pos;
    if ((pos = strchr(s, '\n')) != NULL) {
        *pos = '\0';
    }
}

void readString(char message[], char out[], int n) {
    printf("%s:\n", message);
    while (getchar() != '\n');
    fgets(out, n, stdin);
    removeTrailingNewline(out);
}

void addProduct(Console *c) {
    char name[21];
    readString("Product name", name, 20);

    category_type type = readCategory(1);

    int qty;
    printf("Quantity:\n");
    scanf("%d", &qty);

    char date[11];
    readString("Date Y-m-d", date, 11);

    if (controllerAddProduct(c->ctrl, name, type, qty, date)) {
        printf("Added new product.\n");
    } else {
        printf("Updated existing product.\n");
    }

}

void deleteProduct(Console *c) {
    char name[21];
    readString("Product name", name, 20);

    category_type type = readCategory(1);

    if (controllerDeleteProduct(c->ctrl, name, type)) {
        printf("Deleted product successfully.\n");
    } else {
        printf("Could not find specified product.\n");
    }
}


void printProducts(vector *v) {
    for (int i = 0; i < vectorSize(v); i++) {
        printf("#%d: %s\n", i + 1, productString(vectorGet(v, i)));
    }
}

void updateProduct(Console *c) {
    char name[21];
    readString("Product name", name, 20);

    category_type type = readCategory(1);

    int newQty;
    printf("New Quantity:\n");
    scanf("%d", &newQty);

    char newDate[11];
    readString("New date", newDate, 11);

    if (controllerUpdateProduct(c->ctrl, name, type, newQty, newDate)) {
        printf("Updated product successfully.\n");
    } else {
        printf("Could not find product.\n");
    }
}

void listProducts(Console *c) {
    char query[20];
    readString("Enter query", query, 20);

    void *filters[] = {query};
    vector *r = controllerGetProducts(c->ctrl, productNameContains, filters, productSortQuantityAsc);

    printProducts(r);
    vectorDestroy(r);
}

void listCategoryDays(Console *c) {
    category_type t = readCategory(0);

    void *filters[] = {&t};

    vector *tmp = controllerGetProducts(c->ctrl, productCategory, filters, NULL);

    int days;
    printf("Enter days:\n");
    scanf("%d", &days);
    filters[0] = &days;

    vector *r = vectorFilter(tmp, productFilterDate, filters);
    printProducts(r);
    vectorDestroy(r);
    vectorDestroy(tmp);
}

void listCategory(Console *c) {
    category_type t = readCategory(0);

    void *filters[] = {&t};

    vector *tmp = controllerGetProducts(c->ctrl, productCategory, filters, productSortQuantityDesc);

    printProducts(tmp);
    vectorDestroy(tmp);
}

void undo(Console *c) {
    if (controllerUndo(c->ctrl) == 1) {
        printf("Undo was successful!\n");
        return;
    }

    printf("Nothing to undo!\n");
}

void redo(Console *c) {
    if (controllerRedo(c->ctrl) == 1) {
        printf("Redo was successful!\n");
        return;
    }

    printf("Nothing to redo!\n");
}

void consoleRun(Console *c) {
    int command;

    void (*options[9])(Console *);

    options[1] = addProduct;
    options[2] = updateProduct;
    options[3] = deleteProduct;
    options[4] = listProducts;
    options[5] = listCategoryDays;
    options[6] = undo;
    options[7] = redo;
    options[8] = listCategory;
    while (1) {
        command = readCommand(printOptions());
        if (command == 0) {
            return;
        }
        clearScreen();
        options[command](c);
        waitForKey();
        clearScreen();
    }
}
