#ifndef FAIL_H
#define FAIL_H

#include <stdbool.h>
#include <stdlib.h>
#ifndef WIN32
#include <execinfo.h>
#endif
#include <stdio.h>
#include <stdarg.h>

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

#define FAIL_RED "\x1b[31m"
#define FAIL_RESET "\x1b[0m"

void trace_stack();

#define failwith(message)   \
    do {                    \
        printf(FAIL_RED);   \
        printf(message);    \
        printf(FAIL_RESET); \
        trace_stack();      \
        exit(EXIT_FAILURE); \
    } while (0)

/**
 * @brief Print the error cause and exit the program with an error value.
 * 
 * @param cause to print before exiting. Use this like you would use printf.
 * @param VAR_ARGS, whatever you want it to say in your failure output.
 */
#define failwithf(format, ...)              \
    do {                                    \
        printf(FAIL_RED);                   \
        printf(format, ##__VA_ARGS__);      \
        printf(FAIL_RESET);                 \
        trace_stack();                      \
        exit(EXIT_FAILURE);                 \
    } while(0)                          

#endif
