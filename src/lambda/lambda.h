#ifndef LAMBDA_H
#define LAMBDA_H

/**
 * @file closure.h
 * @author Jon Voigt Tøttrup (jvoi@itu.dk)
 *
 * @brief A module for allowing creation and usage of closures.
 * 
 * The piece d' resistance of this entire library.
 * @version 0.1
 * @date 2018-11-06
 *
 * @copyright WingCorp (c) 2018
 * 
 */

#include "./../dictionary/dictionary.h"

typedef struct _Lambda Lambda;

/**
 * @brief Constructs a new Lambda function from a given lambda text and environment.
 * 
 * @param body The code that the lambda should execute, the 'body' of the lambda.
 * @param environment A dictionary of the variables that the lambda should have access to.
 * @return Lambda A Lambda struct.
 */
Lambda* lambda(char* body, Dict* environment);

Dynamic go(Lambda* lambda);

#endif