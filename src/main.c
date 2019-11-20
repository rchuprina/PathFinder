#include "pathfinder.h"

int main(int argc, char **argv)
{
    int fd = 0;
    int number = 0;
    t_node **node = NULL;

    if (argc != 2)
        mx_print_file_err(-3, NULL);
    mx_print_file_err(mx_file_len(argv[1]), argv[1]);
    fd = open(argv[1], O_RDONLY);
    number = mx_get_number(fd);
    node = mx_get_node(number, fd);
    close(fd);
    mx_print_result(node, number);
    mx_exit(node, number);
}
