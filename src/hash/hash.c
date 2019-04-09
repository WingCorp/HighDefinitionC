#include "hash.h"

/**
 * @brief Hashes a char* to an unsigned long.
 * K&R's hash function.
 *
 * @param s A string.
 * @return unsigned long A hash of the string.
 */
unsigned long hash(char* s)
{
    unsigned long hash = 5381;
    int c;

    while((c = *s++))
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}
