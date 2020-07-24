#include "map.h"
#include <stdlib.h>
#include "../lambda/lambda.h"

Iterator* map(Iterator* ite, Dynamic (*mapper) (Dynamic))
{
    int size = iterator_remaining(ite);
    Dynamic* mappedValues = malloc(size * sizeof(Dynamic));
    int i = 0;
    while(iterator_hasNext(ite))
    {
        mappedValues[i] = (*mapper)(coerce(iterator_next(ite)));
        i += 1;
    }
    iterator_reset(ite);
    return iterator_init_eager(mappedValues, size);
}
