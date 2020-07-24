#ifndef LAMBDA_H
#define LAMBDA_H

/**
 * @file lambda.h
 * @author Jon Voigt Tøttrup (jvoi@itu.dk)
 *
 * @brief A module for allowing creation and usage of lambda functions.
 * 
 * The piece d' resistance of this entire library.
 * @version 0.1
 * @date 2018-11-06
 *
 * @copyright WingCorp (c) 2018
 * 
 */

#include "./../dictionary/dictionary.h"
#include "./../list/list.h"
#include <stdarg.h>

typedef struct _Lambda Lambda;

/**
 * @brief Constructs a new Lambda function from a given function and environment.
 * 
 * @param function The function that the lambda invokes.
 * @return Lambda A Lambda struct.
 */
Lambda* lambda(Dynamic (*function)(Dict*, List*), Dict* env);

/**
 * @brief Invoke a lambda with a set of parameters.
 * 
 * @param l 
 * @param arguments
 * @return Dynamic<Option>
 */
Dynamic invoke(Lambda* l, List* arguments);

/**
 * @brief Takes an option and a lambda 
 *        that takes the result of the given option
 *        and applies the option to the given function
 *        if the option was some.
 *
 * @param opt a Dynamic<Option> value.
 * @param optLambda a lambda of signature: Dynamic<Option> <name>(Dynamic <arg>); 
 * @return Option an option value.
 */
Dynamic successl(Dynamic opt, Lambda* optLambda);

/**
 * @brief Maps an iterator using a Lambda.
 * 
 * @param iterator An iterator
 * @param lambda A lambda of the type Lambda<Dynamic>
 * @return Iterator* A new mapped iterator
 */
Iterator* mapl(Iterator* iterator, Lambda* lambda);

#endif