#ifndef DICTIONARY_H
#define DICTIONARY_H


/**
 * @file dictionary.h
 * @author Jon Voigt Tøttrup (jvoi@itu.dk)
 *
 * @brief A hash-table style dictionary.
 * 
 * Capable of storing by string.
 * Useful for storing dynamics.
 * 
 * @version 0.1
 * @date 2018-11-05
 *
 * @copyright WingCorp (c) 2018
 * 
 */

#include "./../dynamic/dynamic.h"
#include "./../option/option.h"
#include "./../hash/hash.h"

#include <stdarg.h>

typedef struct _Dict Dict;

/**
 * @brief Returns a new, empty dictionary, ready for use.
 * 
 * @return Dict* 
 */
Dict* dict_empty();

/**
 * @brief Creates a dictionary from a set of key-value pairs.
 * 
 * @param count The initial size of the dictionary.
 *              Must correspond to the total amound of pairs in this call.
 * @param pair A key-value pair, the left side of the pair must be an unsigned long.
 *             The dictionary uses the HDC hash function, meaning that you can use hash(<your char*>)
 *             to use strings as keys.
 *             Otherwise, just build the Dictionary yourself.
 * @param ... A variable amount of pairs.
 * @return Dict* A dictionary of the pairs.
 */
Dict* dict_from(int count, Dynamic pair, ...);

/**
 * @brief Determine whether the dictionary contains an entry for the given key.
 * 
 * @param dict The dictionary to search.
 * @param key The key to find.
 * @return true The key is in the dictionary.
 * @return false The key is not in the dictionary.
 */
bool dict_contains(Dict* dict, unsigned long key);

/**
 * @brief Get a value from the dictionary by the given key.
 * 
 * @param dict The dictionary.
 * @param key The key to get by.
 * @return Option An option, possibly containing a value.
 */
Option dict_get(Dict* dict, unsigned long key);

/**
 * @brief Store the given value by the given key in the dictionary.
 * 
 * @param dict The dictionary.
 * @param key The key to store by.
 * @param val The value to store.
 */
void dict_put(Dict* dict, unsigned long key, Dynamic val);

/**
 * @brief Remove a value from the dictionary by the given key.
 * 
 * @param dict The dictionary to remove the key-value pair from.
 * @param key The key that is to be removed along its value.
 */
void dict_remove(Dict* dict, unsigned long key);

/**
 * @brief Remove a value from the dictionary and apply a destruction function to free
 * the stored value as well. Only use this function for 'ref' dynamics and if you know
 * what you are doing.
 * 
 * @param dict The dictionary to remove the key-value pair from.
 * @param key The key that is to be removed along with its value.
 * @param destroyer A function that takes a dynamic and frees the memory references.
 *                  Only use this for 'ref' dynamics.
 */
void dict_remove_destroy(Dict* dict, unsigned long key, void (*destroyer)(Dynamic));

/**
 * @brief Determine whether the dictionary contains an entry for the given key string.
 * 
 * @param dict The dictionary to search.
 * @param key The key string to find.
 * @return true The key string is in the dictionary.
 * @return false The key string is not in the dictionary.
 */
bool dict_contains(Dict* dict, unsigned long key);

/**
 * @brief Returns the size of the dictionary
 * 
 * @param dict A pointer to a dictionary.
 */
int dict_size(Dict* dict);

/**
 * @brief Determines whether the given dictionary is empty.
 * 
 * @param dict A pointer to a dictionary.
 * @return true The dictionary is empty.
 * @return false The dictionary is not empty.
 */
bool dict_isEmpty(Dict* dict);

/**
 * @brief Get a value from the dictionary by the given key string.
 * 
 * @param dict The dictionary.
 * @param key The key to get by.
 * @return Option An option, possibly containing a value.
 */
Option dict_get_s(Dict* dict, char* key);

/**
 * @brief Store the given value by the given key string in the dictionary.
 * 
 * @param dict The dictionary.
 * @param key The key string to store by.
 * @param val The value to store.
 */
void dict_put_s(Dict* dict, char* key, Dynamic val);

/**
 * @brief Remove a value from the dictionary by the given key string.
 * 
 * @param dict The dictionary to remove the key-value pair from.
 * @param key The key string that is to be removed along its value.
 */
void dict_remove_s(Dict* dict, char* key);

/**
 * @brief Remove a value from the dictionary and apply a destruction function to free
 * the stored value as well. Only use this function for 'ref' dynamics and if you know
 * what you are doing.
 * 
 * @param dict The dictionary to remove the key-value pair from.
 * @param key The key string that is to be removed along with its value.
 * @param destroyer A function that takes a dynamic and frees the memory references.
 *                  Only use this for 'ref' dynamics.
 */
void dict_remove_destroy_s(Dict* dict, char* key, void (*destroyer)(Dynamic));

/**
 * @brief Destroys the given dictionary, freeing it from memory.
 * 
 * @param dict The dictionary to destroy.
 */
void dict_destroy(Dict* dict);

/**
 * @brief Destroys the given dictionary, freeing it from memory.
 *        Uses the provided destroyer function to destroy dynamics stored in the dictionary.
 *        Only useful if you are using 'ref' type dynamics.
 * 
 * @param dict The dictionary to destroy.
 * @param destroyer A function that takes a dynamic and frees the memory references.
 *                  Only use this for 'ref' dynamics.
 */
void dict_destroy_thorough(Dict* dict, void (*destroyer)(Dynamic));

#endif