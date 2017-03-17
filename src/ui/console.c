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

int readCommand(int n) {
    int command = n;
    printf(">>> ");
    do {
        scanf("%d", &command);
    } while (command >= n || command < 0);
    return command;
}

int printOptions() {
    const int n = 6;
    char *options[] = {
            "0. Exit!",
            "1. Add a product!",
            "2. Update a product!",
            "3. Delete some products!",
            "4. Search products!",
            "5. List category!",
    };

    for (int i = 0; i < n; i++) {
        printf("%s\n", options[i]);
    }
    return n;
}

void waitForKey() {
    printf("Press any key...");
    while (getchar() != '\n');
    getchar();
}

void clearScreen() {
    for (int i = 0; i < 20; i++) {
        printf("\n");
    }
}

category_type readCategory() {
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

    category_type type = readCategory();

    int qty;
    printf("Quantity:\n");
    scanf("%d", &qty);

    char date[11];
    readString("Date Y-m-d", date, 10);

    controllerAddProduct(c->ctrl, name, type, qty, date);
}

void deleteProduct(Console *c) {
    char name[21];
    readString("Product name", name, 20);

    category_type type = readCategory();

    controllerDeleteProduct(c->ctrl, name, type);
}

void listProducts(Console *c) {
    char query[20];
    readString("Enter query", query, 20);

    vector *r = controllerGetProducts(c->ctrl, query);

    for (int i = 0; i < vectorSize(r); i++) {
        printf("#%d: %s\n", i+1, productString(vectorGet(r, i)));
    }
}

void updateProduct(Console *c) {
    char name[21];
    readString("Product name", name, 20);

    category_type type = readCategory();

    int newQty;
    printf("New Quantity:\n");
    scanf("%d", &newQty);

    char newDate[11];
    readString("New date", newDate, 11);

    controllerUpdateProduct(c->ctrl, name, type, newQty, newDate);
}

void listCategory(Console *c) {
    category_type t = readCategory();

    void *filters[] = {&t};

    vector *r = controllerGetProductsFiltered(c->ctrl, productCategory, filters);
    vectorSort(r, productSortQuantity);
    for (int i = 0; i < vectorSize(r); i++) {
        printf("#%d: %s\n", i+1, productString(vectorGet(r, i)));
    }
}

void consoleRun(Console *c) {
    int command;

    void (*options[6])(Console *);

    options[1] = addProduct;
    options[2] = updateProduct;
    options[3] = deleteProduct;
    options[4] = listProducts;
    options[5] = listCategory;

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
