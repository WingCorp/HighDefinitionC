#ifndef OPTION_H
#define OPTION_H
/**
 * @brief The option type
 * 
 * @file option.h
 * @author WingCorp
 * @date 2018-06-15
 */

#include "./../primitive/primitive.h"

typedef enum _OptionType
{
    SOME,
    NONE
} OptionType;

typedef struct _Option
{
    OptionType type;
    Primitive value;
} Option;

Option none();
Option some(Primitive value);

#endif
