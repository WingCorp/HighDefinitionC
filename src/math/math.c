/**
 * Math
 * @brief An attempt at a simple math module in C.
 * 
 * @file math.c
 * @author Jon Voigt Tøttrup
 * @date 2018-06-14
 */

double math_epsilon = 0.0000001;

long math_longAbs(long l) 
{
    if(l < 0) 
    {
        return l * -1;
    }
    else return l;
}

int math_intAbs(int i) 
{
    return (int) math_longAbs((long) i);
}

double math_doubleAbs(double d)
{
    if(d + math_epsilon < 0)
    {
        return d * -1;
    }
    else return d;
}

float math_floatAbs(float f)
{
    return (float) math_doubleAbs((double) f);
}

int ilog10(int i)
{
    return 
        (i > 999999999) ? 9 : (i >= 99999999) ? 8 :
        (i > 9999999) ? 7 : (i > 999999) ? 6 : (i > 99999) ? 5 : 
        (i > 9999) ? 4 : (i > 999) ? 3 : (i > 99) ? 2 : (i > 9) ? 1 : 0;
}
