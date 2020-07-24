#include "option.h"
#include "./../fail/fail.h"

Dynamic none()
{
    return (Dynamic) { .type = NONE };
}

Dynamic some(Dynamic value)
{
    return (Dynamic) { .type = SOME, .value = value };
}

Dynamic success(Dynamic opt, Dynamic (*optFunc)(Dynamic))
{
    if (opt.type == NONE)
    {
        return none();
    }
    return (*optFunc)(opt.value);
}

Dynamic coerce(Dynamic opt)
{
    if (opt.type == NONE)
    {
        failwith("Could not coerce value from empty option!\n");
    }
    return opt.value;
}
