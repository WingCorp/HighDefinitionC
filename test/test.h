/**
 * @brief Declare a test in stdout and evaluate the result.
 * 
 * @param testName The name of the test, to announce.
 * @param testFunction A test function, must take nothing and return an int, 1 for passed, else not passed.
 */
void test_declareAndRun(char* testName, int (*testFunction) (void));