#include "dynamic.h"
#include "./../fail/fail.h"

#include <stdlib.h>
#include <string.h>

char* dyntypes[12] = {"BOOL", "CHAR", "INT", "LONG", "UINT", "ULONG", "FLOAT", "DOUBLE", "REFERENCE", "STRING", "PAIR", "OPTION" };

Dynamic dbol(bool val)
{
    return (Dynamic) { .type = BOOL, .value = (DynValue) { .chr = val } };
}

Dynamic dchr(char val)
{
    return (Dynamic) { .type = CHAR, .value = (DynValue) { .chr = val } };
}

Dynamic di32(int val)
{
    return (Dynamic) { .type = INT, .value = (DynValue) { .i32 = val } };
}

Dynamic dui32(unsigned int val)
{
    return (Dynamic) { .type = UINT, .value = (DynValue) { .ui32 = val } };
}

Dynamic di64(long val)
{
    return (Dynamic) { .type = LONG, .value = (DynValue) { .i64 = val } };
}

Dynamic dui64(unsigned long val)
{
    return (Dynamic) { .type = ULONG, .value = (DynValue) { .ui64 = val } };
}

Dynamic df32(float val)
{
    return (Dynamic) { .type = FLOAT, .value = (DynValue) { .f32 = val } };
}

Dynamic df64(double val)
{
    return (Dynamic) { .type = DOUBLE, .value = (DynValue) { .f64 = val } };
}

Dynamic dstr(char* str)
{
    int len = strlen(str);
    char* heap_str = malloc(sizeof(char*) + sizeof(char*) * len);
    int i;
    for (i = 0; i < len; i++)
    {
        heap_str[i] = str[i];
    }
    heap_str[len + 1] = '\0';
    return (Dynamic) { .type = STRING, .value = (DynValue) { .str = heap_str } };
}

Dynamic dref(void* ref)
{
    return (Dynamic) { .type = REFERENCE, .value = (DynValue) { .ref = ref } };
}

Dynamic pair(Dynamic left, Dynamic right)
{
    Dynamic* lp = malloc(sizeof(Dynamic));
    lp->type = left.type;
    lp->value = left.value;
    Dynamic* rp = malloc(sizeof(Dynamic));
    rp->type = right.type;
    rp->value = right.value;
    return (Dynamic) 
    { 
        .type = PAIR, 
        .value = (DynValue) 
        { 
            .pair = (Pair)
            { 
                .left = lp,
                .right = rp
            } 
        }
    };
}

Dynamic fst(Dynamic pair)
{
    if (pair.type != PAIR)
    {
        failwithf("Call to fst() expected Dynamic of type PAIR, but was %s!\n", dyntypes[pair.type]);
    }
    return (*pair.value.pair.left);
}

DynType t_fst(Dynamic pair)
{
    if (pair.type != PAIR)
    {
        failwithf("Call to t_fst() expected Dynamic of type PAIR, but was %s!\n", dyntypes[pair.type]);
    }
    return pair.value.pair.left->type;
}

Dynamic snd(Dynamic pair)
{
    if (pair.type != PAIR)
    {
        failwithf("Call to snd() expected Dynamic of type PAIR, but was %s!\n", dyntypes[pair.type]);
    }
    return (*pair.value.pair.right);
}

DynType t_snd(Dynamic pair)
{
    if (pair.type != PAIR)
    {
        failwithf("Call to t_snd() expected Dynamic of type PAIR, but was %s!\n", dyntypes[pair.type]);
    }
    return pair.value.pair.right->type;
}

Dynamic none()
{
    return (Dynamic) { .type = OPTION, .value = (DynValue) { .option = (Option) { .type = NONE }}};
}

Dynamic some(Dynamic value)
{
    Dynamic* vp = malloc(sizeof(Dynamic));
    vp->type = value.type;
    vp->value = value.value;
    return (Dynamic) { .type = OPTION, .value = (DynValue) { .option = (Option) { .type = SOME, .value = vp }}};
}

Dynamic success(Dynamic opt, Dynamic (*optFunc)(Dynamic))
{
    if (opt.type != OPTION)
    {
        failwithf("success() can only be applied to an option, but was given an %s\n", dyntypes[opt.type]);
    }
    Option option = opt.value.option;    
    if (option.type == NONE)
    {
        return none();
    }
    Dynamic value = *option.value;
    return (*optFunc)(value);
}

Dynamic coerce(Dynamic opt)
{
    if (opt.type != OPTION)
    {
        failwithf("coerce() can only be applied to an option, but was given an %s\n", dyntypes[opt.type]);
    }
    Option option = opt.value.option;
    if (option.type == NONE)
    {
        failwith("Could not coerce value from empty option!\n");
    }
    return *option.value;
}

bool bol(Dynamic dyn)
{
    if (dyn.type != BOOL)
    {
        failwithf("Call to bol() expected Dynamic of type BOOL, but was %s!\n", dyntypes[dyn.type]);
    }
    return dyn.value.bol;
}

char chr(Dynamic dyn)
{
    if (dyn.type != CHAR)
    {
        failwithf("Call to chr() expected Dynamic of type CHAR, but was %s!\n", dyntypes[dyn.type]);
    }
    return dyn.value.chr;
}

int i32(Dynamic dyn)
{
    if (dyn.type != INT)
    {
        failwithf("Call to i32() expected Dynamic of type INT, but was %s!\n", dyntypes[dyn.type]);
    }
    return dyn.value.i32;
}

unsigned int ui32(Dynamic dyn)
{
    if (dyn.type != UINT)
    {
        failwithf("Call to ui32() expected Dynamic of type UINT, but was %s!\n", dyntypes[dyn.type]);
    }
    return dyn.value.ui32;
}

long i64(Dynamic dyn)
{
    if (dyn.type != LONG)
    {
        failwithf("Call to i64() expected Dynamic of type LONG, but was %s!\n", dyntypes[dyn.type]);
    }
    return dyn.value.i64;
}

unsigned long ui64(Dynamic dyn)
{
    if (dyn.type != ULONG)
    {
        failwithf("Call to ui64() expected Dynamic of type ULONG, but was %s!\n", dyntypes[dyn.type]);
    }
    return dyn.value.ui64;
}

float f32(Dynamic dyn)
{
    if (dyn.type != FLOAT)
    {
        failwithf("Call to f32() expected Dynamic of type FLOAT, but was %s!\n", dyntypes[dyn.type]);
    }
    return dyn.value.f32;
}

double f64(Dynamic dyn)
{
    if (dyn.type != DOUBLE)
    {
        failwithf("Call to f64() expected Dynamic of type DOUBLE, but was %s!\n", dyntypes[dyn.type]);
    }
    return dyn.value.f64;
}

char* str(Dynamic dyn)
{
    if (dyn.type != STRING)
    {
        failwithf("Call to str() expected Dynamic of type STRING, but was %s!\n", dyntypes[dyn.type]);
    }
    return dyn.value.str;
}

void* ref(Dynamic dyn)
{
    if (dyn.type != REFERENCE)
    {
        failwithf("Call to ref() expected Dynamic of type REFERENCE, but was %s!\n", dyntypes[dyn.type]);
    }
    return dyn.value.ref;
}

void delete(Dynamic dyn)
{
    if (dyn.type != REFERENCE || dyn.type != PAIR || dyn.type == STRING) {
        failwithf("Call to delete() expected Dynamic of type REFERENCE, STRING or PAIR, but was %s!\n", dyntypes[dyn.type]);
    }
    if (dyn.type == REFERENCE) {
        free(dyn.value.ref);
    }
    if (dyn.type == PAIR) {
        free(dyn.value.pair.left);
        free(dyn.value.pair.right);
    }
    if (dyn.type == OPTION) {
        free(dyn.value.option.value);
    }
    if (dyn.type == STRING)
    {
        free(dyn.value.str);
    }
}

char* typename(DynType type)
{
    return dyntypes[type];
}
