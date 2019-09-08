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
#include "./queue/queue.h"
#include "./list/list.h"
#include "./fold/fold.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _SourceFile
{
    char* path;
    char* filename;
    Queue* dependencies;
} SourceFile;

char* determine_filename(char* path)
{
    if (str_contains("\\", path))
    {
        path = str_replace(path, "\\", "/");
    }
    Dynamic split = str_split(path, "/");
    int split_len = i32(snd(split));
    char** fragments = (char**) ref(fst(split));
    char* filename = fragments[split_len - 1];
    return filename;
}

char * determine_path_to_dependency(char* own_path, char* dep_rel_path)
{
    char* path = str_replace(own_path, "\\", "/");
    Dynamic split = str_split(path, "/");
    int split_len = i32(snd(split));
    char** fragments = (char**) ref(fst(split));
    char* rel_dir = str_join("/", iterator_init_pointer(fragments, *dstr, split_len - 1), *str);
    char* dep_rel_source = str_replace(dep_rel_path, ".h", ".c");
    char* rel_path = str_concat(str_concat_c(rel_dir, '/'), dep_rel_source);
    if (rel_path[0] == '/')
    {
        char* g = rel_path;
        rel_path = str_concat(".", rel_path);
        free(g);
    }
    return rel_path;
}

SourceFile* init_sourcefile(char* path)
{
    SourceFile* s = malloc(sizeof(SourceFile));
    s->path = path;
    s->filename = determine_filename(path);
    s->dependencies = queue_init(3);
    FILE* source = fopen(s->filename, 'r');
    char line_buffer[512];
    int r;
    r = fscanf(source, "%s\n", line_buffer);
    while (r != EOF)
    {
        if (str_contains(line_buffer, "#include"))
        {
            if (str_contains(line_buffer, "<"))
            {
                goto read_next;
            }
            if (str_contains(line_buffer, "\""))
            {
                char* rel_path_with_junk = str_sub(line_buffer, strlen("#include"), strlen(line_buffer));
                char* rel_path = str_trim(rel_path_with_junk);
                free(rel_path_with_junk);
                
            }
        }
        read_next: {
            r = fscanf(source, "%s\n", line_buffer);
            continue;
        }
    }
    return NULL;
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
