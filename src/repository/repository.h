//
// Created by Andrei Gavrila on 06.03.2017.
//

#ifndef INTELLIGENTREFRIGERATOR_REPOSITORY_H
#define INTELLIGENTREFRIGERATOR_REPOSITORY_H


#include "../utils/vector.h"
#include "../domain/product.h"

typedef struct {
    vector *products;

} Repository;


/// @brief Creates a repository
/// @return Pointer to the repository
Repository *repositoryCreate();

/// @brief Destorys a repository
/// @param rep  Repository
/// @param dataDestructor destructor for the repo elements
void repositoryDestroy(Repository *rep, void (*dataDestructor)(void *));

/// @brief Adds an element to the repository
/// @param rep The repository
/// @param p The pointer for the new element
void repositoryAdd(Repository *rep, void *p);

/// @brief Searches a product in the repository
/// @param rep Repository
/// @param searchFunction Search function comparator
/// @param searchAttributes Search query
/// @return The index of the result
int repositoryFind(Repository *rep, int (*searchFunction)(void *, void **), void **searchAttributes);

/// @brief Gets the idth element from the repo
/// @param rep The repo
/// @param id The index to be extracted
/// @return pointer to the extracted element
void *repositoryGet(Repository *rep, int id);

//readall
/// @brief Returns all the elements
/// @param rep The repo
/// @return The vector with all the elements
vector *repositoryAll(Repository *rep);

//repositoryUpdate
/// @brief Updates an element in the repo
/// @param rep The repo
/// @param i The index of the element to be updated
/// @param p The new pointer
void repositoryUpdate(Repository *rep, int i, void *p);

//vectorDelete
/// @brief Deletes an element from the repo
/// @param rep The repo
/// @param i The index of the element
void repositoryRemove(Repository *rep, int i);

#endif //INTELLIGENTREFRIGERATOR_REPOSITORY_H
