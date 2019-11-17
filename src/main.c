#include "pathfinder.h"

int main(int argc, char **argv)
{/*
    argc++;
    argv++;
    head[0]->name = mx_strdup("A");
    head[1]->name = mx_strdup("B");
    head[2]->name = mx_strdup("C");
    mx_add_edge(head[0], head[2], 10);
    mx_add_edge(head[0], head[1], 11);

    mx_printstr(((t_edge *)head[0]->edges)->node->name);

    */
    int fd = 0;
    int number = 0;
    int line = 1;
    char *str = NULL;
    char **arr = NULL;
    t_node **node = NULL;

    if (argc != 2)
        mx_print_file_err(-3, NULL);
    mx_print_file_err(mx_file_len(argv[1]), argv[1]);
    fd = open(argv[1], O_RDONLY);
    while (mx_read_line(&str, 10, '\n', fd) != -1)
    {
        if (line == 1)
        {
            if (!currect_number(str))
                mx_print_line_err(line);
            number = mx_atoi(str);
            node = mx_createnode(number);
        }
        else
        {
            arr = parser(str);
            if (!arr)
            {
                mx_strdel(&str);
                mx_print_line_err(line);
            }
            mx_add_node(node, arr, number);
        }
        line++;
    }
    if (*str)
    {
        mx_strdel(&str);
        mx_print_line_err(line);
    }
    close(fd);
    for (int i = 0; i < number; i++)
    {
        for (t_edge *e = (t_edge *)node[i]->edges; e; e = e->next)
        {
            mx_printstr(node[i]->name);
            mx_printstr(" - ");
            mx_printstr(e->node->name);
            mx_printstr(" ");
            mx_printint(e->val);
            mx_printstr("\n");
        }
    }
}
