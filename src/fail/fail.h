#ifndef FAIL_H
#define FAIL_H

#include <stdbool.h>

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
