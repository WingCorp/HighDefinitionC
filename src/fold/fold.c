#include "fold.h"

Dynamic fold(Iterator iterator, Dynamic initialState, Dynamic (*folder) (Dynamic, Dynamic));