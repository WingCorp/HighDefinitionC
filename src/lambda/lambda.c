#include "./lambda.h"
#include "./../fail/fail.h"
#include "./../list/list.h"

#include <stdlib.h>

typedef struct _Lambda
{
    Dynamic (*function)(Dict*, List*);
    Dict* env;
} Lambda;

Lambda* lambda(Dynamic(*function)(Dict*, List*), Dict* env)
{
    Lambda* l = malloc(sizeof(Lambda));
    l->env = env;
    l->function = function;
    return l;
}

Dynamic invoke(Lambda* l, List* arguments)
{
    Dynamic (*function)(Dict*, List*) = l->function;
    return function(l->env, arguments);
}

Dynamic successl(Dynamic opt, Lambda* optLambda)
{
    if (opt.type != OPTION)
    {
        failwithf("successl() can only be called on an OPTION, but was given a %s\n", typename(opt.type));
    }
    Option option = opt.value.option;
    if (option.type == NONE)
    {
        return none();
    }
    Dynamic value = *option.value;
    return invoke(optLambda, list_from(1, value));
}

Iterator* mapl(Iterator* iterator, Lambda* lambda)
{
    int size = iterator_remaining(iterator);
    Dynamic* mappedValues = malloc(size * sizeof(Dynamic));
    int i = 0;
    while (iterator_hasNext(iterator))
    {
        mappedValues[i] = invoke(lambda, list_from(1, coerce(iterator_next(iterator))));
    }
    iterator_reset(iterator);
    return iterator_init_eager(mappedValues, size);
}

