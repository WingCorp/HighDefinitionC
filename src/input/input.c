#include <stdio.h>
#include <stdlib.h>

#include "./../queue/queue.h"
#include "./../str/str.h"

typedef struct _Input {
    char* buffer;
    FILE* file;
} Input;

Input* input_start(char* path, const int bufferSize)
{
    Input* inp = malloc(sizeof(Input));
    inp->buffer = malloc(sizeof(char) * bufferSize);
    inp->file = fopen(path, 'r');
    return inp;
}

Iterator* input_findNext(Input* input, Dynamic (*scanfun)(char*))
{
    Queue* q = list_empty();
    Option currentLineOpt = input_readLine(input);
    while (currentLineOpt.type != NONE)
    {
        queue_add(q, (*scanfun)(str(coerce(currentLineOpt))));
    }
    return queue_iterator(q);
}

Option input_readLine(Input* input)
{
    if (fscanf(input->file, "%s\n", &(input->buffer)) == EOF) {
        return none();
    };
    return some(dstr(str_copy(input->buffer)));
}

void input_end(Input* input)
{
    fclose(input->file);
    free(input->buffer);
    free(input);
}
