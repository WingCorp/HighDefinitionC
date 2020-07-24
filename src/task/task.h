#ifndef PAR_H
#define PAR_H

/**
 * @file task.h
 * @author Jon Voigt Tøtturp (jon@zendata.dk)
 * @brief A simple module for setting up asynchronous operations.
 * @version 0.1
 * @date 2019-08-25
 * 
 * @copyright WingCorp (c) 2019
 * 
 */

#include "./../fail/fail.h"
#include "./../lambda/lambda.h"

/**
 * @brief Enables the Task module.
 * Asynchronous operations (tasks) cannot be awaited until this is called.
 *
 * @param parallelism How much parallelization the program should use.
 *                    This should usually be a multiple of the amount of logical
 *                    cores available to the system.
 */
void task_enable(int parallelism);

/**
 * @brief Disables the Task module.
 * All running asynchronous operations (tasks) are lost.
 * Calling this before all tasks have been awaited will cause undefined behaviour.
 */
void task_disable();

/**
 * @brief A struct that encapsulates the information required for an asynchronous operation.
 */
typedef struct _Task Task;

/**
 * @brief Setup an asynchronous operation.
 * 
 * @param operation The operation to perform asynchronously.
 * @return Task* A pointer to the task representing the asynchronous execution of the operation.
 */
Task* asynco(Dynamic (*operation)());

/**
 * @brief Setup an asynchronous lambda.
 * 
 * @param lambda The lambda to invoke asynchronously.
 * @param arguments The arguments to call the asynchronous lambda with.
 * @return Task* A pointer to the task representing the asynchronous execution of the lambda.
 */
Task* asyncl(Lambda* lambda, List* arguments);

/**
 * @brief Awaits the execution of an asynchronous operation.
 * 
 * @param task Pointer to the Task to await.
 * @return Dynamic<Option> The result of the operation (if any).
 */
Dynamic await(Task *task);

#endif