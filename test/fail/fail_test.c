#include "./../../src/fail/fail.h"

int main()
{
    failwith("%d + %d = %d If you are reading this, you just failed!\n", 1, 2, 3);
}