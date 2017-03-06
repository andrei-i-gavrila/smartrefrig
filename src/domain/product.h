//
// Created by Andrei Gavrila on 06.03.2017.
//

#ifndef INTELLIGENTREFRIGERATOR_DOMAIN_H
#define INTELLIGENTREFRIGERATOR_DOMAIN_H

typedef enum {
    DAIRY, SWEETS, MEAT, FRUIT
} category_type;

typedef struct {
    char name[20];
    category_type category;
    int quantity;
    char date[10];
} Product;

char *getName(Product *p);

void setName(Product *p, char *name);

int getQuantity(Product *p);

void setQuantity(Product *p, int quantity);

char *getDate(Product *p);

void setDate(Product *p, category_type category);


#endif //INTELLIGENTREFRIGERATOR_DOMAIN_H
