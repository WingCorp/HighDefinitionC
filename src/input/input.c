#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./../queue/queue.h"
#include "./../str/str.h"
#include "./../fail/fail.h"
#include "./../math/math.h"

typedef struct _Input
{
    FILE *file;
    char *buffer;
} Input;

Input* input_fromFile(FILE* file, int bufferSize)
{
    Input* inp = malloc(sizeof(Input));
    inp->file = file;
    inp->buffer = malloc(sizeof(char) * bufferSize);
    return inp;
}

Input *input_fromPath(char *path, int bufferSize)
{
    FILE* file = fopen(path, "r");
    if ((void *)file == NULL)
    {
        failwith(
            str_concat(
                str_concat("Could not open file at '", path),
                "', check that the file is not in use and that the path is correct."));
    }

    return input_fromFile(file, bufferSize);
}

Option input_readLine(Input *input)
{
    int result = fscanf(input->file, "%s\n", input->buffer);
    if (result == EOF)
    {
        return none();
    };
    return some(dstr(str_copy(input->buffer)));
}

Dynamic input_scan(Input *input, Dynamic (*scanFun)(char *))
{
    Option line = input_readLine(input);
    if (line.type == NONE)
    {
        failwith("input_scan failed: no lines in file!");
    }
    return (*scanFun)(str(coerce(line)));
}

Iterator *input_scanEnd(Input *input, Dynamic (*scanfun)(char *))
{
    Queue* q = queue_init(16);
    Option currentLineOpt = input_readLine(input);
    while (currentLineOpt.type != NONE)
    {
        queue_add(q, (*scanfun)(str(coerce(currentLineOpt))));
        currentLineOpt = input_readLine(input);
    }
    return queue_iterator(q);
}

void input_scanEndHandler(Input* input, void (*lineHandler)(char*))
{
    Option currentLineOpt = input_readLine(input);
    while (currentLineOpt.type != NONE)
    {
        (*lineHandler)(str(coerce(currentLineOpt)));
        currentLineOpt = input_readLine(input);
    }
}

Iterator *input_scanN(Input *input, Dynamic (*scanfun)(char *), int n)
{
    Queue* q = queue_init(n);
    Option currentLineOpt = input_readLine(input);
    int i;
    for (i = 0; i < n; i++)
    {
        if (currentLineOpt.type == NONE)
        {
            char *format = "input_scan_n() reach end of file after %d lines, but expected %d!";
            char *msgBuffer = malloc(sizeof(char) + sizeof(char) * (ilog10(n) + 1) * 2 + strlen(format));
            sprintf(msgBuffer, format, i, n);
            failwith(msgBuffer);
        }
        queue_add(q, (*scanfun)(str(coerce(currentLineOpt))));
        currentLineOpt = input_readLine(input);
    }
    return queue_iterator(q);
}

void input_scanNHandler(Input* input, void (*lineHandler)(char*), int n)
{
    Option currentLineOpt = input_readLine(input);
    int i;
    for (i = 0; i < n; i++)
    {
        if (currentLineOpt.type == NONE)
        {
            char *format = "input_scan_n() reach end of file after %d lines, but expected %d!";
            char *msgBuffer = malloc(sizeof(char) + sizeof(char) * (ilog10(n) + 1) * 2 + strlen(format));
            sprintf(msgBuffer, format, i, n);
            failwith(msgBuffer);
        }
        (*lineHandler)(str(coerce(currentLineOpt)));
        currentLineOpt = input_readLine(input);
    }
}

void input_end(Input *input)
{
    fclose(input->file);
    free(input->buffer);
    free(input);
}
