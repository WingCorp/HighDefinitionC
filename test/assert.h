#ifndef ASSERT_H
#define ASSERT_H
/**
 * Find out whether two given pointers are referencing the same memory.
 **/
int assertRefEquals(void* expected, void* actual);

/**
 * Find out whether two given chars are equal.
 **/
int assertCharEquals(char expected, char actual);

/**
 * Find out whether two given strings are equal.
 */
int assertStringEquals(char* expected, char* actual);

/**
 * Find out whether two given longs are equal.
 **/
int assertLongEquals(long expected, long actual);

/**
 * Find out whether two given integers are equal.
 **/
int assertIntEquals(int expected, int actual);

/**
 * Find out whether two given doubles are equal.
 **/
int assertDoubleEquals(double expected, double actual);

/**
 * Find out whether two given floats are equal.
 **/
int assertFloatEquals(float expected, float actual);

/**
 * Find out whether a given boolean returned true.
 */
int assertTrue(char* expression, int boolean);

#endif
