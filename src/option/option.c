#include "option.h"

Option none()
{
    return (Option) { .type = NONE };
}

Option some(Dynamic value)
{
    return (Option) { .type = SOME, .value = value };
}

Option success(Option opt, Option (*optFunc)(Dynamic))
{
    if (opt.type == NONE)
    {
        return none();
    }
    return (*optFunc)(opt.value);
}