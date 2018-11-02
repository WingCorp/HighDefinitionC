#include "./src/dynamic/dynamic.h"
#include "./src/comparable/comparable.h"
#include "./src/option/option.h"
#include "./src/tree/tree.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    Tree* tree = tree_init();
    int start_char = (int)'A';
    int i;
    for(i = 0; i < 11; i++)
    {
        printf("Inserting %c at %d\n", (char) (start_char + i), i);
        tree_put(tree, comparable(di32(i)), dchr((char) (start_char + i)));
    }
    printf("Inserted letters into tree.\n");
    tree_print(tree);
    for(i = 0; i < 9; i++)
    {
        printf("Removing letter at %d\n", i);
        tree_remove(tree, comparable(di32(i)));
    }
    char expected9th = 'I';
    char expected10th = 'J';
    
    char actual9th = chr(coerce(tree_get(tree, comparable(di32(9)))));
    char actual10th = chr(coerce(tree_get(tree, comparable(di32(10)))));
    
    printf("expected: %c, got %c\n", expected9th, actual9th);
    printf("expected: %c, got %c\n", expected10th, actual10th);

    return 0;
}
