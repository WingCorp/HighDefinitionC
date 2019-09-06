#ifndef STR_H

#define STR_H
/**
 * @file str.h
 * @author Jon Voigt Tøttrup (jon@zendata.dk)
 * @brief A set of helper methods for strings.
 * @version 0.1
 * @date 2019-09-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <stdbool.h>
#include "./../iterator/iterator.h"


char* str_concat(char* a, char* b);

Dynamic str_concat_d(Dynamic a, Dynamic b);

char* str_concat_c(char* s, char c);

Dynamic str_concat_c_d(Dynamic s, Dynamic c);

char* str_join(char* infix, Iterator* iterator,  char* (*to_string)(Dynamic));

Iterator* str_iterator(char* string);

bool str_equals(char* strA, char* strB);

char* to_str(Dynamic d);

#endif