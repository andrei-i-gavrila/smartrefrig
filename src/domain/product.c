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
    memset(&p->date, 0, sizeof(struct tm));
    productSetName(p, name);
    productSetDate(p, date);
    productSetQuantity(p, qty);
    productSetCategory(p, type);

    return p;
}

void productDestroy(void *p) {
    free(((Product *) p)->name);
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
    p->name = (char *) malloc(nameLength*sizeof(char));
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

void productGetDate(Product *p, char ret[11]) {
    strftime(ret, 11, "%F", &p->date);
}

int productSetDate(Product *p, char *date) {
    if (p == NULL) {
        return 0;
    }

    int y, m, d;
    if (sscanf(date, "%d-%d-%d", &y, &m, &d) != 3) {
        return 0;
    }

    p->date.tm_year = y - 1900;
    p->date.tm_mon = m - 1;
    p->date.tm_mday = d;
    p->date.tm_isdst = 0;
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

int productFilterDate(void *p, void **filters) {

    int days = *(int *) filters[0];
    int seconds = days * 24 * 60 * 60;

    time_t now = time(NULL);

    double diff = difftime(mktime(&((Product *)p)->date), now);

    return diff <= seconds;
}

int productNameContains(void *p, void **filters) {
    char *query = (char *) filters[0];
    return strcmp(query, "\n") == 0 ? 1 : strstr(productGetName(p), query) != NULL;

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
        case UNDEFINED_CATEGORY:
            break;
    }
    return "";
}

char *productString(void *p) {
    char *str = calloc(100, sizeof(char));


    char date[11];
    productGetDate(p, date);
    sprintf(str, "%s\nCategory %s. Expires at %s. Quantity %d", productGetName(p),
            categoryString(productGetCategory(p)), date, productGetQuantity(p));
    return str;
}

int productSortQuantityDesc(const void *a, const void *b) {
    return productGetQuantity(*(void **) b) - productGetQuantity(*(void **) a);
}

int productCategory(void *product, void **filters) {
    category_type t = *(category_type *) filters[0];

    return t == UNDEFINED_CATEGORY? 1: productGetCategory(product) == t;
}

void *productClone(void *p) {
    if (p == NULL) {
        return NULL;
    }
    char b[11];
    productGetDate((Product *) p, b);
    Product *new = productNew(((Product *) p)->name, ((Product *) p)->category, ((Product *) p)->quantity, b);
    return new;
}

int productSortQuantityAsc(const void *a, const void *b) {
    return productGetQuantity(*(void **) a) - productGetQuantity(*(void **) b);
}
