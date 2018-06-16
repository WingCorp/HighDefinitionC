#ifndef OPTION_H
#define OPTION_H
/**
 * @brief The option type
 * 
 * @file option.h
 * @author WingCorp
 * @date 2018-06-15
 */

#include "./../dynamic/dynamic.h"

typedef enum _OptionType
{
    SOME,
    NONE
} OptionType;

typedef struct _Option
{
    OptionType type;
    Dynamic value;
} Option;

Option none();
Option some(Dynamic value);

#endif
