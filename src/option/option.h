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

/**
 * @brief Coerces an option to its value.
 *        Might cause a failure, if no value is present.
 * 
 * @param opt the option to coerce.
 * @return Dynamic the value to find;
 */
Dynamic coerce(Option opt);

/**
 * @brief Checks if an option has the type SOME.
 *  
 * @return int 1 if it is, 0 otherwise
 */
#define isSome(option) option.type == SOME

/**
 * @brief Checks if an option has the type NONE.
 * 
 * @return int 1 if it is, 0 otherwise
 */
#define isNone(option) option.type == NONE


#endif
