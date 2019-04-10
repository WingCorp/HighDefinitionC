/**
 * @brief A resizable stack for working with dynamics.
 * 
 * @file stack.c
 * @author WingCorp
 * @date 2018-06-15
 */

#include "stack.h"
#include "./../option/option.h"
#include "./../iterator/iterator.h"
#include <stdlib.h>
#include <stdio.h>

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