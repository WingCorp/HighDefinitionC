#include "set.h"

Set* set_empty();

Set* set_init(int size, Comparable *(initFun)(int));

Set* set_init(Iterator* iterator);

Set* set_add(Comparable item);

Set* set_contains(Comparable item);

Iterator* set_iterator(Set* set);