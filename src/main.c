#include "pathfinder.h"

int mx_get_number(int fd)
{
    int number = 0;
    char *str = NULL;

    if (mx_read_line(&str, 10, '\n', fd) == -1)
    {
        mx_strdel(&str);
        mx_print_line_err(1);
    }
    if (!currect_number(str))
    {
        mx_strdel(&str);
        mx_print_line_err(1);
    }
    number = mx_atoi(str);
    mx_strdel(&str);
    return number;
}

t_node **mx_get_node(int number, int fd)
{
    t_node **node = mx_createnode(number);
    char *str = NULL;
    char **arr = NULL;
    int line = 2;

    while (mx_read_line(&str, 10, '\n', fd) != -1)
    {
        arr = parser(str);
        if (!arr)
        {
            mx_strdel(&str);
            mx_print_line_err(line);
        }
        mx_add_node(node, arr, number);
        line++;
    }
    if (*str)
    {
        mx_strdel(&str);
        mx_print_line_err(line);
    }
    mx_strdel(&str);
    return node;
}

int main(int argc, char **argv)
{
    int fd = 0;
    int number = 0;
    t_node **node = NULL;
    t_path *path = NULL;
    t_path *pathfinder = NULL;

    if (argc != 2)
        mx_print_file_err(-3, NULL);
    mx_print_file_err(mx_file_len(argv[1]), argv[1]);
    fd = open(argv[1], O_RDONLY);
    number = mx_get_number(fd);
    node = mx_get_node(number, fd);
    close(fd);
    for (int i = 0; i < number - 1; i++)
    {
        mx_pushpath_back(&path, node[i], 0);
        mx_add_to_list(&pathfinder, path, 2147483647);
        for (int j = i + 1; j < number; j++)
        {
            mx_get_paths(&pathfinder, path, path, node[j], 0);
            mx_printint(pathfinder->val);
            //mx_clean_pathfinder(&pathfinder);
            mx_clean_list(&path);
            
        }
    }
    /*for (int i = 0; i < number; i++)
    {
        for (t_path *e = node[i]->path; e; e = e->next)
        {
            mx_printstr(node[i]->name);
            mx_printstr(" - ");
            mx_printstr(((t_node *)e->node)->name);
            mx_printstr(" ");
            mx_printint(e->val);
            mx_printstr("\n");
        }
    }
    mx_printstr(((t_node *)((t_node *)node[0]->path->next->node)->path->node)->name);
    //mx_printstr(((t_path *)((t_path *)node[0]->path)->next->node->path)->node->name);
    mx_printstr("\n");*/
}
