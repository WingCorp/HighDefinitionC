#include "str.h"
#include "./../fold/fold.h"
#include "./../iterator/iterator.h"
#include "./../math/math.h"
#include "./../fail/fail.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

char* str_concat(char* a, char* b)
{
    int len_a = strlen(a);
    int len_b = strlen(b);
    int combined_len = len_a + len_b;
    char* combined = malloc(sizeof(char) + sizeof(char) * combined_len);
    int i;
    for (i = 0; i < len_a; i++)
    {
        combined[i] = a[i];
    }
    for (i = i; i < combined_len; i++)
    {
        combined[i] = b[i - len_a];
    }
    combined[combined_len] = '\0';
    return combined;
}

char* str_join(char* infix, Iterator* iterator, char* (*to_string)(Dynamic))
{
    char** intermediate_results = malloc(sizeof(char*) * ((iterator_remaining(iterator) * 2) - 2));
    char* blank = "";
    if (!iterator_hasNext(iterator))
    {
        return blank;
    }
    char* acc = str_concat(blank, (*to_string)(iterator_next(iterator).value));
    intermediate_results[0] = acc;
    int i = 1;
    while (iterator_hasNext(iterator))
    {
        Dynamic element = iterator_next(iterator).value;
        char* element_str = (*to_string)(element);
        char* infix_element = str_concat(infix, element_str);
        intermediate_results[i++] = acc;
        intermediate_results[i++] = infix_element;
        acc = str_concat(acc, infix_element);
    }
    printf("%d\n", iterator_remaining(iterator));
    char* final = acc;
    printf("%d\n", i);
    int j;
    for (j = 1; j < i; j++)
    {
        free(intermediate_results[j]);
    }
    return final;
}

char* to_str(Dynamic d)
{
    char* out;
    switch (d.type)
    {
        case BOOL:
            if (bol(d))
            {
                out = "true";
            } else {
                out = "false";
            }
            break;
        case CHAR:
            out = malloc(sizeof(char));
            sprintf(out, "%c", chr(d));
            break;
        case INT:
            out = malloc(sizeof(char)*(ilog10(i32(d)) + 1));
            sprintf(out, "%d", i32(d));
            break;
        case STRING:
            out = str(d);
            break;
        case REFERENCE:
        {
            uintptr_t p = (uintptr_t) ref(d);
            out = malloc(sizeof(char)*(ilog10(p) + 1));
            sprintf(out, "%d", (int)p);
            break;
        }
        default:
            failwith("to_str only implemented for booleans, 32-bit integers, chars, strings and references.");
            break;
    }
    return out;
}
