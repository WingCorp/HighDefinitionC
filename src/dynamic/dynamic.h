#ifndef DYNAMIC_H
#define DYNAMIC_H
/**
 * @brief Union type for emulating dynamic typing.
 * 
 * @file dynamic.h
 * @author WingCorp
 * @date 2018-06-15
 */

#include <stdbool.h>

typedef struct _Dynamic Dynamic;

typedef enum _DynType 
{
    BOOL,
    CHAR,
    INT,
    LONG,
    UINT,
    ULONG,
    FLOAT,
    DOUBLE,
    REFERENCE,
    PAIR
} DynType;

typedef struct _Pair
{
    Dynamic* left;
    Dynamic* right;
} Pair;

typedef union _DynValue
{
    bool bol;
    char chr;
    int i32;
    unsigned int ui32;
    long i64;
    unsigned long ui64;
    float f32;
    double f64;
    void* ref;
    Pair pair;
} DynValue;

typedef struct _Dynamic
{
    DynType type;
    DynValue value;
} Dynamic;

/**
 * @brief Creates a new pair from two dynamic values.
 * 
 * @param left The left value.
 * @param right The right value.
 * @return Pair The constructed pair.
 */
Dynamic pair(Dynamic left, Dynamic right);

/**
 * @brief Get the first value (leftmost) stored in a pair.
 * 
 * @param pair The pair.
 * @return Dynamic The first value.
 */
Dynamic fst(Dynamic pair);

/**
 * @brief Returns the type of the first value of the pair.
 * 
 * @param pair The pair.
 * @return DynType The type of the first value.
 */
DynType t_fst(Dynamic pair);

/**
 * @brief Get the second value (rightmost) stored in a pair.
 * 
 * @param pair The pair.
 * @return Dynamic The second value.
 */
Dynamic snd(Dynamic pair);

/**
 * @brief Return the type of the second value of the pair.
 * 
 * @param pair The pair.
 * @return DynType The type of the second value.
 */
DynType t_snd(Dynamic pair);


Dynamic dbol(bool val);
Dynamic dchr(char val);
Dynamic di32(int val);
Dynamic dui32(unsigned int val);
Dynamic di64(long i64);
Dynamic dui64(unsigned long ui64);
Dynamic df32(float val);
Dynamic df64(double val);
Dynamic dref(void* ref);


//Shorthands to get the values of a dynamic.
//Be wary of segmentation fault.

bool bol(Dynamic dyn);
char chr(Dynamic dyn);
int i32(Dynamic dyn);
unsigned int ui32(Dynamic dyn);
long i64(Dynamic dyn);
unsigned long ui64(Dynamic dyn);
float f32(Dynamic dyn);
double f64(Dynamic dyn);
void* ref(Dynamic dyn);

/**
 * @brief Delete a dynamic if it is on the heap.
 *        Frees the memory held by a dynamic reference or a dynamic pair.
 * 
 * @param dyn A dynamic holding a reference or a pair-dynamic.
 */
void delete(Dynamic dyn);

#endif
