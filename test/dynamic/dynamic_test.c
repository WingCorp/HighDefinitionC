#include "./../../src/dynamic/dynamic.h"
#include "./../assert.h"
#include "./../test.h"
#include <string.h>

int dynamic_int32CreatesDynamic()
{
    int testValue = 500;
    Dynamic integer;
    integer = di32(testValue);
    return assertIntEquals(testValue, i32(integer));
}

typedef struct _TestStruct
{
    char* someString;
} TestStruct;

int dynamic_refCanStoreStruct()
{
    char* testString = "TestStringLol";
    TestStruct testStruct = (TestStruct) { .someString = testString };
    Dynamic dRef = dref(&testStruct);
    void* refVal = ref(dRef);
    TestStruct refStruct = * ((TestStruct*) (refVal));
    return assertStringEquals(testString, refStruct.someString);
}

int dynamic_refCanStoreString()
{
    char* testString = "TestString";
    Dynamic dRef = dref(testString);
    char* refVal = ref(dRef);
    return assertIntEquals(0, strcmp(testString, refVal));
}

int main()
{
    test_declareAndRun("Dynamic int32 is equivalent to regular int", dynamic_int32CreatesDynamic);
    test_declareAndRun("Dynamic ref can store Struct properly", dynamic_refCanStoreStruct);
    test_declareAndRun("Dynamic ref can store String properly", dynamic_refCanStoreString);
    return 0;
}