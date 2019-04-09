#include "dynamic.h"
#include "./../fail/fail.h"

#include <stdlib.h>

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
        failwith("Call to fst() expected Dynamic of type PAIR!");
    }
    return (*pair.value.pair.left);
}

DynType t_fst(Dynamic pair)
{
    if (pair.type != PAIR)
    {
        failwith("Call to t_fst() expected Dynamic of type PAIR!");
    }
    return pair.value.pair.left->type;
}

Dynamic snd(Dynamic pair)
{
    if (pair.type != PAIR)
    {
        failwith("Call to snd() expected Dynamic of type PAIR!");
    }
    return (*pair.value.pair.right);
}

DynType t_snd(Dynamic pair)
{
    if (pair.type != PAIR)
    {
        failwith("Call to t_snd() expected Dynamic of type PAIR!");
    }
    return pair.value.pair.right->type;
}

bool bol(Dynamic dyn)
{
    if (dyn.type != BOOL)
    {
        failwith("Call to bol() expected Dynamic of type BOOL!");
    }
    return dyn.value.bol;
}

char chr(Dynamic dyn)
{
    if (dyn.type != CHAR)
    {
        failwith("Call to chr() expected Dynamic of type CHAR!");
    }
    return dyn.value.chr;
}

int i32(Dynamic dyn)
{
    if (dyn.type != INT)
    {
        failwith("Call to i32() expected Dynamic of type INT!");
    }
    return dyn.value.i32;
}

unsigned int ui32(Dynamic dyn)
{
    if (dyn.type != UINT)
    {
        failwith("Call to ui32() expected Dynamic of type UINT!");
    }
    return dyn.value.ui32;
}

long i64(Dynamic dyn)
{
    if (dyn.type != LONG)
    {
        failwith("Call to i64() expected Dynamic of type LONG!");
    }
    return dyn.value.i64;
}

unsigned long ui64(Dynamic dyn)
{
    if (dyn.type != ULONG)
    {
        failwith("Call to ui64() expected Dynamic of type ULONG!");
    }
    return dyn.value.ui64;
}

float f32(Dynamic dyn)
{
    if (dyn.type != FLOAT)
    {
        failwith("Call to f32() expected Dynamic of type FLOAT!");
    }
    return dyn.value.f32;
}

double f64(Dynamic dyn)
{
    if (dyn.type != DOUBLE)
    {
        failwith("Call to f64() expected Dynamic of type DOUBLE!");
    }
    return dyn.value.f64;
}

void* ref(Dynamic dyn)
{
    if (dyn.type != REFERENCE)
    {
        failwith("Call to ref() expected Dynamic of type REFERENCE!");
    }
    return dyn.value.ref;
}

void delete(Dynamic dyn)
{
    if (dyn.type != REFERENCE || dyn.type != PAIR) {
        failwith("Call to delete() expected Dynamic of type REFERENCE or PAIR!");
    }
    if (dyn.type == REFERENCE) {
        free(dyn.value.ref);
    }
    if (dyn.type == PAIR) {
        free(dyn.value.pair.left);
        free(dyn.value.pair.right);
    }
}
