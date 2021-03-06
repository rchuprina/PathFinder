#include "pathfinder.h"

static bool mx_contpath(t_path *path, t_node *node)
{
    for (; path; path = path->next)
    {
        if (((t_node *)path->node) == node)
            return true;
    }
    return false;
}

static t_path *mx_pathcpy(t_path *path)
{
    t_path *copy = NULL;

    for (; path; path = path->next)
        mx_pushpath_back(&copy, path->node, path->val);
    return copy;
}

void mx_clean_pathfinder(t_path **pathfinder)
{
    if (!pathfinder || !(*pathfinder))
        return;

    for (t_path *p = *pathfinder; p->next; p = p->next)
    {
        while (p->node)
        {
            t_path **hui = (t_path **)&(p->node);
            mx_poppath_back(hui);
        }
    }
    while ((*pathfinder)->next)
    {
        t_path *p = (*pathfinder)->next;

        free(*pathfinder);
        *pathfinder = p;
    }
}

void mx_get_paths(t_path **pathfinder, t_path *path, t_path *prev, t_node *end, int counter)
{   
    for (t_path *p = ((t_node *)prev->node)->path; p; p = p->next)
    {
        if (((t_node *)p->node) == end && (*pathfinder)->val >= counter + p->val)
        {
            mx_pushpath_back(&path, p->node, p->val);
            counter += p->val;
            mx_add_to_list(pathfinder, mx_pathcpy(path), counter);
            counter -= p->val;
            mx_poppath_back(&path);
        }
    }
    for (t_path *p = ((t_node *)prev->node)->path; p; p = p->next)
    {
        if (((t_node *)p->node) != end && (*pathfinder)->val >= counter + p->val && 
            !mx_contpath(path, p->node))
        {
            mx_pushpath_back(&path, p->node, p->val);
            counter += p->val;
            mx_get_paths(pathfinder, path, p, end, counter);
            counter -= p->val;
            mx_poppath_back(&path);
        }
    }
}

void mx_print_result(t_node **node, int number)
{
    t_path *path = NULL;
    t_path *pathfinder = NULL;

    for (int i = 0; i < number - 1; i++)
    {
        mx_pushpath_back(&path, node[i], 0);
        mx_add_to_list(&pathfinder, path, 2147483647);
        for (int j = i + 1; j < number; j++)
        {
            mx_get_paths(&pathfinder, path, path, node[j], 0);
            int min = pathfinder->val;
            for (t_path *p = pathfinder; p->val == min; p = p->next)
            {
                mx_printstr("========================================\n");
                mx_printstr("Path: ");
                mx_printstr(node[i]->name);
                mx_printstr(" -> ");
                mx_printstr(node[j]->name);
                mx_printstr("\n");

                mx_printstr("Route: ");
                for (t_path *p2 = p->node; p2; p2 = p2->next)
                {
                    mx_printstr(((t_node *)p2->node)->name);
                    if (p2->next)
                        mx_printstr(" -> ");
                }
                mx_printstr("\n");

                mx_printstr("Distance: ");
                if (((t_node *)((t_path *)p->node)->next->node) != node[j])
                {
                    for (t_path *p2 = ((t_path *)p->node)->next; p2; p2 = p2->next)
                    {
                        mx_printint(p2->val);
                        if (p2->next)
                            mx_printstr(" + ");
                    }
                    mx_printstr(" = ");
                }
                mx_printint(p->val);
                mx_printstr("\n");
                mx_printstr("========================================\n");
            }
            mx_clean_pathfinder(&pathfinder);
        }
        mx_poppath_back(&path);
        mx_poppath_back(&pathfinder);
    }
}

