#include "pathfinder.h"

static int get_index(t_node **node, char *name, int num)
{
    int i = 0;

    while (i < num && node[i]->name && mx_strcmp(name, node[i]->name) != 0)
        i++;
    if (i == num)
        return -1;
    else if (!node[i]->name)
        node[i]->name = name;
    else if (mx_strcmp(name, node[i]->name) == 0)
        mx_strdel(&name);
    return i;
}

t_node **mx_createnode(int num)
{
    t_node **node = (t_node **)malloc(num * sizeof(t_node *));

    for (int i = 0; i < num; i++)
    {
        node[i] = (t_node *)malloc(sizeof(t_node));
        node[i]->name = NULL;
        node[i]->path = NULL;
    }
    return node;
}

void mx_add_node(t_node **node, char **arr, int num)
{
    int indexa = get_index(node, arr[0], num);
    int indexb = get_index(node, arr[1], num);

    if (indexa < 0 || indexb < 0)
    {
        if (indexa < 0)
            mx_strdel(&arr[0]);
        else
            mx_strdel(&arr[1]);
        mx_invalid_number(node, arr, num);
    }
    mx_add_path(node[indexa], node[indexb], mx_atoi(arr[2]));
    mx_strdel(&arr[2]);
    free(arr);
}

void mx_add_path(t_node *n1, t_node *n2, int val)
{
    mx_add_to_list(&n1->path, n2, val);
    mx_add_to_list(&n2->path, n1, val);
}

int mx_get_number(int fd)
{
    int number = 0;
    char *str = NULL;

    if (mx_read_line(&str, 10, '\n', fd) == -1)
    {
        mx_strdel(&str);
        mx_print_line_err(1);
    }
    if (!mx_currect_number(str))
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
        arr = mx_parser(str);
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
