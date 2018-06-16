/**
 * @brief A resizable stack for working with primitives.
 * 
 * @file stack.c
 * @author WingCorp
 * @date 2018-06-15
 */

#include "stack.h"
#include "./../option/option.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct _Stack
{
    int capacity;
    int size;
    Primitive* primitives;
} Stack;

Stack* stack_init(int initialCap)
{
    Stack* stack = malloc(sizeof(Stack));
    stack->capacity = initialCap;
    stack->size = 0;
    stack->primitives = malloc(sizeof(Primitive) * initialCap);
    return stack;
}

void stack_destroy(Stack* stack)
{
    free(stack->primitives);
    free(stack);
}

void reallocStack(Stack* stack, float sizeChange)
{
    int oldCap = stack->capacity;
    int newCap = oldCap * sizeChange;
    stack->primitives = realloc(stack->primitives, newCap * sizeof(Primitive));
    stack->capacity = newCap;
}

void increaseCapacity(Stack* stack)
{
    reallocStack(stack, 1.5);
}

void stack_push(Stack* stack, Primitive prim)
{
    int top = stack->size;
    if (top + 1 == stack->capacity)
    {
        increaseCapacity(stack);
    }
    stack->primitives[top] = prim;
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
    Primitive toReturn = stack->primitives[top];
    stack->size -= 1;
    if (stack->size < 2 * stack->capacity)
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
    stack->primitives = realloc(stack->primitives, newCap * sizeof(Primitive));
    stack->capacity = newCap;
}

Stack* stack_map(Stack* stack, Primitive (*mapper) (Primitive))
{
    Stack* mappedStack = stack_init(stack->size);
    int i;
    for (i = 0; i < stack->size; i++){
        Primitive currentValue = stack->primitives[i];
        Primitive mappedValue = (*mapper)(currentValue);
        stack_push(mappedStack, mappedValue);
    }
    return mappedStack;
}

Primitive stack_fold(Stack* stack, Primitive state, Primitive (*folder) (Primitive, Primitive))
{
    Primitive currentState = state;
    int i;
    for (i = 0; i < stack->size; i++)
    {
        Primitive currentValue = stack->primitives[i];
        currentState = (*folder)(currentState, currentValue);
    }
    return currentState;
}