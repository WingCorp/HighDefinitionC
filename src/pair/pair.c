#include "pair.h"

Pair pair_of(Dynamic left, Dynamic right)
{
    return (Pair) { .left_type = left.type, .left = left, .right_type = right.type, .right = right };
}
