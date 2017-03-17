//
// Created by Andrei Gavrila on 06.03.2017.
//

#ifndef INTELLIGENTREFRIGERATOR_DOMAIN_H
#define INTELLIGENTREFRIGERATOR_DOMAIN_H

typedef enum {
    DAIRY, SWEETS, MEAT, FRUIT
} category_type;

typedef struct {
    char *name;
    category_type category;
    int quantity;
    char *date;
} Product;

/// @brief Creates a new product
/// @param name The name
/// @param type The type
/// @param qty The quantity
/// @param date The date
/// @return Pointer to the new product
Product *productNew(char *name, category_type type, int qty, char *date);

/// @brief Destroys a product
/// @param p The product to be destroyed
void productDestroy(void *p);

/// @brief Returns a product name
/// @param p The product
/// @return The name of the product
char *productGetName(Product *p);

/// @brief Sets a product name
/// @param p the product
/// @param name the name
/// @return 1 on success, 0 on failure
int productSetName(Product *p, char *name);

/// @brief Returns a product quantity
/// @param p The product
/// @return The quantity of the product
int productGetQuantity(Product *p);

/// @brief Sets a product quantity
/// @param p the product
/// @param quantity the quantity
/// @return 1 on success, 0 on failure
int productSetQuantity(Product *p, int quantity);

/// @brief Returns a product date
/// @param p The product
/// @return The date of the product
char *productGetDate(Product *p);

/// @brief Sets a product date
/// @param p The product
/// @param date The date
/// @return 1 on success, 0 on failure
int productSetDate(Product *p, char *date);

/// @brief Returns a product category
/// @param p The product
/// @return The category of the product
category_type productGetCategory(Product *p);

/// @brief Sets a product category
/// @param p the product
/// @param type the category
/// @return 1 on success, 0 on failure
int productSetCategory(Product *p, category_type type);

/// @brief Checks if a product matches a search
/// @param product the product
/// @param searchAttributes the searching attributes
/// @return 1 if it does, 0 if not
int productSearch(void *product, void **searchAttributes);

/// @brief Checks whether a product name contains a string
/// @param product The product
/// @param filters The filters
/// @return 1 if true, 0 if not
int productNameContains(void *product, void **filters);

int productCategory(void *product, void **filters);

/// @brief String representation of product
/// @param p the product
/// @return The string representation
char *productString(void *p);

int productSortQuantity(void *a, void *b);
#endif //INTELLIGENTREFRIGERATOR_DOMAIN_H
