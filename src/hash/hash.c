#include "hash.h"

unsigned long hash(char* s)
{
    unsigned long hash = 5381;
    int c;

    while(c = *s++)
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}
