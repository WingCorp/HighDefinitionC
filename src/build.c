/**
 * @file build.c
 * @author Jon Voigt Tøttrup (jon@zendata.dk)
 * @brief A C program that compiles C programs.
 * @version 0.1
 * @date 2019-09-06
 * 
 * @copyright WingCorp (c) 2019
 * 
 */

//I wrote this program to compile HDC,
//but, ironically, it will be using HDC.
#include "./str/str.h"
#include "./stack/stack.h"
#include "./list/list.h"
#include "./fold/fold.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _SourceFile
{
    char* path;
    char* filename;
    List* dependencies;
} SourceFile;

SourceFile* init_sourcefile(char* path)
{
    
}

List* get_build_order(SourceFile* sf)
{
    List* build_order = list_empty();
}

List* determine_build_order(char* path_to_main)
{
    SourceFile* main = init_sourcefile(path_to_main);
    List* build_order = get_build_order(main);
}

int build(char* path_to_main, char* output_path, char* flags)
{
    printf("Builidng source: '%s' to %s.", path_to_main, output_path);
    List* build_order = determine_build_order(path_to_main);

}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        printf("Usage of this program:\nbuild <path to main file> <output path> <flags>\n");
        return 0;
    }
    char* path_to_main = argv[1];
    char* output_path = argv[2];
    int remaining = argc - 3;
    char* default_flags = "-pedantic -Wall -Wextra -rdynamic -Wno-unknown-pragmas";
    Stack* custom_flags;
    char* flags;
    if (remaining > 0)
    {
        custom_flags = stack_init(remaining);
        int i;
        for (i = 0; i < remaining; i++)
        {
            stack_push(custom_flags, dstr(argv[i+3]));
        }
        flags = str_join(" ", stack_iterator(custom_flags), *str);
    } else {
        flags = default_flags;
    }
    return build(path_to_main, output_path, flags);
}
