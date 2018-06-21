#ifndef TEST_H
#define TEST_H

/**
 * @brief Runs a testFunction in a subProcess and makes an assertion on the output.
 * 
 * @param testFunction A function to test functionality that requires a separate thread.
 * @param assertFunction A function to make assertions on the testFunction's output.
 * @return int the result of the assertFunction.
 */
int test_runInSubProcess(void (*testFunction) (void), int (*assertFunction) (char* output));

/**
 * @brief Declare a test in stdout and evaluate the result.
 * 
 * @param testName The name of the test, to announce.
 * @param testFunction A test function, must take nothing and return an int, 1 for passed, else not passed.
 */
void test_declareAndRun(char* testName, int (*testFunction) (void));

#endif
