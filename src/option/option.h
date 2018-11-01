#ifndef OPTION_H
#define OPTION_H
/**
 * @brief The option monad
 * 
 * @file option.h
 * @author WingCorp
 * @date 2018-06-15
 */

#include "./../dynamic/dynamic.h"

typedef enum _OptionType
{
    NONE,
    SOME
} OptionType;

typedef struct _Option
{
    OptionType type;
    Dynamic value;
} Option;

/**
 * @brief The 'none' return-function.
 * 
 * @return Option 
 */
Option none();

/**
 * @brief The 'some' return-function
 * 
 * @param value 
 * @return Option 
 */
Option some(Dynamic value);

/**
 * @brief Takes an option and a function 
 *        that takes the result of the given option
 *        and applies the option to the given function
 *        if the option was some.
 *
 * @param opt an Option value.
 * @param optFunc a function of signature: Option <name>(Dynamic <arg>); 
 * @return Option an option value.
 */
Option success(Option opt, Option (*optFunc)(Dynamic));

#endif
