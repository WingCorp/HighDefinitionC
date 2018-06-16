#include "fold.h"

Dynamic fold(Iterator iterator, Dynamic initialState, Dynamic (*folder) (Dynamic, Dynamic))
{
    Dynamic current_state = initialState;
    int i;
    for (i = 0; i < iterator.length; i++)
    {
        Dynamic currentValue = iterator.data[i];
        current_state = (*folder)(current_state, currentValue);
    }
    return current_state;
}