#include "fail.h"
#include <stdlib.h>
#include <execinfo.h>
#include <stdio.h>

#define FAIL_RED "\x1b[31m"
#define FAIL_RESET "\x1b[0m"

void* callstack[1024];

void trace_stack()
{
    int frames = backtrace(callstack, 1024);
    char** strs = backtrace_symbols(callstack, frames);
    int i;
    printf(FAIL_RED);
    for (i = 0; i < frames; i++)
    {
        printf("%s\n", strs[i]);
    }
    printf(FAIL_RESET);
    free(strs);
}

void fail()
{
    trace_stack();
    exit(EXIT_FAILURE);
}

void failwith(char* cause)
{
    printf(FAIL_RED);
    printf("%s\n", cause);
    printf(FAIL_RESET);
    trace_stack();
    exit(EXIT_FAILURE);
}
