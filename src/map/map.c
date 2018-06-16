#include "map.h"
#include <stdlib.h>

Iterator map(Iterator ite, Dynamic (*mapper) (Dynamic))
{
    Dynamic* mappedValues = malloc(ite.length * sizeof(Dynamic));
    int i;
    for (i = 0; i < ite.length; i++)
    {
        mappedValues[i] = (*mapper)(ite.data[i]);
    }
    return iterator(mappedValues, ite.length);
}
