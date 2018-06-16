#ifndef DYNAMIC_H
#define DYNAMIC_H
/**
 * @brief Union type for emulating dynamic typing.
 * 
 * This is actually a monad... sort of.
 * 
 * @file dynamic.h
 * @author WingCorp
 * @date 2018-06-15
 */

#include <stdbool.h>

typedef enum _DynType 
{
    BOOL,
    CHAR,
    STRING,
    INT,
    LONG,
    FLOAT,
    DOUBLE,
    REFERENCE
} DynType;

typedef union _DynValue
{
    bool bol;
    char chr;
    char* str;
    int i32;
    long i64;
    float f32;
    double f64;
    void* ref;
} DynValue;

typedef struct _Dynamic
{
    DynType type;
    DynValue value;
} Dynamic;

Dynamic dbol(bool val);
Dynamic dchr(char val);
Dynamic dstr(char* val);
Dynamic di32(int val);
Dynamic di64(long i64);
Dynamic df32(float val);
Dynamic df64(double val);
Dynamic dref(void* ref);


//Shorthands to get the values of a dynamic.
//Be wary of segmentation fault.

bool bol(Dynamic dyn);
char chr(Dynamic dyn);
char* str(Dynamic dyn);
int i32(Dynamic dyn);
long i64(Dynamic dyn);
float f32(Dynamic dyn);
double f64(Dynamic dyn);
void* ref(Dynamic dyn);


/**
 * @brief Returns a pointer to whatever value is stored in the dynamic.
 * Useful, if you don't know what's inside the dynamic, which is not the way to use Dynamics.
 * 
 * @param dyn the dynamic to retrieve the value from.
 * @return void* a pointer to whatever value we've recovered.
 */
void* val(Dynamic dyn);

#endif
