#include "./../../src/dynamic/dynamic.h"
#include "./../assert.h"
#include "./../test.h"

#include <string.h>
#include <stdio.h>

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

int dynamic_pairsCanStoreDynamics()
{
    int i = 0;
    int j = 1;
    Dynamic dPair = pair(di32(i), di32(j));
    int fstVal = i32(fst(dPair));
    int sndVal = i32(snd(dPair));
    return assertIntEquals(i, fstVal) && assertIntEquals(j, sndVal);
}

int dynamic_strsWorkAsExpected()
{
    Dynamic dstring = dstr("DYNAMIC");
    return assertStringEquals("DYNAMIC", str(dstring));
}

int dynamic_strsCanBeStoredInPairs()
{
    Dynamic left = dstr("LEFT");
    Dynamic right = dstr("RIGHT");
    Dynamic p = pair(left, right);
    return assertStringEquals("LEFT", str(fst(p))) && assertStringEquals("RIGHT", str(snd(p)));
}

int main()
{
    test_declareAndRun("Dynamic int32 is equivalent to regular int", dynamic_int32CreatesDynamic);
    test_declareAndRun("Dynamic ref can store Struct properly", dynamic_refCanStoreStruct);
    test_declareAndRun("Dynamic ref can store String properly", dynamic_refCanStoreString);
    test_declareAndRun("Dynamic pair functions work properly", dynamic_pairsCanStoreDynamics);
    test_declareAndRun("Dynamic strings can be initialized properly", dynamic_strsWorkAsExpected);
    test_declareAndRun("Dynamic strings can be stored in pairs", dynamic_strsCanBeStoredInPairs);
    return 0;
}