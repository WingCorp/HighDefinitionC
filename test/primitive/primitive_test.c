#include "./../../src/primitive/primitive.h"
#include "./../assert.h"
#include "./../test.h"

int primitive_int32CreatesPrimitive()
{
    int testValue = 500;
    Primitive integer;
    integer = pi32(testValue);
    return assertIntEquals(testValue, i32(integer));
}

typedef struct _TestStruct
{
    char* someString;
} TestStruct;

int primitive_refCanStoreStruct()
{
    char* testString = "TestStringLol";
    TestStruct testStruct = (TestStruct) { .someString = testString };
    Primitive primRef = pref(&testStruct);
    void* refVal = ref(primRef);
    TestStruct refStruct = * ((TestStruct*) (refVal));
    return assertStringEquals(testString, refStruct.someString);
}

int main()
{
    test_declareAndRun("Primitive int32 is equivalent to regular int", primitive_int32CreatesPrimitive);
    test_declareAndRun("Primitive ref can store Struct properly", primitive_refCanStoreStruct);
    return 1;
}