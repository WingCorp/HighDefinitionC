#include "par.h"
#include <stdlib.h>

#include "./../queue/queue.h"

Queue** queues;

void par_enable()
{
    queues = malloc(sizeof(Queue*) * 4);
    
}

void par_disable()
{
    int i;
    for (i = 0; i < 4; i++)
    {
        queue_destroy(queues[i]);
    }
}

typedef struct _Par
{
    Option value;
} Par;

Par par_unit(Option opt)
{
    return (Par) { .value = opt };
}

Par par_map2(Par a, Par b, Option* mapper(Option a, Option b))
{

}