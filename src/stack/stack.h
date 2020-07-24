#ifndef STACK_H
#define STACK_H

/**
 * @brief A resizable stack for working with dynamics.
 * 
 * @file stack.h
 * @author WingCorp
 * @date 2018-06-15
 */

#include "./../dynamic/dynamic.h"
#include "./../iterator/iterator.h"

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
Dynamic stack_pop(Stack* stack);

/**
 * @brief Peeks at the top value of a Stack.
 * 
 * @param stack The stack to peek at.
 * @return Option The value at the top of the stack, if any.
 */
Dynamic stack_peek(Stack* stack);

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
 * @param stack The stack.
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
