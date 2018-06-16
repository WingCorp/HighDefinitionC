#include "primitive.h"

Primitive pchr(char val)
{
    return (Primitive) { .type = CHAR, .value = (PrimValue) { .chr = val } };
}

Primitive pstr(char* val)
{
    return (Primitive) { .type = STRING, .value = (PrimValue) { .str = val } };
}

Primitive pi32(int val)
{
    return (Primitive) { .type = INT, .value = (PrimValue) { .i32 = val } };
}

Primitive pi64(long val)
{
    return (Primitive) { .type = LONG, .value = (PrimValue) { .i64 = val } };
}

Primitive pf32(float val)
{
    return (Primitive) { .type = FLOAT, .value = (PrimValue) { .f32 = val } };
}

Primitive pf64(double val)
{
    return (Primitive) { .type = DOUBLE, .value = (PrimValue) { .f64 = val } };
}

Primitive pref(void* ref)
{
    return (Primitive) { .type = REFERENCE, .value = (PrimValue) { .ref = ref } };
}

char chr(Primitive prim)
{
    return prim.value.chr;
}

char* str(Primitive prim)
{
    return prim.value.str;
}

int i32(Primitive prim)
{
    return prim.value.i32;
}

long i64(Primitive prim)
{
    return prim.value.i64;
}

float f32(Primitive prim)
{
    return prim.value.f32;
}

double f64(Primitive prim)
{
    return prim.value.f64;
}

void* ref(Primitive prim)
{
    return prim.value.ref;
}

void* val(Primitive prim)
{
    void* toReturn;
    switch(prim.type)
    {
        case CHAR:
            toReturn = &(prim.value.chr);
            break;
        case STRING:
            toReturn = &(prim.value.str);
            break;
        case INT:
            toReturn = &(prim.value.i32);
            break;
        case LONG:
            toReturn = &(prim.value.i64);
            break;
        case FLOAT:
            toReturn = &(prim.value.f32);
            break;
        case DOUBLE:
            toReturn = &(prim.value.f64);
            break;
        case REFERENCE:
            toReturn = prim.value.ref;
            break;
    }
    return toReturn;
}
