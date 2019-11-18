#include "pathfinder.h"

static t_path *mx_create_path(void *node, int val)
{
    t_path *path = (t_path *)malloc(sizeof(t_path));

    path->node = node;
    path->val = val;
    path->next = NULL;
    return path;
}

static void mx_pushpath_front(t_path **list, void *node, int val)
{
    t_path *path = mx_create_path(node, val);

    path->next = *list;
    *list = path;
}

void mx_pushpath_back(t_path **list, void *node, int val)
{
    if (*list)
    {
        t_path *p = *list;

        while (p->next)
            p = p->next;
        p->next = mx_create_path(node, val);
    }
    else
        *list = mx_create_path(node, val);
}

void mx_add_to_list(t_path **list, void *node, int val)
{
    t_path *path = *list;
    t_path *buf = NULL;

    if (path)
    {
        if (path->val > val)
            mx_pushpath_front(list, node, val);
        else
        {
            while (path->next && path->val < val)
                path = path->next;
            if (!path->next)
                path->next = mx_create_path(node, val);
            else
            {
                buf = path->next;
                path->next = mx_create_path(node, val);
                path->next->next = buf;                
            }
        }
    }
    else
        *list = mx_create_path(node, val);
}

void mx_poppath_back(t_path **head)
{
    if (*head)
    {
        if ((*head)->next)
        {
            t_path *p = *head;

            while (p->next->next)
                p = p->next;
            free(p->next);
            p->next = NULL;
        }
        else
        {
            free(*head);
            *head = NULL;
        }
    }
}
