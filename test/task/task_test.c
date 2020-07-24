#include "./../../src/task/task.h"
#include "./../assert.h"
#include "./../test.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

char* strings[4] = {"Hello ", " my", " friends", "!\n"};

Dynamic print_first()
{
    printf("%s", strings[0]);
    return none();
}

Dynamic print_second()
{
    printf("%s", strings[1]);
    return none();
}

Dynamic print_third()
{
    printf("%s", strings[2]);
    return none();
}

Dynamic print_fourth()
{
    printf("%s", strings[3]);
    return none();
}

int print_exclamation_mark_test()
{
    task_enable(6);
    Task* t = asynco(print_fourth);
    await(t);
    task_disable();
    return 1;
}

Dynamic square(Dict* _env, List* arguments)
{
    int* values = (int *)ref(coerce(list_head(arguments)));
    int index = i32(coerce(list_item(arguments, 1)));
    int x = values[index];
    values[index] = x * x;
    return none();
}

Dynamic squareVal(Dict* _env, List* arguments)
{
    int x = i32(coerce(list_head(arguments)));
    return some(di32(x * x));
}

int compute_squares_parallel_test()
{
    int n = 5;
    int values[n];
    Task* tasks[n];

    int i;

    task_enable(2);
    Lambda* lsquare = lambda(square, dict_empty());
    
    for (i = 0; i < n; i++)
    {
        values[i] = i + 1;
    }

    int sum = 0;
    for (i = 0; i < n; i++)
    {
        sum += values[i];
    }
    printf("Sum of values: %d\n", sum);

    printf("computing squares in parallel...\n");
    for (i = 0; i < n; i++)
    {
        List* args = list_from(2, dref(values), di32(i));
        tasks[i] = asyncl(lsquare, args);
    }
    printf("Done!\n");

    printf("awaiting computations...\n");
    for (i = 0; i < n; i++)
    {
        await(tasks[i]);
    }
    printf("Done!\n");

    int squaredSum = 0;
    for (i = 0; i < n; i++)
    {
        squaredSum += values[i];
    }
    printf("Sum of squares: %d\n", squaredSum);
    return 1;
}

int print_async_test()
{
    task_enable(6);
    printf("enabled tasks\n");
    strings[0] = "Hello ";
    strings[1] = " my";
    strings[2] = " friends";
    strings[4] = " (enemies?)!\n";
    printf("setup strings\n");

    Task* tasks[400];
    int repetitions = 100;
    int i;
    for (i = 0; i < repetitions; i+=4)
    {
        tasks[i] = asynco(print_first);
        tasks[i + 1] = asynco(print_second);
        tasks[i + 2] = asynco(print_third);
        tasks[i + 3] = asynco(print_fourth);
    }

    for (i = 0; i < repetitions * 4; i++)
    {
        await(tasks[i]);
    }

    task_disable();
    return 0;
}

int enable_disable_test()
{
    task_enable(2);
    task_disable();
    return 1;
}

int main()
{
    test_declareAndRun("Enable and disable tasks", enable_disable_test);
    test_declareAndRun("Print a single message asynchronously", print_exclamation_mark_test);
    test_declareAndRun("Sum of squared random values computed in parallel", compute_squares_parallel_test);
    // test_declareAndRun("Print 400 messages and watch the messed up ordering", print_async_test);
}