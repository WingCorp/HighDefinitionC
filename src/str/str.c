#include "str.h"
#include "./../fold/fold.h"
#include "./../iterator/iterator.h"
#include "./../array/array.h"
#include "./../math/math.h"
#include "./../fail/fail.h"
#include "./../stack/stack.h"
#include "./../foreach/foreach.h"


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

char* str_sub(char* s, int start, int end)
{
    int slen = strlen(s);
    if (start < 0 || start >= slen)
    {
        failwith("Illegal argument: Call to str_sub(), start out of bounds.");
    }
    if (end < 0 || end > slen)
    {
        failwith("Illegal argument: Call to str_sub(), end out of bounds");
    }    
    if (end < start)
    {
        failwith("Illegal argument: Call to str_sub() where start > end.");
    }
    char* out = malloc(sizeof(char) + sizeof(char) * (end - start));
    int i;
    int j = 0;
    for (i = start; i < end; i++)
    {
        out[j++] = s[i];
    }
    out[end - 1] = '\0';
    return out;
}

char* str_copy(char* s)
{
    int slen = strlen(s);
    char* copy = malloc(sizeof(char) + sizeof(char) * slen);
    int i;
    for (i = 0; i < slen; i++)
    {
        copy[i] = s[i];
    }
    copy[slen] = '\0';
    return copy;
}

bool str_contains(char* in, char* match)
{
    int mlen = strlen(match);
    int inlen = strlen(in);
    if (mlen > inlen)
    {
        return false;
    }
    int i;
    for (i = 0; i < inlen; i++)
    {
        int snp = 0;
        int j;
        for (j = 0; j < mlen; j++)
        {
            if (in[i + j] == match[j])
            {
                snp++;
            }
            if (snp == mlen)
            {
                return true;
            }
        }
    }
    return false;
}

void free_ref(Dynamic dyn)
{
    free(ref(dyn));
}

char* str_replace(char* in, char* old, char* new)
{
    // Stack* garbage = stack_init(2);
    char* out = "";
    int inlen = strlen(in);
    int oldlen = strlen(old);
    int i;
    int j;
    for (i = 0; i < inlen; i++)
    {
        int snp = 0;
        for (j = 0; j < oldlen; j++)
        {
            if (in[i + j] == old[j])
            {
                snp++;
            }
            if (snp == oldlen)
            {
                // char* ancientOut = out;
                out = str_concat(out, str_sub(in, i, j));
                // stack_push(garbage, dref(ancientOut));
                // char* oldOut = out;
                out = str_concat(out, new);
                // stack_push(garbage, dref(oldOut));
                i = i + (oldlen - 1);
                continue;
            }
        }
    }
    // Iterator* gi = stack_iterator(garbage);
    // foreach(gi, *free_ref);
    // stack_destroy(garbage);
    // iterator_destroy(gi);
    return out;
}

Dynamic str_concat_c_d(Dynamic s, Dynamic c)
{
    return dstr(str_concat_c(str(s), chr(c)));
}

char* str_concat_c(char* s, char c)
{
    if (c == '\0')
    {
        int len_s = strlen(s);
        char* copy = malloc(sizeof(char) + sizeof(char) * len_s);
        int i;
        for (i = 0; i < len_s; i++)
        {
            copy[i] = s[i];
        }
        copy[len_s] = '\0';
        return copy;
    }
    int len_s = strlen(s);
    char* combined = malloc(sizeof(char) + sizeof(char) * (len_s + 1));
    int i;
    for (i = 0; i < len_s; i++)
    {
        combined[i] = s[i];
    }
    combined[len_s] = c;
    combined[len_s + 1] = '\0';
    return combined;
}

Dynamic str_concat_d(Dynamic a, Dynamic b)
{
    return dstr(str_concat(str(a), str(b)));
}

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
    char* final = acc;
    free(intermediate_results[0]);
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

bool str_equals(char* strA, char* strB)
{
    return strcmp(strA, strB) == 0;
}

Iterator* str_iterator(char* string)
{
    int len = strlen(string);
    Array* arr = array_empty(len);
    int i;
    for (i = 0; i < len; i++)
    {
        array_setItem(arr, i, dchr(string[i]));
    }
    return array_iterator(arr);
}
