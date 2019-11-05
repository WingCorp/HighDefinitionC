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
#include "./iterator/iterator.h"
#include "./stack/stack.h"
#include "./queue/queue.h"
#include "./list/list.h"
#include "./array/array.h"
#include "./fold/fold.h"
#include "./foreach/foreach.h"
#include "./set/set.h"

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
    Array* split = str_split(path, "/");
    char* filename = str(array_item(split, array_length(split) - 1));
    array_destroy(split);
    return filename;
}

char * determine_path_to_dependency(char* own_path, char* dep_rel_path)
{
    char* path = str_replace(own_path, "\\", "/");
    Array* split = str_split(path, "/");
    char* rel_dir = str_join("/", array_iterator(split), str);
    char* dep_rel_source = str_replace(dep_rel_path, ".h", ".c");
    char* rel_path = str_concat(str_concat_c(rel_dir, '/'), dep_rel_source);
    if (rel_path[0] == '/')
    {
        char* g = rel_path;
        rel_path = str_concat(".", rel_path);
        free(g);
    }
    array_destroy(split);
    return rel_path;
}

SourceFile* init_sourcefile(char* path)
{
    SourceFile* s = malloc(sizeof(SourceFile));
    s->path = path;
    s->filename = determine_filename(path);
    s->dependencies = queue_init(3);
    FILE* source = fopen(s->filename, "r");
    char line_buffer[1024];
    int r;
    r = fscanf(source, "%s\n", line_buffer);
    while (r != EOF)
    {
        if (!str_contains(line_buffer, "//") && str_contains(line_buffer, "#include"))
        {
            if (str_contains(line_buffer, "<"))
            {
                goto read_next;
            }
            if (str_contains(line_buffer, "\""))
            {
                char* rel_path_with_junk = str_sub(line_buffer, strlen("#include"), strlen(line_buffer));
                char* rel_path = str_trim(rel_path_with_junk);
                char* dep_path = determine_path_to_dependency(s->path, rel_path);
                char* dep_name = determine_filename(dep_path);
                char* hopefully_not_own_file = str_replace(dep_name, ".h", ".c");
                if (hopefully_not_own_file == s->filename) //gotta eliminate those circles.
                {
                    free(rel_path_with_junk);
                    free(rel_path);
                    free(dep_path);
                    free(dep_name);
                    free(hopefully_not_own_file);
                    continue;
                }
                SourceFile* dep = init_sourcefile(dep_path);
                queue_add(s->dependencies, dref(dep));
                free(rel_path_with_junk);
                free(rel_path);
                free(dep_name);
                free(hopefully_not_own_file);
            }
        }
        read_next: {
            r = fscanf(source, "%s\n", line_buffer);
            continue;
        }
    }
    return NULL;
}

void add_to_build_order(Queue* build_order, SourceFile* sf)
{
    Iterator* qit = queue_iterator(sf->dependencies);
    if (iterator_remaining(qit) == 0)
    {
        iterator_destroy(qit);
        return;
    }
    Option depOpt;
    for (depOpt = iterator_next(qit); isSome(depOpt); depOpt = iterator_next(qit))
    {
        SourceFile* inner = (SourceFile*) ref(coerce(depOpt));
        add_to_build_order(build_order, inner);
    }
    queue_add(build_order, dref(sf));
}

Set* determine_build_order(char* path_to_main)
{
    SourceFile* mainFile = init_sourcefile(path_to_main);
    Queue* build_order = queue_init(3);
    add_to_build_order(build_order, mainFile);
    Set* unique_build_order = set_fromIterator(queue_iterator(build_order));
    return unique_build_order;
}

int build(char* path_to_main, char* output_path, char* flags)
{
    printf("Builidng source: '%s' to %s.", path_to_main, output_path);
    Set* build_order = determine_build_order(path_to_main);
    char* build_order_string = str_join(" ", set_iterator(build_order), str);
    Dynamic cmd_words[] = { dstr("gcc"), dstr(flags), dstr(build_order_string), dstr("-o"), dstr(output_path) };
    Iterator* cmd_iterator = iterator_init_eager(cmd_words, 4);
    char* cmd = str_join(" ", cmd_iterator, str);
    iterator_reset(cmd_iterator);
    foreach(cmd_iterator, delete);
    iterator_destroy(cmd_iterator);
    FILE* fp = popen(cmd, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "HDC build system could not run the following command:\n%s\n", cmd);
        fprintf(stderr, "Check if gcc is properly installed on your system (must be added to PATH variable)\n");
        return EXIT_FAILURE;
    }
    char buffer[BUFSIZ];
    while (fgets(buffer, BUFSIZ, fp) != NULL)
    {
        printf("%s", buffer);
    }
    pclose(fp);
    return EXIT_SUCCESS;
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
        flags = str_join(" ", stack_iterator(custom_flags), str);
    } else {
        flags = default_flags;
    }
    return build(path_to_main, output_path, flags);
}
