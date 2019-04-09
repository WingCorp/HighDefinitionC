#include "dictionary.h"
#include "./../fail/fail.h"
#include "./../dynamic/dynamic.h"
#include "./../option/option.h"
#include "./../hash/hash.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define INIT_CAPACITY 4

typedef struct _Dict
{
    int size;
    int capacity;
    unsigned long* keys;
    Dynamic* values;
} Dict;

Dict* dict_empty()
{
    Dict* dict = malloc(sizeof(Dict));
    dict->capacity = INIT_CAPACITY;
    dict->size = 0;
    dict->keys = malloc(sizeof(unsigned long) * INIT_CAPACITY);
    dict->values = malloc(sizeof(Dynamic) * INIT_CAPACITY);
    return dict;
}

int dict_size(Dict* dict)
{
    return dict->size;
}

bool dict_isEmpty(Dict* dict)
{
    return dict->size <= 0;
}

void resize(Dict* dict, int newCapacity)
{
    unsigned long* newKeys = realloc(dict->keys, newCapacity * sizeof(unsigned long));
    Dynamic* newValues = realloc(dict->values, newCapacity * sizeof(Dynamic));
    unsigned long* oldKeys = dict->keys;
    Dynamic* oldValues = dict->values;
    int cap = dict->capacity;
    int i;
    for (i = 0; i < cap; i++)
    {
        newKeys[i] = oldKeys[i];
        newValues[i] = oldValues[i];
    }
    dict->capacity = newCapacity;
}

void dict_put(Dict* dict, unsigned long key, Dynamic value)
{
    if (dict->size >= dict->capacity/2)
    {
        resize(dict, 2 * dict->capacity);
    }
    int i;
    for(i = key % dict->capacity; /* stops when succesful */; i = (i + 1) % dict->capacity)
    {
        if (dict->keys[i] != 0ul) 
        {
            continue;
        }
        dict->keys[i] = key;
        dict->values[i] = value;
        break;
    }
    dict->size++;
}

Option dict_get(Dict* dict, unsigned long key)
{
    if (dict_isEmpty(dict))
    {
        return none();
    }
    int start = key % dict->capacity;
    int i = start;
    do
    {
        if (dict->keys[i] == key)
        {
            return some(dict->values[i]);
        }
        i++;
    } while (i != start);
    return none();
}

bool dict_contains(Dict* dict, unsigned long key)
{
    Option opt = dict_get(dict, key);
    return opt.type == SOME;
}

void dict_remove_destroy(Dict* dict, unsigned long key, void (*destroyer)(Dynamic))
{
    if (dict_isEmpty(dict))
    {
        return;
    }
    int start = key % dict->capacity;
    int i = start;
    do
    {
        if (dict->keys[i] == key)
        {
            dict->keys[i] = 0ul;
            destroyer(dict->values[i]);
            dict->values = NULL;
        }
        i++;
    } while (i != start);
    if (dict->size - 1 <= dict->capacity/3)
    {
        resize(dict, dict->capacity/3);
    }
    dict->size--;
}

void default_destroyer(Dynamic d) {
    //Don't do anything at all.
}

void dict_remove(Dict* dict, unsigned long key)
{
    dict_remove_destroy(dict, key, default_destroyer);
}

Option dict_get_s(Dict* dict, char* key)
{
    return dict_get(dict, hash(key));
}

bool dict_contains_s(Dict* dict, char* key)
{
    return dict_contains(dict, hash(key));
}

void dict_put_s(Dict* dict, char* key, Dynamic val)
{
    dict_put(dict, hash(key), val);
}

void dict_remove_s(Dict* dict, char* key)
{
    dict_remove(dict, hash(key));
}

Dict* dict_from(int count, Dynamic pair, ...)
{
    if (t_fst(pair) != ULONG) {
        failwith("Left type of every pair must be an unsigned long.");
    }
    
    va_list args;
    va_start(args, pair);

    Dict* dict = dict_empty();
    dict_put(dict, ui64(fst(pair)), snd(pair));
    int i;
    for (i = 1; i < count; i++)
    {
        Dynamic param = va_arg(args, Dynamic);
        if (t_fst(param) != ULONG) {
            failwith("Left type of every pair must be an unsigned long.");
        }
        dict_put(dict, ui64(fst(param)), snd(param));
    }
    va_end(args);
    return dict;
}
