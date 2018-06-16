#include "option.h"

Option none()
{
    return (Option) { .type = NONE };
}

Option some(Primitive value)
{
    return (Option) { .type = SOME, .value = value };
}

