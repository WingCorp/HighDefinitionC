#include "primitive.h"
#include <string.h>

Char chr(char val)
{
    Char c = (Char) { .val = val };
    return c;
}

String str(char* val)
{
    return (String) { .val = val, .length = strlen(val) };
}

Int32 i32(int val)
{
    return (Int32) { .val = val };
}

Int64 i64(long val)
{
    return (Int64) { .val = val };
}

Float32 f32(float val)
{
    return (Float32) { .val = val };
}

Float64 f64(double val)
{
    return (Float64) { .val = val };
}

None none() {
    return (None) { .sign = '\0' };
}
