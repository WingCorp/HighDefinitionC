#include "fold.h"

Dynamic fold(Iterator* iterator, Dynamic initialState, Dynamic (*folder) (Dynamic, Dynamic))
{
    Dynamic current_state = initialState;
    while (iterator_hasNext(iterator))
    {
        Dynamic currentValue = coerce(iterator_next(iterator));
        current_state = (*folder)(current_state, currentValue);
    }
    iterator_reset(iterator);
    return current_state;
}
