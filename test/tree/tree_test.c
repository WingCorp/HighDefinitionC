#include "./../../src/comparable/comparable.h"
#include "./../../src/tree/tree.h"
#include "./../assert.h"
#include "./../test.h"

#include <stdio.h>

int put_test()
{
    int expected_size = 1;
    char expected_char = 'A';
    
    Tree* tree = tree_init();
    Comparable key = comparable(di32(1));

    tree_put(tree, key, dchr(expected_char));

    tree_print(tree);

    int actual_size = tree_size(tree);

    char get_1 = chr(coerce(tree_get(tree, key)));
    return assertIntEquals(expected_size, actual_size) && assertCharEquals(expected_char, get_1);
}

int put_more_values_test()
{
    char expected_char = 'A';
    char new_char = 'B';
    
    Tree* tree = tree_init();
    Comparable key_A = comparable(di32(1));
    Comparable key_B = comparable(di32(2));
    
    tree_put(tree, key_A, dchr('A'));
    tree_put(tree, key_B, dchr('B'));

    tree_print(tree);

    char get_1 = chr(coerce(tree_get(tree, key_A)));
    char get_2 = chr(coerce(tree_get(tree, key_B)));
    return assertCharEquals(expected_char, get_1) && assertCharEquals(new_char, get_2);
}

int put_overwrites_existing_value_test()
{
    char expected_char = 'B';

    Tree* tree = tree_init();
    Comparable key = comparable(di32(1));

    tree_put(tree, key, dchr('A'));
    tree_put(tree, key, dchr('B'));

    char get_1 = chr(coerce(tree_get(tree, key)));
    return assertCharEquals(expected_char, get_1);
}

int contains_test()
{
    Tree* tree = tree_init();
    tree_put(tree, comparable(di32(1)), di32(25));
    return assertTrue("Tree contained value with key 1", tree_contains(tree, comparable(di32(1))));
}

int remove_existing_values_test()
{
    Tree* tree = tree_init();
    int start_char = (int)'A';
    int i;
    for(i = 0; i < 10; i++)
    {
        tree_put(tree, comparable(di32(i)), dchr((char) (start_char + i)));
    }
    tree_print(tree);
    for(i = 0; i < 8; i++)
    {
        tree_remove(tree, comparable(di32(i)));
    }
    char expected9th = 'I';
    char expected10th = 'J';
    
    char actual9th = chr(coerce(tree_get(tree, comparable(di32(8)))));
    char actual10th = chr(coerce(tree_get(tree, comparable(di32(9)))));

    return assertCharEquals(expected9th, actual9th) && assertCharEquals(expected10th, actual10th);
}

int main() 
{
    test_declareAndRun("Put single value into tree, size increases by 1", put_test);
    test_declareAndRun("Put more values into tree, see if values are still there", put_more_values_test);
    test_declareAndRun("Put existing values into tree, see if values are overwritten", put_overwrites_existing_value_test);
    test_declareAndRun("Remove some values from a tree of chars, check if remaining remains", remove_existing_values_test);
    return 0;
}
