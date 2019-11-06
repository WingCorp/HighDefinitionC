#include "str.h"
#include "./../fail/fail.h"
#include "./../math/math.h"
#include "./../array/array.h"
#include "./../queue/queue.h"
#include "./../fold/fold.h"
#include "./../iterator/iterator.h"

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
        failwithf("Illegal argument: Call to str_sub(), start of %d was out of bounds [1;%d[.\n", start, slen);
    }
    if (end < 0 || end > slen)
    {
        failwithf("Illegal argument: Call to str_sub(), end of %d out of bounds [1;%d[.\n", end, slen);
    }    
    if (end < start)
    {
        failwithf("Illegal argument: Call to str_sub() where start of %d > end of %d.\n", start, end);
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
    return strstr(in, match) != NULL;
}

void free_ref(Dynamic dyn)
{
    free(ref(dyn));
}

char* str_replace(char* orig, char* rep, char* with)
{
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return str_copy(orig);
    len_rep = strlen(rep);
    if (len_rep == 0)
        return str_copy(orig); // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; (tmp = strstr(ins, rep)); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return str_copy(orig);

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
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
    free(intermediate_results);
    return final;
}

Array* str_split(char* str, char* delim)
{
    Queue* batches = queue_init(2);
    int len = strlen(str);
    char sub = (char) 26;
    char* replaced = str_replace(str, delim, str_concat_c("", sub));
    int start = 0;
    int i;
    for (i = 0; i < len; i++)
    {
        char c = replaced[i];
        if (c == sub)
        {
            char* batch = str_sub(replaced, start, i);
            queue_add(batches, dstr(batch));
            start = i + 1;
        }
    }
    return array_initFromIterator(queue_iterator(batches));
}

char* str_trim(char* str)
{
    int i;
    int len = strlen(str);
    int regular_chars = 0;
    for (i = 0; i < len; i++)
    {
        if (str[i] != ' ' || str[i] != '\n' || str[i] != '\t')
        {
            regular_chars++;
        }
    }
    char* out = malloc(sizeof(char) + sizeof(char) * regular_chars);
    int j = 0;
    for (i = 0; i < len; i++)
    {
        if (str[i] != ' ' || str[i] != '\n' || str[i] != '\t')
        {
            out[j++] = str[i];
        }
    }
    out[j] = '\0';
    return out;
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
            out = malloc(sizeof(char) + sizeof(char));
            sprintf(out, "%c", chr(d));
            break;
        case INT:
            out = malloc(sizeof(char) + sizeof(char)*(ilog10(i32(d)) + 1));
            sprintf(out, "%d", i32(d));
            break;
        case STRING:
            out = str(d);
            break;
        case REFERENCE:
        {
            uintptr_t p = (uintptr_t) ref(d);
            out = malloc(sizeof(char) + sizeof(char)*(ilog10(p) + 1));
            sprintf(out, "%d", (int)p);
            break;
        }
        default:
            failwith("to_str only implemented for booleans, 32-bit integers, chars, strings and references.\n");
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
