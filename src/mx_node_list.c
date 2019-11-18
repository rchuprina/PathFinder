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

    if(indexa < 0 || indexb < 0)
        mx_invalid_number(node, arr, num);    
    mx_add_path(node[indexa], node[indexb], mx_atoi(arr[2]));
    mx_strdel(&arr[2]);
    free(arr);
}

void mx_add_path(t_node *n1, t_node *n2, int val)
{
    mx_add_to_list(&n1->path, n2, val);
    mx_add_to_list(&n2->path, n1, val);
}
