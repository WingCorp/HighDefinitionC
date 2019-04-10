#ifndef TREE_H
#define TREE_H

/**
 * @file tree.h
 * @author Jon Voigt Tøttrup (jvoi@itu.dk)
 * @brief An implementation of the Red-Black BST data structure.
 * @version 0.1
 * @date 2018-11-01
 * 
 * @copyright WingCorp (c) 2018
 * 
 */

#include "./../comparable/comparable.h"
#include "./../option/option.h"
#include "./../iterator/iterator.h"

typedef struct _Tree Tree;

/**
 * @brief Initialize a new Tree.
 * 
 * @return Tree* a new Tree instance.
 */
Tree* tree_init();

/**
 * @brief Destroy the given tree, freeing the memory.
 * 
 * @param tree The tree to destroy.
 */
void tree_destroy(Tree* tree);

/**
 * @brief Inserts a value into the tree.
 * 
 * @param tree The Tree to put the element into.
 * @param key The key to distinguish the element by.
 * @param value The value to insert.
 */
void tree_put(Tree* tree, Comparable key, Dynamic value);

/**
 * @brief Attempts to retrieve a value from the tree by a key.
 * 
 * @param tree The tree to get the value from.
 * @param key The key to get by.
 * @return Option An option that might contain a value.
 */
Option tree_get(Tree* tree, Comparable key);

/**
 * @brief Remove a value from the tree matching the given key.
 * 
 * @param tree The tree to remove from.
 * @param key The key to remove by.
 */
void tree_remove(Tree* tree, Comparable key);

/**
 * @brief Determines the size of the given tree.
 * 
 * @param tree The tree to get the size from.
 * @return int The size of the tree.
 */
int tree_size(Tree* tree);

/**
 * @brief Prints the layout of the tree.
 * 
 * Prints () for empty nodes and (O) for nodes with values.
 * 
 * @param tree The tree to print.
 */
void tree_print(Tree* tree);

/**
 * @brief Determines if the tree contains a value.
 * 
 * Should take O(log(N))
 * 
 * @param tree The Tree to check.
 * @param key The key to check for.
 * @return true The key is present in the tree.
 * @return false The key is not present in the tree.
 */
bool tree_contains(Tree* tree, Comparable key);

/**
 * @brief Returns an ordered iterator from the tree.
 * 
 * @param tree The tree to create the iterator from.
 * @return Iterator* An ordered iterator.
 */
Iterator* tree_iterator(Tree* tree);

#endif

