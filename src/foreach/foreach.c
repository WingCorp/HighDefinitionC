#include "foreach.h"

void foreach(Iterator* iterator, void (*action) (Dynamic))
{
    while (iterator_hasNext(iterator))
    {
        (*action)(iterator_next(iterator).value);
    }
    iterator_reset(iterator);
}