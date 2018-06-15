#include <stdio.h>

void test_declareAndRun(char* testName, int (*testFunction) (void))
{
    printf("#############################\n");
    printf("Running test: '%s'.\n", testName);
    int result = (*testFunction)();
    if(result)
    {
        printf("Test passed!\n");
    }
    else
    {
        printf("Test failed!\n");
    }
}
