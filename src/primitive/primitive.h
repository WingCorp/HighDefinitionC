#ifndef PRIMITIVE_H
#define PRIMITIVE_H
/**
 * @brief Union type for wrapping primitive types.
 * 
 * @file primitive.h
 * @author WingCorp
 * @date 2018-06-15
 */

typedef enum _PrimType 
{
    CHAR,
    STRING,
    INT,
    LONG,
    FLOAT,
    DOUBLE,
    REFERENCE
} PrimType;

typedef union _PrimValue
{
    char chr;
    char* str;
    int i32;
    long i64;
    float f32;
    double f64;
    void* ref;
} PrimValue;

typedef struct _Primitive
{
    PrimType type;
    PrimValue value;
} Primitive;

Primitive pchr(char val);
Primitive pstr(char* val);
Primitive pi32(int val);
Primitive pi64(long i64);
Primitive pf32(float val);
Primitive pf64(double val);
Primitive pref(void* ref);


//Shorthands to get the values of a primitive.
//Be wary of segmentation fault.

char chr(Primitive prim);
char* str(Primitive prim);
int i32(Primitive prim);
long i64(Primitive prim);
float f32(Primitive prim);
double f64(Primitive prim);
void* ref(Primitive prim);


/**
 * @brief Returns a pointer to whatever value is stored in the primitive.
 * Useful, if you don't know what's inside the primitive, which is not the way to use Primitives.
 * 
 * @param prim the primitive to retrieve the value from.
 * @return void* a pointer to whatever value we've recovered.
 */
void* val(Primitive prim);

#endif
