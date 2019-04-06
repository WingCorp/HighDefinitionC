#include "lambda.h"
#include "fail.h"

#include <string.h>
#include <stdlib.h>
#include <varargs.h>

#pragma region INTERPRETER



char** get_words(char* code, int* out_counter)
{
    size_t len = strlen(code);

    if (len <= 4)
    {
        //Sounds crazy, but the shortest possible lambda, the id lambda is 'x => x'
        failwith("Cannot create a Lambda with a body shorter than 4 characters.\n");
    }
    
    
    int word_count = 1;
    int c;
    for (c = 0; c < len; c++) 
    {
        if (code[c] == ' ')
        {
            word_count++;
        }
    }

    char** words = malloc(sizeof(char*) * word_count);
    //Tokens:
    int saved_words = 0;
    int latest_word_pos = 0;    
    for (c = 0; c < len; c++)
    {
        if (code[c] == ' ')
        {
            int t;
            char* word = malloc(sizeof(char) * c);
            for (t = c - 1; t >= latest_word_pos; t--)
            {
                word[t - latest_word_pos] = code[t];
            }
            words[saved_words++] = word;
            latest_word_pos = c + 1;
        }
    }
    out_counter[0] = word_count;
    return words;
}

char** get_parameters(char** words, int word_count, int* out_counter)
{
    int arrow_index = -1;
    int i;
    for (i = 0; i < word_count; i++)
    {
        if (strcmp(words[i], "=>"))
        {
            arrow_index = i;
            break;
        }
    }
    if (arrow_index)
    {
        failwith("No arrow present in Lambda code");
    }
    char** parameters = malloc(sizeof(char*) * arrow_index);
    for (i = 0; i < arrow_index; i++)
    {
        parameters[i] = words[i];
    }
    return parameters;
}



Dynamic apply(Lambda* lambda, Dynamic param, ...)
{
    va_list args;
    va_start(args, param);
    char* code = lambda->code;
    int word_count[1];
    char** words = get_words(code, word_count);
    int param_count[1];
    char** parameters = get_parameters(words, word_count[0], param_count);
    //Tokenize the body, aka everything past the param_count.
    Dict* env = lambda->environment;
    int i;
    for(i = 0; i < param_count[0]; i++)
    {
        if (i == 0) {
            dict_put_s(env, parameters[i], param);
        }
        
        if (i < 0) {
            dict_put_s(env, parameters[i], va_arg(args, Dynamic));
        }
    }

    va_end(args);
}

#pragma endregion INTERPRETER

typedef struct _Lambda
{
    char* code;
    Dict* environment;
} Lambda;

Lambda* lambda(char* code, Dict* environment)
{
    Lambda* l = malloc(sizeof(Lambda));
    l->code = code;
    l->environment = environment;
    return l;
}