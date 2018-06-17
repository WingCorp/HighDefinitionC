#include "dynamic.h"

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

Dynamic di64(long val)
{
    return (Dynamic) { .type = LONG, .value = (DynValue) { .i64 = val } };
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

bool bol(Dynamic dyn)
{
    return dyn.value.bol;
}

char chr(Dynamic dyn)
{
    return dyn.value.chr;
}

int i32(Dynamic dyn)
{
    return dyn.value.i32;
}

long i64(Dynamic dyn)
{
    return dyn.value.i64;
}

float f32(Dynamic dyn)
{
    return dyn.value.f32;
}

double f64(Dynamic dyn)
{
    return dyn.value.f64;
}

void* ref(Dynamic dyn)
{
    return dyn.value.ref;
}

void* val(Dynamic dyn)
{
    void* toReturn;
    switch(dyn.type)
    {
        case BOOL:
            toReturn = &(dyn.value.bol);
            break;
        case CHAR:
            toReturn = &(dyn.value.chr);
            break;
        case INT:
            toReturn = &(dyn.value.i32);
            break;
        case LONG:
            toReturn = &(dyn.value.i64);
            break;
        case FLOAT:
            toReturn = &(dyn.value.f32);
            break;
        case DOUBLE:
            toReturn = &(dyn.value.f64);
            break;
        case REFERENCE:
            toReturn = dyn.value.ref;
            break;
    }
    return toReturn;
}
