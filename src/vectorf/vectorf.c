#include "vectorf.h"

#include <stdlib.h>
#include <math.h>

#include "./../dynamic/dynamic.h"
#include "./../option/option.h"
#include "./../fail/fail.h"

Vectorf* vectorf_zero(int size)
{
    Vectorf* v = malloc(sizeof(Vectorf));
    v->size = size;
    v->values = malloc(sizeof(float)*size);
    int i;
    for (i = 0; i < size; i++)
    {
        v->values[i] = 0.0f;
    }
    return v;
}

Vectorf* vectorf_initFun(int size, float (*initFun(int)))
{
    Vectorf* v = malloc(sizeof(Vectorf));
    v->size = size;
    v->values = malloc(sizeof(float)*size);
    int i;
    for (i = 0; i < size; i++)
    {
        v->values[i] = *(initFun)(i);
    }
    return v;
}

Vectorf* vectorf_from(int size, float f, ...)
{
    va_list args;
    va_start(args, f);

    Vectorf* v = malloc(sizeof(Vectorf));
    v->size = size;
    v->values = malloc(sizeof(double)*size);
    v->values[0] = f;
    int i;
    for (i = 1; i < size; i++)
    {
        v->values[i] = va_arg(args, double);
    }
    va_end(args);
    return v;
}

Vectorf* vectorf_init(Iterator* iterator)
{
    Vectorf* v = malloc(sizeof(Vectorf));
    v->size = iterator_remaining(iterator);
    v->values = malloc(sizeof(float)*v->size);
    int i = 0;
    while (iterator_hasNext(iterator))
    {
        v->values[i] = f32(coerce(iterator_next(iterator)));
        i++;
    }
    return v;
}

void vectorf_destroy(Vectorf* vector)
{
    free(vector->values);
    free(vector);
}

float vectorf_get(Vectorf* v, int index)
{
    return v->values[index];
}

void vectorf_set(Vectorf* v, int index, float value)
{
    if (index < 0 || index >= v->size)
    {
        failwith("Illegal argument: index out of bounds");
    }
    v->values[index] = value;
}

void checkSizes(Vectorf* v, Vectorf* u)
{
    if (v->size != u->size)
    {
        failwith("Cannot perform operation on vectors of different sizes.");
    }
}

Vectorf* vectorf_add(Vectorf* v, Vectorf* u)
{
    checkSizes(v, u);
    Vectorf* res = vectorf_zero(v->size);
    int i;
    for (i = 0; i < v->size; i++)
    {
        res->values[i] = v->values[i] + u->values[i];
    }
    return res;
}

Vectorf* vectorf_scale(float scalar, Vectorf* v)
{
    Vectorf* res = vectorf_zero(v->size);
    int i;
    for (i = 0; i < v->size; i++)
    {
        res->values[i] = v->values[i] * scalar;
    }
    return res;
}

Vectorf* vectorf_sadd(float s, Vectorf* v, float t, Vectorf* u)
{
    checkSizes(v, u);
    Vectorf* res = vectorf_zero(v->size);
    int i;
    for (i = 0; i < v->size; i++)
    {
        res->values[i] = (s * v->values[i]) + (t * u->values[i]);
    }
    return res;
}

float vectorf_mag(Vectorf* v)
{
    float squareSum = 0.0f;
    int i;
    for (i = 0; i < v->size; i++)
    {
        squareSum += v->values[i] * v->values[i];
    }
    return sqrt(squareSum);
}

float vectorf_dot(Vectorf* v, Vectorf* u)
{
    checkSizes(v, u);
    float dotProduct = 0.0f;
    int i;
    for (i = 0; i < v->size; i++)
    {
        dotProduct += v->values[i] * u->values[i];
    }
    return dotProduct;
}

float vectorf_angle(Vectorf* v, Vectorf* u)
{
    float dot = vectorf_dot(v, u);
    float magProd = vectorf_mag(v) * vectorf_mag(u);
    return acos(dot / magProd);
}
