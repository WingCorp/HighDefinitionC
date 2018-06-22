#include "fail.h"
#include <stdlib.h>
#include <execinfo.h>
#include <stdio.h>

#define RED "\x1b[31m"
#define RESET "\x1b[0m"

void* callstack[512];

void trace_stack()
{
    int frames = backtrace(callstack, 512);
    char** strs = backtrace_symbols(callstack, frames);
    int i;
    printf(RED);
    for (i = 0; i < frames; i++)
    {
        printf("%s\n", strs[i]);
    }
    printf(RESET);
    free(strs);
}

void fail()
{
    trace_stack();
    exit(EXIT_FAILURE);
}

void failwith(char* cause)
{
    printf(RED);
    printf("%s\n", cause);
    printf(RESET);
    trace_stack();
    exit(EXIT_FAILURE);
}
