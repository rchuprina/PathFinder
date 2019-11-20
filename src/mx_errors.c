#include "pathfinder.h"

void mx_print_file_err(int err, char *file)
{
    char *error = NULL;

    if (err < 0)
    {
        if (err == -1)
            error = mx_replace_substr("error: file [filename] doesn't exist\n", "[filename]", file);
        if (err == -2)
            error = mx_replace_substr("error: file [filename] is empty\n", "[filename]", file);
        if (err == -3)
            error = mx_strdup("usage: ./pathfinder [filename]\n");
        write(2, error, mx_strlen(error));
        mx_strdel(&error);
        exit(0);

    }
}

void mx_print_line_err(int line)
{
    char *error = NULL;
    char *itoa = NULL;

    if (line >= 0)
    {
        itoa = mx_itoa(line);
        error = mx_replace_substr("error: line num isn't valid\n", "num", itoa);
        mx_strdel(&itoa);
    }
    else
        error = mx_strdup("error: invalid number of islands\n");
    write(2, error, mx_strlen(error));
    mx_strdel(&error);
    exit(0);
}

void mx_invalid_number(t_node **node, char **arr, int num)
{
    free(arr[2]);
    free(arr);
    for (int i = 0; i < num; i++)
    {
        if (node[i]->name)
            free(node[i]->name);
        while (node[i]->path)
            mx_poppath_back(&node[i]->path);
    }
    mx_print_line_err(-1);
}

void mx_exit(t_node **node, int number)
{
    for (int i = 0; i < number; i++)
    {
        free(node[i]->name);
        while(node[i]->path)
            mx_poppath_back(&node[i]->path);
        free(node[i]);
    }
    free(node);
    exit(0);
}
