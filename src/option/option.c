#include "option.h"

Option none()
{
    return (Option) { .type = NONE };
}

Option some(Dynamic value)
{
    return (Option) { .type = SOME, .value = value };
}

