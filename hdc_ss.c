#include <stdbool.h>

#include <string.h>

#include <stdio.h>

#include <stdarg.h>

#include <stdlib.h>

#include <execinfo.h>

#pragma region HDC

#ifndef HDC
#define HDC

/**
 * @file hdc.h
 * @author Jon Voigt Tøttrup (jvoi@itu.dk)
 * @brief The HighDefinitionC library, ready for action.
 * @version 0.1
 * @date 2018-10-30
 * 
 * @copyright WingCorp (c) 2018
 * 
 */


#define long long long

#ifndef FAIL_H
#define FAIL_H


/**
 * @brief The fail-module.
 * 
 * @file fail.h
 * @author WingCorp
 * @date 2018-06-19
 */

/**
 * @brief Exit the program with an error value.
 */
void fail();

/**
 * @brief Print the error cause and exit the program with an error value.
 * 
 * @param cause the cause to print before exiting.
 */
void failwith(char* cause);

#endif

#define FAIL_RED "\x1b[31m"
#define FAIL_RESET "\x1b[0m"

void* callstack[1024];

void trace_stack()
{
    int frames = backtrace(callstack, 1024);
    char** strs = backtrace_symbols(callstack, frames);
    int i;
    printf(FAIL_RED);
    for (i = 0; i < frames; i++)
    {
        printf("%s\n", strs[i]);
    }
    printf(FAIL_RESET);
    free(strs);
}

void fail()
{
    trace_stack();
    exit(EXIT_FAILURE);
}

void failwith(char* cause)
{
    printf(FAIL_RED);
    printf("%s\n", cause);
    printf(FAIL_RESET);
    trace_stack();
    exit(EXIT_FAILURE);
}

#ifndef MATH
#define MATH
/***
 * The math module.
 * 
 **/

long math_longAbs(long l);
int math_intAbs(int i);

double math_doubleAbs(double d);
float math_floatAbs(float f);

int ilog10(int i);

#endif
/**
 * Math
 * @brief An attempt at a simple math module in C.
 * 
 * @file math.c
 * @author Jon Voigt Tøttrup
 * @date 2018-06-14
 */

double math_epsilon = 0.0000001;

long math_longAbs(long l) 
{
    if(l < 0) 
    {
        return l * -1;
    }
    else return l;
}

int math_intAbs(int i) 
{
    return (int) math_longAbs((long) i);
}

double math_doubleAbs(double d)
{
    if(d + math_epsilon < 0)
    {
        return d * -1;
    }
    else return d;
}

float math_floatAbs(float f)
{
    return (float) math_doubleAbs((double) f);
}

int ilog10(int i)
{
    return 
        (i > 999999999) ? 9 : (i >= 99999999) ? 8 :
        (i > 9999999) ? 7 : (i > 999999) ? 6 : (i > 99999) ? 5 : 
        (i > 9999) ? 4 : (i > 999) ? 3 : (i > 99) ? 2 : (i > 9) ? 1 : 0;
}

#ifndef DYNAMIC_H
#define DYNAMIC_H
/**
 * @brief Union type for emulating dynamic typing.
 * 
 * @file dynamic.h
 * @author WingCorp
 * @date 2018-06-15
 */


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

#ifndef OPTION_H
#define OPTION_H
/**
 * @brief The option monad
 * 
 * @file option.h
 * @author WingCorp
 * @date 2018-06-15
 */


typedef enum _OptionType
{
    NONE,
    SOME
} OptionType;

typedef struct _Option
{
    OptionType type;
    Dynamic value;
} Option;

/**
 * @brief The 'none' return-function.
 * 
 * @return Option 
 */
Option none();

/**
 * @brief The 'some' return-function
 * 
 * @param value 
 * @return Option 
 */
Option some(Dynamic value);

/**
 * @brief Takes an option and a function 
 *        that takes the result of the given option
 *        and applies the option to the given function
 *        if the option was some.
 *
 * @param opt an Option value.
 * @param optFunc a function of signature: Option <name>(Dynamic <arg>); 
 * @return Option an option value.
 */
Option success(Option opt, Option (*optFunc)(Dynamic));

/**
 * @brief Coerces an option to its value.
 *        Might cause a failure, if no value is present.
 * 
 * @param opt the option to coerce.
 * @return Dynamic the value to find;
 */
Dynamic coerce(Option opt);

#endif

Option none()
{
    return (Option) { .type = NONE };
}

Option some(Dynamic value)
{
    return (Option) { .type = SOME, .value = value };
}

Option success(Option opt, Option (*optFunc)(Dynamic))
{
    if (opt.type == NONE)
    {
        return none();
    }
    return (*optFunc)(opt.value);
}

Dynamic coerce(Option opt)
{
    if (opt.type == NONE)
    {
        failwith("Could not coerce value from empty option!\n");
    }
    return opt.value;
}
#ifndef COMPARABLE_H
#define COMPARABLE_H

/**
 * @file comparable.h
 * @author Jon Voigt Tøttrup (jvoi@itu.dk)
 * @brief A wrapper for Dynamics that allow them to be compared,
 *        given, that they are the same type.
 * @version 0.1
 * @date 2018-11-01
 * 
 * @copyright WingCorp (c) 2018
 * 
 */


typedef struct _Comparable
{
    Dynamic value;
} Comparable;

/**
 * @brief Creates a Comparable from a Dynamic
 * 
 * Fails if the dynamic cannot be converted to a Comparable.
 * 
 * @param dynamic The dynamic value.
 * @return Comparable The value, wrapped in a Comparable.
 */
Comparable comparable(Dynamic dynamic);

/**
 * @brief Compares two Comparables
 * 
 * @param a 
 * @param b 
 * @return int 0 if a == b, 1 if a > b, -1 if a < b
 */
int compare(Comparable a, Comparable b);

#endif
/**
 * @file comparable.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2018-11-01
 * 
 * @copyright Copyright (c) 2018
 * 
 */


Comparable comparable(Dynamic dynamic)
{
    switch(dynamic.type)
    {
        case BOOL:
            failwith("Cannot construct comparable from a BOOL value.\n");
            break;
        case REFERENCE:
            failwith("Cannot construct comparable from a REFERENCE value.\n");
            break;
        default:
            break;
    }
    return (Comparable) { .value = dynamic};
}

int compare(Comparable a, Comparable b)
{
    if(a.value.type != b.value.type)
    {
        failwith("Cannot compare comparables of different dynamic types!\n");
    }
    Dynamic aVal = a.value;
    Dynamic bVal = b.value;

    switch(a.value.type)
    {
        case CHAR:
            if (chr(aVal) == chr(bVal)) 
            {
                return 0;
            } 
            else
            {
                return (chr(aVal)) > (chr(bVal)) ? 1 : -1;
            }
        case INT:
            if (i32(aVal) == i32(bVal)) 
            {
                return 0;
            } 
            else
            {
                return (i32(aVal)) > (i32(bVal)) ? 1 : -1;
            }
        case FLOAT:
            if (f32(aVal) == f32(bVal)) 
            {
                return 0;
            } 
            else
            {
                return (f32(aVal)) > (f32(bVal)) ? 1 : -1;
            }
        
        case DOUBLE:
            if (f64(aVal) == f64(bVal)) 
            {
                return 0;
            } 
            else
            {
                return (f64(aVal)) > (f64(bVal)) ? 1 : -1;
            }

        case LONG:
            if (i64(aVal) == i64(bVal)) 
            {
                return 0;
            } 
            else
            {
                return (i64(aVal)) > (i64(bVal)) ? 1 : -1;
            }
        
        default:
            failwith("Cannot create comparable from unknown dynamic type!\n");
            break;
    }
    int f = 0;
    return 0 / f; //So, we have to return an integer, but we should not.
    //We should never reach these statements, but if we do, I've made a terrible mistake somewhere.
}


#ifndef HASH_H
#define HASH_H
/**
 * @file hash.h
 * @author Jon Voigt Tøttrup (jvoi@itu.dk)
 *
 * @brief A module responisble for hashing things
 * @version 0.1
 * @date 2018-11-08
 *
 * @copyright WingCorp (c) 2018
 * 
 */


unsigned long hash(char* s);

#endif
/**
 * @brief Hashes a char* to an unsigned long.
 * K&R's hash function.
 *
 * @param s A string.
 * @return unsigned long A hash of the string.
 */
unsigned long hash(char* s)
{
    unsigned long hash = 5381;
    int c;

    while((c = *s++))
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

#ifndef ITERATOR_H
#define ITERATOR_H


typedef struct _Iterator Iterator;

/**
 * @brief Initializes a new iterator from a Dynamic pointer.
 * 
 * @param data The data to iterate from.
 * @param length The length of the data.
 * @return Iterator An Iterator struct.
 */
Iterator* iterator_init_eager(Dynamic* data, int length);

/**
 * @brief Initializes a new iterator from an int -> Dynamic function.
 * 
 * @param nextFun A function that takes the position of the iterator
 *                and returns the corresponding Dynamic.
 * @param length The length of the iterator.
 * @return Iterator* An Iterator struct.
 */
Iterator* iterator_init_lazy(Dynamic (*nextFun)(int), int length);

/**
 * @brief Whether an iterator holds another value.
 * 
 * @param iterator 
 * @return bool a bool value.
 */
bool iterator_hasNext(Iterator* iterator);

/**
 * @brief Retrieves the next value from the iterator.
 * 
 * @param iterator the iterator to get the value from.
 * @return Option some if there is a value, none if there isn't.
 */
Option iterator_next(Iterator* iterator);

/**
 * @brief How many entries that remain in the iterator.
 * 
 * @param iterator 
 * @return int 
 */
int iterator_remaining(Iterator* iterator);

/**
 * @brief Resets iterator.
 * 
 * @param iterator the iterator.
 */
void iterator_reset(Iterator* iterator);

/**
 * @brief Destroys the iterator and the values that the iterator is reading from.
 * 
 * @param iterator the iterator to destroy.
 */
void iterator_destroy(Iterator* iterator);

#endif

typedef union _Source
{
    Dynamic* data;
    Dynamic (*nextFun)(int);
} Source;

typedef enum _Type
{
    EAGER,
    LAZY
} Type;

typedef struct _Iterator
{
    int position;
    int length;
    Source* source;
    Type type;
} Iterator;

Iterator* iterator_init_eager(Dynamic* data, int length)
{
    Iterator* iterator = malloc(sizeof(Iterator));
    iterator->position = 0;
    iterator->length = length;
    iterator->type = EAGER;
    iterator->source = malloc(sizeof(Source));
    iterator->source->data = data;
    return iterator;
}

Iterator* iterator_init_lazy(Dynamic (*nextFun)(int), int length)
{
    Iterator* iterator = malloc(sizeof(Iterator));
    iterator->position = 0;
    iterator->length = length;
    iterator->type = LAZY;
    iterator->source = malloc(sizeof(Source));
    iterator->source->nextFun = nextFun;
    return iterator;
}

bool iterator_hasNext(Iterator* iterator)
{
    return iterator->position < iterator->length;
}

Option iterator_next(Iterator* iterator)
{
    if(iterator->position < iterator->length)
    {
        Dynamic toReturn;
        switch(iterator->type)
        {
            case EAGER:
                toReturn = iterator->source->data[iterator->position];
                break;
            case LAZY:
                toReturn = iterator->source->nextFun(iterator->position);
                break;
        }
        iterator->position += 1;
        return some(toReturn);
    }
    else
    {
        return none();
    }
}

int iterator_remaining(Iterator* iterator)
{
    return iterator->length - iterator->position;
}

void iterator_reset(Iterator* iterator)
{
    iterator->position = 0;
}

void iterator_destroy(Iterator* iterator)
{
    free(iterator);
}

#ifndef FOREACH_H
#define FOREACH_H

/**
 * @brief The foreach function.
 * 
 * @file foreach.h
 * @author WingCorp
 * @date 2018-06-16
 */


/**
 * @brief Performs an action on every value from an iterator using an action function.
 *  
 * @param iterator the iterator to loop through.
 * @param action the action function, must have signature: void <name>(Dynamic <arg>)
 */
void foreach(Iterator* iterator, void (*action) (Dynamic));

#endif
void foreach(Iterator* iterator, void (*action) (Dynamic))
{
    while (iterator_hasNext(iterator))
    {
        (*action)(iterator_next(iterator).value);
    }
    iterator_reset(iterator);
}
#ifndef MAP_H
#define MAP_H

/**
 * @brief The 'map' monad, as known from FP.
 * 
 * @file map.h
 * @author WingCorp
 * @date 2018-06-16
 */


/**
 * @brief maps every value from an iterator with a mapper function.
 * 
 * ATTENTION: this function will allocate memory to the mapped values.
 * To free memory of old values or of mapped values, use iterator_destroy.
 * 
 * @param iterator the iterator to map.
 * @param mapper the mapper function, must have signature: Dynamic <name>(Dynamic <arg>)
 * @return Iterator a new iterator for the new values.
 */
Iterator* map(Iterator* iterator, Dynamic (*mapper) (Dynamic));

#endif

Iterator* map(Iterator* ite, Dynamic (*mapper) (Dynamic))
{
    int size = iterator_remaining(ite);
    Dynamic* mappedValues = malloc(size * sizeof(Dynamic));
    int i = 0;
    while(iterator_hasNext(ite))
    {
        mappedValues[i] = (*mapper)(iterator_next(ite).value);
        i += 1;
    }
    iterator_reset(ite);
    return iterator_init_eager(mappedValues, size);
}

#ifndef FOLD_H
#define FOLD_H

/**
 * @brief The 'fold' monad, as known from FP.
 * 
 * @file fold.h
 * @author WingCorp
 * @date 2018-06-16
 */


/**
 * @brief Folds over every entry in the iterator.
 * 
 * @param iterator the iterator to fold over..
 * @param initialState the initial state to fold onto.
 * @param folder the folder function with the signature Dynamic folder(Dynamic acc, Dynamic i)
 * @return Dynamic the final state.
 */
Dynamic fold(Iterator* iterator, Dynamic initialState, Dynamic (*folder) (Dynamic, Dynamic));

#endif

Dynamic fold(Iterator* iterator, Dynamic initialState, Dynamic (*folder) (Dynamic, Dynamic))
{
    Dynamic current_state = initialState;
    while (iterator_hasNext(iterator))
    {
        Dynamic currentValue = iterator_next(iterator).value;
        current_state = (*folder)(current_state, currentValue);
    }
    iterator_reset(iterator);
    return current_state;
}


#ifndef ARRAY_H
#define ARRAY_H

/**
 * @brief Wrapper for dynamic pointers, so that they include length as well.
 * 
 * @file array.h
 * @author WingCorp
 * @date 2018-06-17
 */


typedef struct _Array Array;

/**
 * @brief Initializes an empty array of a given length.
 * 
 * @param length 
 * @return Array* 
 */
Array* array_empty(int length);

/**
 * @brief Initializes the array with a Dynamic* and a specified length.
 * 
 * Copies all given Dynamic values to a new memory space on heap.
 * 
 * @param dynamics A Dynamic pointer to a primitive array of dynamics.
 * @param length the length of the dynamic array.
 * @return Array* an Array*
 */
Array* array_init(Dynamic* dynamics, int length);

/**
 * @brief Retrieves the length of the array.
 * 
 * @param array the array.
 * @return int the length,
 */
int array_length(Array* array);

/**
 * @brief Get an item from the array.
 * 
 * @param array the array.
 * @param index the index for the array.
 * @return Option an option value, some if index < length and index > 0
 *         else returns none.
 */
Option array_item(Array* array, int index);


/**
 * @brief Sets an item in the array to a new value.
 * 
 * @param array the array.
 * @param index the index to modify.
 * @param value the new value.
 */
void array_setItem(Array* array, int index, Dynamic value);

/**
 * @brief Creates an iterator from the array data.
 * 
 * @param array 
 * @return Iterator* 
 */
Iterator* array_iterator(Array* array);

/**
 * @brief Creates a new array from an iterator (consumes the iterator).
 * 
 * @param it the iterator to create the array from.
 * @return Array* 
 */
Array* array_initFromIterator(Iterator* it);

/**
 * @brief Initialize array with function.
 * 
 * @param length the length of the array.
 * @param initFunc function that inserts dynamic values into the array, based on the index.
 * @return Array* the new array.
 */
Array* array_initFromFunc(int length, Dynamic (*initFunc)(int));

/**
 * @brief Destroys the array, freeing the memory it held.
 * 
 * @param array an array.
 */
void array_destroy(Array* array);

#endif

typedef struct _Array
{
    Dynamic* data;
    int length;
} Array;

Array* array_empty(int length)
{
    if(length <= 0)
    {
        failwith("Cannot initialize array of length <= 0!");
    }
    Array* array = malloc(sizeof(Array));
    array->data = malloc(sizeof(Dynamic) * length);
    array->length = length;
    return array;
}

Array* array_init(Dynamic* dynamics, int length)
{
    Array* array = array_empty(length);
    int i;
    //Copy the values.
    for (i = 0; i < length; i++)
    {
        array->data[i] = dynamics[i];
    }
    return array;
}

int array_length(Array* array)
{
    return array->length;
}

Option array_item(Array* array, int index)
{
    if (index >= 0 && index < array->length)
    {
        return some(array->data[index]);
    }
    else return none();
}

void array_setItem(Array* array, int index, Dynamic value)
{
    if (index >= 0 && index < array->length)
    {
        array->data[index] = value;
    }
    else
    {
        failwith("Cannot set item to index that is out of bounds!");
    }
}

Iterator* array_iterator(Array* array)
{
    return iterator_init_eager(array->data, array->length);
}

Array* array_initFromIterator(Iterator* it)
{
    Array* array = array_empty(iterator_remaining(it));
    int i = 0;
    while(iterator_hasNext(it))
    {
        array->data[i] = iterator_next(it).value;
        i += 1;
    }
    return array;
}

Array* array_initFromFunc(int length, Dynamic (*initFunc)(int))
{
    Array* array = array_empty(length);
    int i;
    for (i = 0; i < length; i++)
    {
        array->data[i] = (*initFunc)(i);
    }
    return array;
}

void array_destroy(Array* array)
{
    free(array->data);
    free(array);
}
#ifndef STACK_H
#define STACK_H

/**
 * @brief A resizable stack for working with dynamics.
 * 
 * @file stack.h
 * @author WingCorp
 * @date 2018-06-15
 */


typedef struct _Stack Stack;

/**
 * @brief Initializes a new Stack data structure.
 * 
 * @param initialCap the initial capacity of the stack.
 * @return Stack* a pointer to the new stack.
 */
Stack* stack_init(int initialCap);

/**
 * @brief Frees the memory occupied by a Stack data structure.
 * 
 * @param stack the stack to destroy.
 */
void stack_destroy(Stack* stack);

/**
 * @brief Pushes a value on the stack.
 * 
 * @param stack the stack to push the value on.
 * @param dyn the dynamic to put on the stack.
 */
void stack_push(Stack* stack, Dynamic dyn);

/**
 * @brief Pops a value from the stack.
 * 
 * @param stack the stack to pop from.
 * @return Option the value from the stack, if any.
 */
Option stack_pop(Stack* stack);

/**
 * @brief Determines number of values currently stored in the stack.
 * 
 * @param stack the stack to check.
 * @return int the number of values in the stack.
 */
int stack_size(Stack* stack);

/**
 * @brief Determines the capacity of the stack.
 * 
 * @param stack the stack to check.
 * @return int how many values the stack can hold, before reallocating.
 */
int stack_capacity(Stack* stack);

/**
 * @brief Trims the capacity of the stack to just the values.
 * 
 */
void stack_trim(Stack* stack);

/**
 * @brief Gets an iterator from the current stack.
 * 
 * @return Iterator an iterator.
 */
Iterator* stack_iterator(Stack* stack);

/**
 * @brief Maps every entry in the stack to a new stack using a mapper function.
 * 
 * @param stack the stack to map.
 * @param mapper the mapper function.
 * @return Stack* the mapped stack.
 */
Stack* stack_map(Stack* stack, Dynamic (*mapper) (Dynamic));

/**
 * @brief Folds over every entry in the stack.
 * 
 * @param stack the stack to fold.
 * @param state the initial state to fold onto.
 * @param folder the folder function with the signature Dynamic folder(Dynamic acc, Dynamic i)
 * @return Dynamic the final state.
 */
Dynamic stack_fold(Stack* stack, Dynamic state, Dynamic (*folder) (Dynamic, Dynamic));

#endif
/**
 * @brief A resizable stack for working with dynamics.
 * 
 * @file stack.c
 * @author WingCorp
 * @date 2018-06-15
 */


typedef struct _Stack
{
    int capacity;
    int size;
    Dynamic* dynamics;
} Stack;

Stack* stack_init(int initialCap)
{
    Stack* stack = malloc(sizeof(Stack));
    stack->capacity = initialCap;
    stack->size = 0;
    stack->dynamics = malloc(sizeof(Dynamic) * initialCap);
    return stack;
}

void stack_destroy(Stack* stack)
{
    free(stack->dynamics);
    free(stack);
}

void reallocStack(Stack* stack, float sizeChange)
{
    int oldCap = stack->capacity;
    int newCap = oldCap * sizeChange;
    stack->dynamics = realloc(stack->dynamics, newCap * sizeof(Dynamic));
    stack->capacity = newCap;
}

void increaseCapacity(Stack* stack)
{
    reallocStack(stack, 2.5);
}

void stack_push(Stack* stack, Dynamic dyn)
{
    int top = stack->size;
    if (top + 1 == stack->capacity)
    {
        increaseCapacity(stack);
    }
    stack->dynamics[top] = dyn;
    stack->size += 1;
}

void decreaseCapacity(Stack* stack)
{
    reallocStack(stack, 0.5);
}

Option stack_pop(Stack* stack)
{
    if (stack->size == 0) {
        return none();
    }
    int top = stack->size - 1;
    Dynamic toReturn = stack->dynamics[top];
    stack->size -= 1;
    if (stack->size * 2 < stack->capacity)
    {
        decreaseCapacity(stack);
    }    
    return some(toReturn);
}

int stack_size(Stack* stack)
{
    return stack->size;
}

int stack_capacity(Stack* stack)
{
    return stack->capacity;
}

void stack_trim(Stack* stack)
{
    int newCap = stack->size;
    stack->dynamics = realloc(stack->dynamics, newCap * sizeof(Dynamic));
    stack->capacity = newCap;
}

Iterator* stack_iterator(Stack* stack)
{
    return iterator_init_eager(stack->dynamics, stack->size);
}

Stack* stack_map(Stack* stack, Dynamic (*mapper) (Dynamic))
{
    Stack* mappedStack = stack_init(stack->size);
    int i;
    for (i = 0; i < stack->size; i++){
        Dynamic currentValue = stack->dynamics[i];
        Dynamic mappedValue = (*mapper)(currentValue);
        stack_push(mappedStack, mappedValue);
    }
    return mappedStack;
}

Dynamic stack_fold(Stack* stack, Dynamic state, Dynamic (*folder) (Dynamic, Dynamic))
{
    Dynamic currentState = state;
    int i;
    for (i = 0; i < stack->size; i++)
    {
        Dynamic currentValue = stack->dynamics[i];
        currentState = (*folder)(currentState, currentValue);
    }
    return currentState;
}
#ifndef LIST_H
#define LIST_H

/**
 * @brief Immutable linked list module.
 * 
 * @file linkedList.h
 * @author your name
 * @date 2018-06-17
 */


typedef struct _List List;

/**
 * @brief Creates a new, empty list.
 * 
 * @return List* an empty list.
 */
List* list_empty();


/**
 * @brief Cons a new value to the end of the list and return the list.
 * 
 * @param list the list to cons
 * @param val the value to cons
 * @return List the new list
 */
List* list_cons(List* list, Dynamic val);

/**
 * @brief Concatenates two lists together.
 * 
 * @param listA the first list
 * @param listB the second list
 * @return List the result of the concatenation.
 */
List* list_concatenate(List* listA, List* listB);

/**
 * @brief Retrieves the head-element from the list.
 * 
 * @param list the list to take the head from.
 * @return Option the head element.
 */
Option list_head(List* list);

/**
 * @brief Retrieves the tail of the list.
 * 
 * @param list the list.
 * @return List the tail of the list.
 */
List* list_tail(List* list);

/**
 * @brief Retrieves the item at given index in given list.
 * 
 * @param list the list
 * @param index the index
 * @return Option some item, if any
 */
Option list_item(List* list, int index);

/**
 * @brief Retrieves the number of elements in the list.
 * 
 * @param list the list.
 * @return int the length of the list in number of elements.
 */
int list_length(List* list);

/**
 * @brief Deallocs the given list.
 * 
 * @param list a list.
 */
void list_destroy(List* list);

/**
 * @brief Creates a new list from an iterator (consumes the iterator).
 * 
 * @param it the iterator to create the list from.
 * @return List* 
 */
List* list_initFromIterator(Iterator* it);

/**
 * @brief Initialize linked list with function.
 * 
 * @param size size of the linked list.
 * @param initFunc function that creates dynamics values from the index in the list.
 * @return List* the new list.
 */
List* list_initFromFunc(int size, Dynamic (*initFunc)(int));

/**
 * @brief Retrieves an iterator from the list;
 * 
 * @param list a list.
 * @return Iterator an iterator for the content of the given list.
 */
Iterator* list_iterator(List* list);

#endif

struct _Link;

typedef struct _Link
{
    Dynamic value;
    struct _Link* next;
    struct _Link* prev;
} Link;

typedef struct _List
{
    Link* start;
    Link* end;
    int length;
} List;

List* list_empty()
{
    List* listRef = malloc(sizeof(List));
    listRef->length = 0;
    listRef->start = NULL;
    listRef->end = NULL;
    return listRef;
}

List* list_cons(List* list, Dynamic val)
{
    // printf("Beginning cons by creating new list:\n");
    List* outlist = list_empty();
    // printf("malloc next link:\n");
    Link* link = malloc(sizeof(Link));
    // printf("assign val to link:\n");
    link->value = val;
    if(list->start)
    {
        // printf("Cons move end\n");
        link->prev = list->end;
        link->prev->next = link;
        outlist->start = list->start;
    }
    else
    {
        // printf("Cons to end\n");
        outlist->start = link;
    }
    outlist->end = link;
    outlist->length = list->length + 1;
    return outlist;
}

List* list_copy(List* list)
{
    List* outList = list_empty();
    Link* currentLink = list->start;
    while(currentLink->next)
    {
        outList = list_cons(outList, currentLink->value);
        currentLink = currentLink->next;
    }
    return list_cons(outList, currentLink->value);
}

List* list_concatenate(List* listA, List* listB)
{
    List* outList = list_empty();
    Link* currentLink = listA->start;
    while(currentLink->next)
    {
        outList = list_cons(outList, currentLink->value);
        currentLink = currentLink->next;
    }
    outList = list_cons(outList, currentLink->value);
    currentLink = listB->start;
    while(currentLink->next)
    {
        outList = list_cons(outList, currentLink->value);
        currentLink = currentLink->next;
    }
    outList = list_cons(outList, currentLink->value);
    return outList;
}

Option list_head(List* list)
{
    if (list->start)
    {
        return some(list->start->value);
    }
    else return none();
}

List* list_tail(List* list)
{
    List* outList = list_empty();
    Link* currentLink = list->start;
    while(currentLink->next)
    {
        outList = list_cons(outList, currentLink->value);
        currentLink = currentLink->next;
    }
    return outList;
}

Option list_item(List* list, int index)
{
    if (index < 0 || index >= list->length)
    {
        return none();
    }

    bool goReverse = index > (list->length / 2);
    
    int ptr;
    Link* currentLink;

    if (goReverse)
    {
        ptr = list->length - 1;
        currentLink = list->end;
    }
    else
    {
        ptr = 0;
        currentLink = list->start;
    }

    while(ptr != index)
    {
        if (goReverse && currentLink->prev)
        {
            currentLink = currentLink->prev;
            ptr -= 1;
        }
        else if(!goReverse && currentLink->next)
        {
            currentLink = currentLink->next;
            ptr += 1;
        }
        else 
        {
            return none();
        }
    }
    return some(currentLink->value);
}

int list_length(List* list)
{
    return list->length;
}

void list_destroy(List* list)
{
    free(list);
}

List* list_initFromIterator(Iterator* it)
{
    List* list = list_empty();
    while(iterator_hasNext(it))
    {
        list = list_cons(list, iterator_next(it).value);
    }
    return list;
}

List* list_initFromFunc(int size, Dynamic (*initFunc)(int))
{
    int i;
    List* list = list_empty();
    for(i = 0; i < size; i++)
    {
        Dynamic val = (*initFunc)(i);
        list = list_cons(list, val);
    }
    return list;
}

Iterator* list_iterator(List* list)
{
    int length = list->length;
    // printf("length: %d\n", length);

    int i = 0;
    // printf("malloc'ing length * sizeof(Dynamic): %lu\n", (length * sizeof(Dynamic)));
    Dynamic* dynArr = malloc(length * sizeof(Dynamic));
    // printf("Getting list start link: %p\n", list->start);
    Link* currentLink = list->start;
    // printf("Entering while loop...\n");
    while(currentLink != NULL && currentLink->next != NULL)
    {
        // printf("Current link: %p\n", currentLink);
        // printf("Next link: %p\n", currentLink->next);
        // printf("Current value at current link: %p\n", (currentLink->value.value.ref));
        Dynamic currentValue = currentLink->value;
        dynArr[i] = currentValue;
        currentLink = currentLink->next;
        i += 1;
    }
    // printf("finished walking through list\n");
    if(length > 0){
        dynArr[i] = currentLink->value;
    }
    return iterator_init_eager(dynArr, length);
}

#ifndef DICTIONARY_H
#define DICTIONARY_H


/**
 * @file dictionary.h
 * @author Jon Voigt Tøttrup (jvoi@itu.dk)
 *
 * @brief A hash-table style dictionary.
 * 
 * Capable of storing by unsigned long or string.
 * Useful for storing dynamics.
 * 
 * @version 0.1
 * @date 2018-11-05
 *
 * @copyright WingCorp (c) 2018
 * 
 */



typedef struct _Dict Dict;

/**
 * @brief Returns a new, empty dictionary, ready for use.
 * 
 * @return Dict* 
 */
Dict* dict_empty();

/**
 * @brief Creates a dictionary from a set of key-value pairs.
 * 
 * @param count The initial size of the dictionary.
 *              Must correspond to the total amound of pairs in this call.
 * @param pair A key-value pair, the left side of the pair must be an unsigned long.
 *             The dictionary uses the HDC hash function, meaning that you can use hash(<your char*>)
 *             to use strings as keys.
 *             Otherwise, just build the Dictionary yourself.
 * @param ... A variable amount of pairs.
 * @return Dict* A dictionary of the pairs.
 */
Dict* dict_from(int count, Dynamic pair, ...);

/**
 * @brief Determine whether the dictionary contains an entry for the given key.
 * 
 * @param dict The dictionary to search.
 * @param key The key to find.
 * @return true The key is in the dictionary.
 * @return false The key is not in the dictionary.
 */
bool dict_contains(Dict* dict, unsigned long key);

/**
 * @brief Get a value from the dictionary by the given key.
 * 
 * @param dict The dictionary.
 * @param key The key to get by.
 * @return Option An option, possibly containing a value.
 */
Option dict_get(Dict* dict, unsigned long key);

/**
 * @brief Store the given value by the given key in the dictionary.
 * 
 * @param dict The dictionary.
 * @param key The key to store by.
 * @param val The value to store.
 */
void dict_put(Dict* dict, unsigned long key, Dynamic val);

/**
 * @brief Remove a value from the dictionary by the given key.
 * 
 * @param dict The dictionary to remove the key-value pair from.
 * @param key The key that is to be removed along its value.
 */
void dict_remove(Dict* dict, unsigned long key);

/**
 * @brief Remove a value from the dictionary and apply a destruction function to free
 * the stored value as well. Only use this function for 'ref' dynamics and if you know
 * what you are doing.
 * 
 * @param dict The dictionary to remove the key-value pair from.
 * @param key The key that is to be removed along with its value.
 * @param destroyer A function that takes a dynamic and frees the memory references.
 *                  Only use this for 'ref' dynamics.
 */
void dict_remove_destroy(Dict* dict, unsigned long key, void (*destroyer)(Dynamic));

/**
 * @brief Determine whether the dictionary contains an entry for the given key string.
 * 
 * @param dict The dictionary to search.
 * @param key The key string to find.
 * @return true The key string is in the dictionary.
 * @return false The key string is not in the dictionary.
 */
bool dict_contains(Dict* dict, unsigned long key);

/**
 * @brief Returns the size of the dictionary
 * 
 * @param dict A pointer to a dictionary.
 */
int dict_size(Dict* dict);

/**
 * @brief Determines whether the given dictionary is empty.
 * 
 * @param dict A pointer to a dictionary.
 * @return true The dictionary is empty.
 * @return false The dictionary is not empty.
 */
bool dict_isEmpty(Dict* dict);

/**
 * @brief Get a value from the dictionary by the given key string.
 * 
 * @param dict The dictionary.
 * @param key The key to get by.
 * @return Option An option, possibly containing a value.
 */
Option dict_get_s(Dict* dict, char* key);

/**
 * @brief Store the given value by the given key string in the dictionary.
 * 
 * @param dict The dictionary.
 * @param key The key string to store by.
 * @param val The value to store.
 */
void dict_put_s(Dict* dict, char* key, Dynamic val);

/**
 * @brief Remove a value from the dictionary by the given key string.
 * 
 * @param dict The dictionary to remove the key-value pair from.
 * @param key The key string that is to be removed along its value.
 */
void dict_remove_s(Dict* dict, char* key);

/**
 * @brief Remove a value from the dictionary and apply a destruction function to free
 * the stored value as well. Only use this function for 'ref' dynamics and if you know
 * what you are doing.
 * 
 * @param dict The dictionary to remove the key-value pair from.
 * @param key The key string that is to be removed along with its value.
 * @param destroyer A function that takes a dynamic and frees the memory references.
 *                  Only use this for 'ref' dynamics.
 */
void dict_remove_destroy_s(Dict* dict, char* key, void (*destroyer)(Dynamic));

/**
 * @brief Destroys the given dictionary, freeing it from memory.
 * 
 * @param dict The dictionary to destroy.
 */
void dict_destroy(Dict* dict);

/**
 * @brief Destroys the given dictionary, freeing it from memory.
 *        Uses the provided destroyer function to destroy dynamics stored in the dictionary.
 *        Only useful if you are using 'ref' type dynamics.
 * 
 * @param dict The dictionary to destroy.
 * @param destroyer A function that takes a dynamic and frees the memory references.
 *                  Only use this for 'ref' dynamics.
 */
void dict_destroy_thorough(Dict* dict, void (*destroyer)(Dynamic));

#endif

#define INIT_CAPACITY 4

typedef struct _Dict
{
    int size;
    int capacity;
    unsigned long* keys;
    Dynamic* values;
} Dict;

Dict* dict_empty()
{
    Dict* dict = malloc(sizeof(Dict));
    dict->capacity = INIT_CAPACITY;
    dict->size = 0;
    dict->keys = malloc(sizeof(unsigned long) * INIT_CAPACITY);
    dict->values = malloc(sizeof(Dynamic) * INIT_CAPACITY);
    return dict;
}

int dict_size(Dict* dict)
{
    return dict->size;
}

bool dict_isEmpty(Dict* dict)
{
    return dict->size <= 0;
}

void resize(Dict* dict, int newCapacity)
{
    unsigned long* newKeys = realloc(dict->keys, newCapacity * sizeof(unsigned long));
    Dynamic* newValues = realloc(dict->values, newCapacity * sizeof(Dynamic));
    unsigned long* oldKeys = dict->keys;
    Dynamic* oldValues = dict->values;
    int cap = dict->capacity;
    int i;
    for (i = 0; i < cap; i++)
    {
        newKeys[i] = oldKeys[i];
        newValues[i] = oldValues[i];
    }
    dict->capacity = newCapacity;
}

void dict_put(Dict* dict, unsigned long key, Dynamic value)
{
    if (dict->size >= dict->capacity/2)
    {
        resize(dict, 2 * dict->capacity);
    }
    int i;
    for(i = key % dict->capacity; /* stops when succesful */; i = (i + 1) % dict->capacity)
    {
        if (dict->keys[i] != 0ul) 
        {
            continue;
        }
        dict->keys[i] = key;
        dict->values[i] = value;
        break;
    }
    dict->size++;
}

Option dict_get(Dict* dict, unsigned long key)
{
    if (dict_isEmpty(dict))
    {
        return none();
    }
    int start = key % dict->capacity;
    int i = start;
    do
    {
        if (dict->keys[i] == key)
        {
            return some(dict->values[i]);
        }
        i++;
    } while (i != start);
    return none();
}

bool dict_contains(Dict* dict, unsigned long key)
{
    Option opt = dict_get(dict, key);
    return opt.type == SOME;
}

void dict_remove_destroy(Dict* dict, unsigned long key, void (*destroyer)(Dynamic))
{
    if (dict_isEmpty(dict))
    {
        return;
    }
    int start = key % dict->capacity;
    int i = start;
    do
    {
        if (dict->keys[i] == key)
        {
            dict->keys[i] = 0ul;
            destroyer(dict->values[i]);
            dict->values = NULL;
        }
        i++;
    } while (i != start);
    if (dict->size - 1 <= dict->capacity/3)
    {
        resize(dict, dict->capacity/3);
    }
    dict->size--;
}

void default_destroyer(Dynamic d) {
    some(d); //No-op, essentially.
}

void dict_remove(Dict* dict, unsigned long key)
{
    dict_remove_destroy(dict, key, default_destroyer);
}

Option dict_get_s(Dict* dict, char* key)
{
    return dict_get(dict, hash(key));
}

bool dict_contains_s(Dict* dict, char* key)
{
    return dict_contains(dict, hash(key));
}

void dict_put_s(Dict* dict, char* key, Dynamic val)
{
    dict_put(dict, hash(key), val);
}

void dict_remove_s(Dict* dict, char* key)
{
    dict_remove(dict, hash(key));
}

Dict* dict_from(int count, Dynamic pair, ...)
{
    if (t_fst(pair) != ULONG) {
        failwith("Left type of every pair must be an unsigned long.");
    }
    
    va_list args;
    va_start(args, pair);

    Dict* dict = dict_empty();
    dict_put(dict, ui64(fst(pair)), snd(pair));
    int i;
    for (i = 1; i < count; i++)
    {
        Dynamic param = va_arg(args, Dynamic);
        if (t_fst(param) != ULONG) {
            failwith("Left type of every pair must be an unsigned long.");
        }
        dict_put(dict, ui64(fst(param)), snd(param));
    }
    va_end(args);
    return dict;
}

#ifndef TREE_H
#define TREE_H

/**
 * @file tree.h
 * @author Jon Voigt Tøttrup (jvoi@itu.dk)
 * @brief An implementation of the Red-Black BST data structure.
 * @version 0.1
 * @date 2018-11-01
 * 
 * @copyright WingCorp (c) 2018
 * 
 */


typedef struct _Tree Tree;

/**
 * @brief Initialize a new Tree.
 * 
 * @return Tree* a new Tree instance.
 */
Tree* tree_init();

/**
 * @brief Destroy the given tree, freeing the memory.
 * 
 * @param tree The tree to destroy.
 */
void tree_destroy(Tree* tree);

/**
 * @brief Inserts a value into the tree.
 * 
 * @param tree The Tree to put the element into.
 * @param key The key to distinguish the element by.
 * @param value The value to insert.
 */
void tree_put(Tree* tree, Comparable key, Dynamic value);

/**
 * @brief Attempts to retrieve a value from the tree by a key.
 * 
 * @param tree The tree to get the value from.
 * @param key The key to get by.
 * @return Option An option that might contain a value.
 */
Option tree_get(Tree* tree, Comparable key);

/**
 * @brief Remove a value from the tree matching the given key.
 * 
 * @param tree The tree to remove from.
 * @param key The key to remove by.
 */
void tree_remove(Tree* tree, Comparable key);

/**
 * @brief Determines the size of the given tree.
 * 
 * @param tree The tree to get the size from.
 * @return int The size of the tree.
 */
int tree_size(Tree* tree);

/**
 * @brief Prints the layout of the tree.
 * 
 * Prints () for empty nodes and (O) for nodes with values.
 * 
 * @param tree The tree to print.
 */
void tree_print(Tree* tree);

/**
 * @brief Determines if the tree contains a value.
 * 
 * Should take O(log(N))
 * 
 * @param tree The Tree to check.
 * @param key The key to check for.
 * @return true The key is present in the tree.
 * @return false The key is not present in the tree.
 */
bool tree_contains(Tree* tree, Comparable key);

/**
 * @brief Returns an ordered iterator from the tree.
 * 
 * @param tree The tree to create the iterator from.
 * @return Iterator* An ordered iterator.
 */
Iterator* tree_iterator(Tree* tree);

#endif

/**
 * @file tree.c
 * @author Jon Voigt Tøttrup (jvoi@itu.dk)
 * @brief An implementation of the Red-Black BST data structure.
 * @version 0.1
 * @date 2018-11-01
 * 
 * @copyright WingCorp (c) 2018
 * 
 */



bool RED = true;
bool BLACK = false;

struct _Node;

typedef struct _Node
{
    Comparable key;
    Dynamic value;
    struct _Node* left;
    struct _Node* right;
    int size;
    bool color;
} Node;

Node* mk_node(Comparable key, Dynamic value, int size, bool color)
{
    Node* node = malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->size = size;
    node->color = color;
    return node;
}

bool is_red(Node* n)
{
    return (n == NULL) ? false : n->color == RED;
}

int size(Node* n)
{
    return (n == NULL) ? 0 : n->size;
}

Node* rotate_left(Node* h)
{
    Node* x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = x->left->color;
    x->left->color = RED;
    x->size = h->size;
    h->size = size(h->left) + size(h->right) + 1;
    return x;
}

Node* rotate_right(Node* h)
{
    Node* x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = x->right->color;
    x->right->color = RED;
    x->size = h->size;
    h->size = size(h->left) + size(h->right) + 1;
    return x;
}

void flip_colors(Node* n)
{
    if (n != NULL) {
        n->color = !(n->color);
    } else return;
    if (n->left != NULL)
    {
        n->left->color = !(n->left->color);
    }
    if (n->right != NULL)
    {
        n->right->color = !(n->right->color);
    }
}

typedef struct _Tree
{
    Node* root;
} Tree;

void node_print_rec(Node* node)
{
    if (node == NULL)
    {
        return;
    }
    else {
        printf("\"O\": {");
    }
    printf("\"left\": {");
    node_print_rec(node->left);
    printf("}, \"right\": {");
    node_print_rec(node->right);    
    printf("}}");
}

void node_print(Node* node)
{
    printf("{");
    node_print_rec(node);
    printf("}\n");   
}

void tree_print(Tree* tree)
{
    if (tree->root == NULL)
    {
        printf("{}\n");
    }
    else
    {
        node_print(tree->root);
    }
}

int tree_size(Tree* tree)
{
    return size(tree->root);
}

Option get(Node* n, Comparable key)
{
    if (n == NULL)
    {
        return none();
    }
    int cmp = compare(key, n->key);
    if (cmp < 0) 
    {
        return get(n->left, key); 
    }
    else if (cmp > 0) 
    { 
        return get(n->right, key); 
    }
    else
    {
        return some(n->value);
    } 
}

Option tree_get(Tree* tree, Comparable key)
{
    return get(tree->root, key);
}

Node* put(Node* n, Comparable key, Dynamic value)
{
    if (n == NULL)
    {
        return mk_node(key, value, 1, RED);
    }
    int cmp = compare(key, n->key);
    if (cmp < 0)
    {
        n->left = put(n->left, key, value);
    }
    else if (cmp > 0)
    {
        n->right = put(n->right, key, value);
    } 
    else 
    {
        n->value = value;
    }
    if (is_red(n->right) && !is_red(n->left))
    {
        n = rotate_left(n);
    }
    if (is_red(n->left) && is_red(n->left->left))
    {
        n = rotate_right(n);
    }
    if (is_red(n->left) && is_red(n->right))
    {
        flip_colors(n);
    }
    n->size = 1 + size(n->left) + size(n->right);
    return n;
}

void tree_put(Tree* tree, Comparable key, Dynamic value)
{
    tree->root = put(tree->root, key, value);
    tree->root->color = BLACK;
}

bool tree_is_empty(Tree* tree)
{
    return tree->root->size == 0;
}

bool tree_contains(Tree* tree, Comparable key)
{
    return tree_get(tree, key).type != NONE;
}

Node* balance(Node* n)
{
    if(is_red(n->right))
    {
        n = rotate_left(n);
    }
    if (is_red(n->left) && is_red(n->left->left))
    {
        n = rotate_right(n);
    }
    if (is_red(n->left) && is_red(n->right))
    {
        flip_colors(n);
    }
    n->size = 1 + size(n->left) + size(n->right);
    return n;
}

Node* move_red_left(Node* n)
{
    flip_colors(n);
    if (is_red(n->right->left))
    {
        n->right = rotate_right(n->right);
        n = rotate_left(n);
        flip_colors(n);
    }
    return n;
}

Node* move_red_right(Node* n)
{
    flip_colors(n);
    if (is_red(n->left->left))
    {
        n = rotate_right(n);
        flip_colors(n);
    }
    return n;
}

Node* node_min(Node* n)
{
    if(n->left == NULL)
    {
        return n;
    }
    else return node_min(n->left);
}

Node* node_remove_min(Node* n)
{
    if(n->left == NULL)
    {
        free(n);
        return NULL;
    }
    if(!is_red(n->left) && !is_red(n->left->left))
    {
        n = move_red_left(n);
    }

    n->left = node_remove_min(n->left);
    return balance(n);
}

Node* node_remove(Node* n, Comparable key)
{
    if (compare(key, n->key) < 0)
    {
        if (!is_red(n->left) && !is_red(n->left->left))
        {
            n = move_red_left(n);
        }
        n->left = node_remove(n->left, key);
    }
    else
    {
        if (is_red(n->left))
        {
            n = rotate_right(n);
        }
        if (compare(key, n->key) == 0 && (n->right == NULL))
        {
            free(n);
            return NULL;
        }
        if (!is_red(n->right) && !is_red(n->right->left))
        {
            n = move_red_right(n);
        }
        if (compare(key, n->key) == 0)
        {
            Node* x = node_min(n->right);
            n->key = x->key;
            n->value = x->value;
            n->right = node_remove_min(n->right);
        }
        else
        {
            n->right = node_remove(n->right, key);
        }
    }
    return balance(n);
}

void tree_remove(Tree* tree, Comparable key)
{
    if(!tree_contains(tree, key))
    {
        return;
    }
    if (!is_red(tree->root->left) && !is_red(tree->root->right))
    {
        tree->root->color = RED;
    }
    tree->root = node_remove(tree->root, key);
    if (tree->root->size != 0)
    {
        tree->root->color = BLACK;
    }
}

void tree_remove_min(Tree* tree)
{
    if (tree->root->size == 0)
    {
        return;
    }
    if(!is_red(tree->root->left) && !is_red(tree->root->right))
    {
        tree->root->color = RED;
    }
    tree->root = node_remove_min(tree->root);
    if (tree->root->size > 0)
    {
        tree->root->color = BLACK;
    }
}

Node* node_remove_max(Node* n)
{
    if(is_red(n->left))
    {
        n = rotate_right(n);
    }

    if(n->right == NULL)
    {
        free(n);
        return NULL;
    }

    if(!is_red(n->right) && !is_red(n->right->left))
    {
        n = move_red_right(n);
    }

    n->right = node_remove_max(n->right);

    return balance(n);
}

void tree_remove_max(Tree* tree)
{
    if (tree->root->size == 0)
    {
        return;
    }
    if(!is_red(tree->root->left) && !is_red(tree->root->right))
    {
        tree->root->color = RED;
    }
    tree->root = node_remove_max(tree->root);
    if (tree->root->size > 0)
    {
        tree->root->color = BLACK;
    }
}

Tree* tree_init()
{
    Tree* tree = malloc(sizeof(Tree));
    return tree;
}

List* tree_traverseInOrder(Node* node)
{
    List* res = list_empty();
    if (node->left != NULL && node->left->size > 0) {
        res = list_concatenate(res, tree_traverseInOrder(node->left));
    }
    res = list_cons(res, node->value);
    if (node->right != NULL && node->right-> size > 0) {
        res = list_concatenate(res, tree_traverseInOrder(node->right));
    }
    return res;
}

Iterator* tree_iterator(Tree* tree)
{
    List* list = tree_traverseInOrder(tree->root);
    Iterator* it = list_iterator(list);
    list_destroy(list);
    return it;
}

void tree_destroy(Tree* tree)
{
    do
    {
        tree_remove_min(tree);
        tree_remove_max(tree);
    }
    while(tree->root->color != BLACK);
    free(tree);
}

#ifndef SET_H
#define SET_H
/**
 * @file set.h
 * @author Jon Voigt Tøttrup (jvoi@itu.dk)
 *
 * @brief A Tree-Set implementation.
 * @version 0.1
 * @date 2018-11-05
 *
 * @copyright WingCorp (c) 2018
 * 
 */


/**
 * @brief The Set struct.
 *        A set of Comparables.
 */
typedef struct _Set Set;

/**
 * @brief Create an Empty set object.
 * 
 * @return Set* A new empty set.
 */
Set* set_empty();

/**
 * @brief Initialize a Set with a fixed size and initFunction.
 * 
 * @param size The size of the new set.
 * @param initFun A function that takes an integer and returns a Set item.
 * @return Set* A new Set.
 */
Set* set_initFun(int size, Comparable *(initFun)(int));

/**
 * @brief Initialize a Set with an iterator of comparable values.
 * 
 * @param iterator An iterator of Comparable values
 * @return Set* A new Set.
 */
Set* set_init(Iterator* iterator);

/**
 * @brief Add an item to a set.
 * 
 * @param set The set.
 * @param item The item to add.
 */
void set_add(Set* set, Comparable item);

/**
 * @brief Determine if a set contains an item.
 * 
 * @param set The set.
 * @param item The item.
 * @return true The set contains the item.
 * @return false The set does not contain the item.
 */
bool set_contains(Set* set, Comparable item);

/**
 * @brief Return an iterator of a set.
 * 
 * @param set The set to iterate over.
 * @return Iterator* The iterator.
 */
Iterator* set_iterator(Set* set);

/**
 * @brief Destroy a set, freeing it from memory.
 * 
 * @param set The set to destroy.
 */
void set_destroy(Set* set);

#endif
typedef struct _Set 
{
    Tree* tree;
} Set;

Set* set_empty()
{
    Set* set = malloc(sizeof(Set));
    set->tree = tree_init();
    return set;
}

void set_add(Set* set, Comparable item)
{
    tree_put(set->tree, item, item.value);
}

bool set_contains(Set* set, Comparable item)
{
    return tree_contains(set->tree, item);
}

Set* set_initFun(int size, Comparable *(initFun)(int))
{
    Set* set = set_empty();
    int i;
    for(i = 0; i < size; i++)
    {
        set_add(set, *initFun(i));
    }
    return set;
}

Set* set_init(Iterator* iterator)
{
    Set* set = set_empty();
    Option itemOpt = iterator_next(iterator);
    while(itemOpt.type == SOME)
    {
        set_add(set, comparable(itemOpt.value));
        itemOpt = iterator_next(iterator);
    }
    return set;
}

Iterator* set_iterator(Set* set)
{
    tree_iterator(set->tree);
}

void set_destroy(Set* set)
{
    tree_destroy(set->tree);
    free(set);
}


#endif

#pragma endregion HDC

#include "hdc.h"

int main()
{
    //Write your code here!
}
