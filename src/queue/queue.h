#ifndef QUEUE_H
#define QUEUE_H

/**
 * @brief A very lazily implemented Queue for dynamics.
 * 
 * @file queue.h
 * @author WingCorp
 * @date 2019-08-25
 * 
 */

#include "./../dynamic/dynamic.h"
#include "./../option/option.h"
#include "./../iterator/iterator.h"

typedef struct _Queue Queue;

/**
 * @brief Initializes a new Queue data structure.
 * 
 * @param initialCap The initial capacity of the queue.
 * @return Queue* A pointer to the new queue.
 */
Queue* queue_init(int initialCap);

/**
 * @brief Frees the memory occupied by a Queue data structure.
 * 
 * @param queue The queue to destroy.
 */
void queue_destroy(Queue* queue);

/**
 * @brief Add a dynamic value to a Queue.
 * 
 * @param queue The Queue to add to.
 * @param dyn The Dynamic to add to the queue.
 */
void queue_add(Queue* queue, Dynamic dyn);

/**
 * @brief Removes the first element of the queue (if any) and returns it.
 * 
 * @param queue The Queue to remove from.
 * @return Option The element polled, Some if any, otherwise None.
 */
Option queue_poll(Queue* queue);

/**
 * @brief Peeks at the first element in the queue without disturbing it.
 * 
 * @param queue The Queue to peek at.
 * @return Option The peeked element, if any.
 */
Option queue_peek(Queue* queue);

/**
 * @brief Returns the size of the Queue.
 * 
 * @param queue The Queue.
 * @return int The size of the Queue.
 */
int queue_size(Queue* queue);

/**
 * @brief Returns the current capacity of the Queue.
 * 
 * @param queue The Queue.
 * @return int The current capacity of the Queue.
 */
int queue_capacity(Queue* queue);

/**
 * @brief Gets an iterator from the current Queue.
 * 
 * @param queue The queue.
 * @return Iterator* An iterator.
 */
Iterator* queue_iterator(Queue* queue);

/**
 * @brief Maps every entry in the Queue to a new Queue using a mapper function.
 * 
 * @param queue The queue.
 * @param mapper The mapper function.
 * @return Queue* The mapped queue.
 */
Queue* queue_map(Queue* queue, Dynamic (*mapper)(Dynamic));

/**
 * @brief Folds over every entry in the queue.
 * 
 * @param queue The queue to fold over.
 * @param state The initial state to fold onto.
 * @param folder The folder function with the signature 'Dynamic folder(Dynamic accumulator, Dynamic element)'.
 * @return Dynamic The final state.
 */
Dynamic queue_fold(Queue* queue, Dynamic state, Dynamic (*folder)(Dynamic, Dynamic));

#endif