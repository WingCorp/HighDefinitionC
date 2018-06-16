#include "assert.h"
#include <stdio.h>
#include <string.h>

int assertRefEquals(void* expected, void* actual)
{
    printf("Assertion that ref %p and ref %p were equal was ", expected, actual);
    if (expected == actual) 
    {
        printf("true!\n");
    } 
    else 
    {
        printf("false!\n");
    }
    return expected == actual;
}

int assertCharEquals(char expected, char actual)
{
    printf("Assertion that chars %c and %c were equal was ", expected, actual);
    if (expected == actual)
    {
        printf("true!\n");
    } 
    else 
    {
        printf("false!\n");
    }
    return expected == actual;
}

int assertStringEquals(char* expected, char* actual)
{
    printf("Assertion that strings %s and %s were equal was ", expected, actual);
    int areEqual = strcmp(expected, actual) == 0;
    
    if (areEqual)
    {
        printf("true!\n");
    } 
    else 
    {
        printf("false!\n");
    }
    return areEqual;
}

int assertLongEquals(long expected, long actual)
{
    printf("Assertion that longs %ld and %ld were equal was ", expected, actual);
    if (expected == actual)
    {
        printf("true!\n");
    } 
    else 
    {
        printf("false!\n");
    }
    return expected == actual;
}

int assertIntEquals(int expected, int actual)
{
    printf("Assertion that ints %d and %d were equal was ", expected, actual);
    if (expected == actual)
    {
        printf("true!\n");
    } 
    else 
    {
        printf("false!\n");
    }
    return expected == actual;
}

int assertDoubleEquals(double expected, double actual)
{
    printf("Assertion that doubles %f and %f were equal was ", expected, actual);
    if (expected == actual)
    {
        printf("true!\n");
    } 
    else 
    {
        printf("false!\n");
    }
    return expected == actual;
}

int assertFloatEquals(float expected, float actual)
{
    printf("Assertion that floats %f and %f were equal was ", expected, actual);
    if (expected == actual)
    {
        printf("true!\n");
    } 
    else 
    {
        printf("false!\n");
    }
    return expected == actual;
}

int assertTrue(char* expression, int boolean)
{
    printf("Assertion that %s is true was ", expression);
    if(boolean == 1)
    {
        printf("true!\n");
    }
    else
    {
        printf("false!\n");
    }
    return boolean == 1;
}
