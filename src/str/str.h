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

#include "./../iterator/iterator.h"

char* str_concat(char* a, char* b);

char* str_join(char* infix, Iterator* iterator,  char* (*to_string)(Dynamic));

char* to_str(Dynamic d);

#endif