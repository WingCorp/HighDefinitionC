#include "./../test.h"
#include "./../assert.h"
#include "./../../src/array/array.h"
#include "./../../src/list/list.h"
#include "./../../src/dynamic/dynamic.h"
#include "./../../src/foreach/foreach.h"
#include "./../../src/fold/fold.h"
#include "./../../src/map/map.h"
#include "./../../src/str/str.h"
#include "./../../src/input/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int input_startEndTest()
{
    Input* inp = input_fromPath("./out/test/input_data.txt", 64);
    Dynamic lineOpt = input_readLine(inp);
    char* string = str(coerce(lineOpt));
    input_end(inp);
    return assertStringEquals("4", string);
}

Dynamic scanLength(char* str)
{
    int n;
    sscanf(str, "%d\n", &n);
    return di32(n);
}

int input_scanTest()
{
    Input* inp = input_fromPath("./out/test/input_data.txt", 64);
    int length = i32(input_scan(inp, scanLength));
    input_end(inp);
    return assertIntEquals(4, length);
}

Dynamic scanLine(char* str)
{
    char name[8];
    char domain[16];
    sscanf(str, "%[_a-zA-Z0-9.]@%[_a-zA-Z0-9.]\n", name, domain);
    return pair(dstr(name), dstr(domain));
}

int input_scanTestScanNLines()
{
    Input* inp = input_fromPath("./out/test/input_data.txt", 64);
    int length = i32(input_scan(inp, scanLength));
    Iterator* scannedItems = input_scanN(inp, scanLine, length);
    char* domain = str(snd(coerce(iterator_next(scannedItems))));
    iterator_reset(scannedItems);
    char* names = str_join(", ", map(scannedItems, fst), str);
    input_end(inp);
    return assertStringEquals("itu.dk", domain) && assertStringContains(names, "mkon");
}

int main()
{
    test_declareAndRun("input start and end with file works.", input_startEndTest);
    test_declareAndRun("input scan 1 lineOpt and parse contents", input_scanTest);
    test_declareAndRun("input scan many lines and parse contents", input_scanTestScanNLines);
}