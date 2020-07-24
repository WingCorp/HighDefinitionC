#include "foreach.h"

void foreach(Iterator* iterator, void (*action) (Dynamic))
{
    while (iterator_hasNext(iterator))
    {
        (*action)(coerce(iterator_next(iterator)));
    }
    iterator_reset(iterator);
}