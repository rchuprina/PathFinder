#include "pathfinder.h"

void mx_print_file_err(int err, char *file)
{
    char *error = NULL;

    if (err < 0)
    {
        if (err == -1)
            error = mx_replace_substr("error: file [filename] is empty", "[filename]", file);
        if (err == -2)
            error = mx_replace_substr("error: file [filename] doesn't exist", "[filename]", file);
        if (err == -3)
            error = mx_strdup("usage: ./pathfinder [filename]");
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
        error = mx_replace_substr("error: line num isn't valid", "num", itoa);
        mx_strdel(&itoa);
    }
    else
        error = mx_strdup("error: invalid number of islands");
    write(2, error, mx_strlen(error));
    mx_strdel(&error);
    exit(0);
}
