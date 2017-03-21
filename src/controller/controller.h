//
// Created by Andrei Gavrila on 12.03.2017.
//

#include "../repository/repository.h"

#ifndef INTELLIGENTREFRIGERATOR_CONTROLLER_H
#define INTELLIGENTREFRIGERATOR_CONTROLLER_H

typedef struct {
    Repository *rep;
} Controller;

/// @brief Creates a controller
/// @param rep Underlying repository
/// @return Pointer to the new controller
Controller *controllerCreate(Repository *rep);

/// @brief Destroys a controller
/// @param ctrl The controller
void controllerDestroy(Controller *ctrl);

/// @brief Adds a product to the repo
/// @param ctrl The controller
/// @param name The product name
/// @param type The product type
/// @param quantity The product quantity
/// @param date The product date
/// @return 1 if new product was added, 0 if updated
int controllerAddProduct(Controller *ctrl, char *name, category_type type,
                          int quantity, char *date);

/// @brief Updates a product
/// @param ctrl The controller
/// @param name The name ident
/// @param type The type ident
/// @param newQuantity The new quantity
/// @param newDate The new date
/// @return 1 if update was done, 0 if product was not found
int controllerUpdateProduct(Controller *ctrl, char *name, category_type type,
                             int newQuantity, char *newDate);

/// @brief Deletes a product from the repository
/// @param ctrl controller
/// @param name Product name
/// @param type Product type
/// @return 1 if product was deleted, 0 if it was not found
int controllerDeleteProduct(Controller *ctrl, char *name, category_type type);

/// @brief Gets all products
/// @param ctrl The controller
/// @return Pointer to a vector that has all the products
vector *controllerGetAllProducts(Controller *ctrl);

/// @brief Gets only filtered products
/// @param ctrl Controller
/// @param query The query
/// @return pointer to a filtered vector
vector *controllerGetProducts(Controller *ctrl, char *query);

vector *controllerGetProductsFiltered(Controller *ctrl, int (*filter)(void *, void **), void **filters);

#endif //INTELLIGENTREFRIGERATOR_CONTROLLER_H
