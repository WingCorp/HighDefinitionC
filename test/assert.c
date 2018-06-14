#include "assert.h"
#include <stdio.h>

void printAssertRefs(long expectedRef, long actualRef)
{
    printf("Assertion that ref %ld and ref %ld were equal was ", expectedRef, actualRef);
}

int assertRefEquals(void* expected, void* actual)
{
    printAssertRefs((long) expected, (long) actual);
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
    printAssertRefs((long) expected, (long) actual);
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

int assertLongEquals(long expected, long actual)
{
    printAssertRefs((long) expected, (long) actual);
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
    printAssertRefs((long) expected, (long) actual);
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
    printAssertRefs((long) expected, (long) actual);
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
    printf("Assertion that floats at ref %ld and ref %ld were equal was ", (long) expected, (long) actual);
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

int assertTrue(int boolean)
{
    printf("Assertion that the given boolean expression result is true was ");
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
