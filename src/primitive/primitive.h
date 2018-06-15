/**
 * @brief Union type for wrapping primitive types.
 * 
 * @file primitive.h
 * @author WingCorp
 * @date 2018-06-15
 */

#include "char.h"
#include "float.h"
#include "integer.h"
#include "none.h"

typedef union _Primitive {
    Char chrVal;
    String strVal;
    Int32 i32Val;
    Int64 i64Val;
    Float32 f32Val;
    Float64 f64Val;
    None none;
} Primitive;

Char chr(char val);
String str(char* val);
Int32 i32(int val);
Int64 i64(long val);
Float32 f32(float val);
Float64 f64(double val);
None none();

Primitive pchr(char val);
Primitive pstr(char* val);
Primitive pi32(int val);
Primitive pi64(long val);
Primitive pf32(float val);
Primitive pf64(double val);
Primitive pnone();
