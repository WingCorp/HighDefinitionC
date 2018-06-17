#include "fold.h"

Dynamic fold(Iterator* iterator, Dynamic initialState, Dynamic (*folder) (Dynamic, Dynamic))
{
    Dynamic current_state = initialState;
    while (iterator_hasNext(iterator))
    {
        Dynamic currentValue = iterator_next(iterator).value;
        current_state = (*folder)(current_state, currentValue);
    }
    iterator_reset(iterator);
    return current_state;
}