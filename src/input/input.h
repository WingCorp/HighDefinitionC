#ifndef INPUT_H
#define INPUT_H

/**
 * @file input.h
 * @author Jon Voigt Tøttrup (jvoi@itu.dk)
 * @brief An inputreader class that uses scanf to parse lines. Perfect for kattis.
 * @version 0.1
 * @date 2019-09-10
 * 
 * @copyright WingCorp (c) 2019
 * 
 */

#include <stdio.h>
#include "./../list/list.h"

typedef struct _Input Input;

Input* input_start(char* path);

List* input_findNext(Input* input, char* format);

char* input_readLine(Input* input);

void input_end(Input* input);

#endif
