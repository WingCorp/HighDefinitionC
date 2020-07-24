#include <stdio.h>
#include <signal.h>
#ifndef WIN32
#include <unistd.h>
#include <sys/wait.h>

int test_runInSubProcess(void (*testFunction) (void), int (*assertFunction) (char* output))
{
    int outcome = 0;

    int tube[2];
    pid_t pid;

    int bufferSize = 512;
    char outputBuffer[bufferSize];

    pipe(tube);
    pid = fork();
    if (pid == 0)
    {
        dup2(tube[1], STDOUT_FILENO);

        //DO THE THINGS:
        (*testFunction)();
        close(tube[1]);
        close(tube[0]);
    }
    else
    {
        close(tube[1]);
        wait(0);
        read(tube[0], outputBuffer, bufferSize);
        outcome = (*assertFunction)(outputBuffer);
        close(tube[0]);
    }

    return outcome;
}

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
#endif
