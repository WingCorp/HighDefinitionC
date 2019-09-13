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
#include "./../dynamic/dynamic.h"
#include "./../option/option.h"
#include "./../iterator/iterator.h"

typedef struct _Input Input;

Input* input_fromFile(FILE* file, int bufferSize);

Input* input_fromPath(char* path, int bufferSize);

Dynamic input_scan(Input* input, Dynamic (*scanfun)(char*));

Iterator* input_scanN(Input* input, Dynamic (*scanfun)(char*), int n);

void input_scanNHandler(Input* input, void (*lineHandler)(char*), int n);

Iterator* input_scanEnd(Input* input, Dynamic (*scanfun)(char*));

void input_scanEndHandler(Input* input, void (*lineHandler)(char*));

Option input_readLine(Input* input);

void input_end(Input* input);

#endif
