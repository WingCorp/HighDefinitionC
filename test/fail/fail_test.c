#include "./../../src/fail/fail.h"

int main()
{
    failwithf("%d + %d = %d If you are reading this, you just failed!\n", 1, 2, 3);
}