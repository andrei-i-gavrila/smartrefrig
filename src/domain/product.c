//
// Created by Andrei Gavrila on 06.03.2017.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "product.h"

Product *productNew(char *name, category_type type, int qty, char *date) {
    Product *p = (Product *) malloc(sizeof(Product));

    if (p == NULL) {
        return NULL;
    }
    p->name = NULL;
    p->date = NULL;
    productSetName(p, name);
    productSetDate(p, date);
    productSetQuantity(p, qty);
    productSetCategory(p, type);

    return p;
}

void productDestroy(void *p) {
    free(((Product *) p)->name);
    free(((Product *) p)->date);
    free(p);
}

char *productGetName(Product *p) {
    if (p == NULL) {
        return NULL;
    }

    return p->name;
}

int productSetName(Product *p, char *name) {
    if (p == NULL) {
        return 0;
    }

    size_t nameLength = strlen(name) + 1;
    if (p->name != NULL) {
        free(p->name);
    }
    p->name = (char *)calloc(nameLength, sizeof(char));
    strcpy(p->name, name);
    return 1;
}

int productGetQuantity(Product *p) {
    if (p == NULL) {
        return 0;
    }

    return p->quantity;
}

int productSetQuantity(Product *p, int quantity) {
    if (p == NULL) {
        return 0;
    }

    p->quantity = quantity;

    return 1;
}

char *productGetDate(Product *p) {
    if (p == NULL) {
        return NULL;
    }

    return p->date;
}

int productSetDate(Product *p, char *date) {
    if (p == NULL) {
        return 0;
    }

    size_t dateLength = strlen(date) + 1;
    if (p->date != NULL) {
        free(p->date);
    }
    p->date = (char *) calloc(dateLength, sizeof(char));
    strncpy(p->date, date, dateLength);

    return 1;
}


category_type productGetCategory(Product *p) {
    return p->category;
}

int productSetCategory(Product *p, category_type type) {
    if (p == NULL) {
        return 0;
    }

    p->category = type;

    return 1;
}

int productSearch(void *product, void **searchAttributes) {

    char *searchName = (char *) searchAttributes[0];
    int *searchCategory = (int *) searchAttributes[1];
    Product *p = (Product *) product;
    if (strcmp(p->name, searchName) == 0 && *searchCategory == p->category) {
        return 1;
    }
    return 0;
}

int productNameContains(void *p, void **filters) {

    char *query = (char *) filters[0];
    return strstr(productGetName(p), query) != NULL;

}

const char *categoryString(category_type t) {

    switch (t) {
        case DAIRY:
            return "Dairy";
        case MEAT:
            return "Meat";
        case SWEETS:
            return "Sweets";
        case FRUIT:
            return "Fruit";
    }
    return "";
}

char *productString(void *p) {
    char *str = calloc(100, sizeof(char));


    sprintf(str, "%s\nCategory %s. Expires at %s. Quantity %d", productGetName(p),
            categoryString(productGetCategory(p)), productGetDate(p), productGetQuantity(p));
    return str;
}

int productSortQuantity(void *a, void *b) {
    return productGetQuantity(*(void **) b) - productGetQuantity(*(void **) a);
}

int productCategory(void *product, void **filters) {
    category_type t = *(category_type *) filters[0];

    return productGetCategory(product) == t;
}
