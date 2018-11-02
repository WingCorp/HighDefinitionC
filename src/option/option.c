#include "option.h"
#include "./../fail/fail.h"

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

Dynamic coerce(Option opt)
{
    if (opt.type == NONE)
    {
        failwith("Could not coerce value from empty option!\n");
    }
    return opt.value;
}