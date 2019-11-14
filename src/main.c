#include "pathfinder.h"

void quit(char *str, int line)
{
    mx_strdel(&str);
    mx_print_line_err(line);
    exit(0);
}

int main(int argc, char **argv)
{
    int fd = 0;
    int number = 0;
    char *str = NULL;
    char **arr = NULL;

    if (argc != 2)
        mx_print_file_err(-3, NULL);
    fd = open(argv[1], O_RDONLY);
    mx_print_file_err(mx_read_line(&str, 10, '\n', fd), argv[1]);
    if (!currect_number(str))
        mx_print_line_err(1);
    number = mx_atoi(str);
    for (int i = 0; i < number; i++)
    {
        if (mx_read_line(&str, 10, '\n', fd) == -1)
            quit(str, -1);
        arr = parser(str);
        if (!arr)
            quit(str, i + 2);
        mx_print_strarr(arr, "/");
        mx_del_strarr(&arr);
    }
    close(fd);
}
