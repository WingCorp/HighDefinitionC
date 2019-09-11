//Trying to solve https://itu.kattis.com/problems/bst

#include "hdc.h"

#include "src/fail/fail.h"
#include "src/dynamic/dynamic.h"
#include "src/option/option.h"
#include "src/comparable/comparable.h"
#include "src/hash/hash.h"
#include "src/iterator/iterator.h"
#include "src/foreach/foreach.h"
#include "src/map/map.h"
#include "src/fold/fold.h"
#include "src/array/array.h"
#include "src/stack/stack.h"
#include "src/input/input.h"

#include <stdio.h>

Dynamic parseDigit(char* line)
{
    int n;
    sscanf(line, "%d\n", &n);
    return di32(n);
}

int main()
{
    Input* input = input_start(stdin, 8);
    int n = i32(input_scan(input, parseDigit));
}
