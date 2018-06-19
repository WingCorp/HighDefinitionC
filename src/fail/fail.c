#include "fail.h"
#include <stdlib.h>
#include <execinfo.h>
#include <stdio.h>

void* callstack[128];

void trace_stack()
{
    int frames = backtrace(callstack, 128);
    char** strs = backtrace_symbols(callstack, frames);
    int i;
    for (i = 0; i < frames; i++)
    {
        printf("%s\n", strs[i]);
    }
    free(strs);
}

void fail()
{
    trace_stack();
    exit(EXIT_FAILURE);
}

void failwith(char* cause)
{
    trace_stack();
    printf("%s\n", cause);
    exit(EXIT_FAILURE);
}