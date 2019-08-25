#ifndef PAR_H
#define PAR_H

/**
 * @file par.h
 * @author Jon Voigt Tøtturp (jon@zendata.dk)
 * @brief A simple module for parallel operations.
 * @version 0.1
 * @date 2019-08-25
 * 
 * @copyright WingCorp (c) 2019
 * 
 */

#include "./../fail/fail.h"
#include "./../option/option.h"

/**
 * @brief Enables the Par module.
 * Parallel operations cannot be awaited until this is called.
 */
void par_enable();

/**
 * @brief Disables the Par module.
 * All running parallel operations are lost.
 * Calling this before all parallel operations have been awaited will cause undefined behaviour.
 */
void par_disable();

/**
 * @brief A struct that encapsulates the information required for a parallel operation.
 */
typedef struct _Par Par;

/**
 * @brief Wraps an option in a Par struct. Use this for wrapping the results of your parallel code.
 * ATTENTION: This is not sufficient for parallelizing code.
 * Use the fork function to run *operations* in parallel.
 * 
 * @param d An optional dynamically typed value.
 * @return Par A parallel struct wrapping the value.
 */
Par par_unit(Option opt);

/**
 * @brief Combines the results of two parallel computations with a binary function.
 * 
 * @param a The first Par struct.
 * @param b The second Par struct.
 * @param mapper The function that combines the underlying values.
 * @return Par A Par struct wrapping the result of the combination.
 */
Par par_map2(Par a, Par b, Option* mapper(Option a, Option b));

/**
 * @brief Marks a computation for concurrent evaluation by await().
 * 
 * @param operation The operation to perform concurrently.
 * @return Par A Par struct that wraps the operation.
 */
Par par_fork(Option* operation());

/**
 * @brief Awaits the execution of a parallel computation.
 * 
 * @param p The Par struct to await.
 * @return Option The result of the par.
 */
Option par_await(Par p);

#endif