/**
 * Math
 * @brief An attempt at a simple math module in C.
 * 
 * @file math.c
 * @author Jon Voigt Tøttrup
 * @date 2018-06-14
 */

long absl(long l) 
{
    return (l < 0L) ? l * -1L : l;
}

int abs(int i) 
{
    return (i < 0) ? i * -1 : i;
}

double absd(double d)
{
    return (d < 0.) ? d * -1. : d;
}

float absf(float f)
{
    return (f < 0.f) ? f * -1.f : f;
}

int ilog10(int i)
{
    return 
        (i > 999999999) ? 9 : (i >= 99999999) ? 8 :
        (i > 9999999) ? 7 : (i > 999999) ? 6 : (i > 99999) ? 5 : 
        (i > 9999) ? 4 : (i > 999) ? 3 : (i > 99) ? 2 : (i > 9) ? 1 : 0;
}


float sqrtf(float num)
{
    float guess, e, upperbound;
    guess = 1;
    e = 0.001f;
    do 
    {
        upperbound = num / guess;
        guess = (upperbound + guess) / 2;
    } while (!(guess * guess >= num - e && 
               guess * guess <= num + e));
    return guess;
}

