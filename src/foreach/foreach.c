#include "foreach.h"

void foreach(Iterator iterator, void (*action) (Dynamic))
{
    int i;
    for (i = 0; i < iterator.length; i++)
    {
        (*action)(iterator.data[i]);
    }
}
