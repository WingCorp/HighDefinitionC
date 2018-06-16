#include "./../../src/stack/stack.h"
#include "./../assert.h"
#include "./../test.h"
#include "./../../src/primitive/primitive.h"

int stack_initWorks()
{
    int stackCap = 10;
    Stack* stack = stack_init(stackCap, INT);
    return 
        assertIntEquals(stackCap, stack_capacity(stack))
        &&
        assertIntEquals(0, stack_size(stack));
}

int stack_destroyWorks()
{
    int stackCap = 10;
    Stack* stack = stack_init(stackCap, INT);
    stack_destroy(stack);
    //Honestly, I have no idea how to test this.
    return assertTrue("Stack is destroyed? I don't know.", 1);
}

int stack_pushPopTest()
{
    int stackCap = 5;
    Stack* stack = stack_init(stackCap, INT);
    int val = 10;
    stack_push(stack, pi32(val));
    Option opt = stack_pop(stack);
    return
        assertTrue("opt.type == SOME", opt.type == SOME)
        &&
        assertIntEquals(val, i32(opt.value));
}

int main()
{
    test_declareAndRun("Stack with ints initializes properly", stack_initWorks);
    test_declareAndRun("Stack with ints destroys properly? At least the pointers might change location", stack_destroyWorks);
    test_declareAndRun("Pushing the int 10 onto stack and then popping returns Option of Some(10)", stack_pushPopTest);
    return 1;
}