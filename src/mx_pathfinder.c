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
    t_path *p = NULL;

    while (*pathfinder)
    {
        p = (*pathfinder)->next;
        mx_clean_list(((t_path *)(*pathfinder))->node);
        free(*pathfinder);
        *pathfinder = p;        
    }
    *pathfinder = NULL;
}

void mx_get_paths(t_path **pathfinder, t_path *path, t_path *prev, t_node *end, int counter)
{
    for (t_path *p = ((t_node *)prev->node)->path; p; p = p->next)
    {
        if ((*pathfinder)->val > counter + p->val && !mx_contpath(path, p->node))
        {
            mx_pushpath_back(&path, p->node, p->val);
            counter += p->val;
            if (((t_node *)p->node) == end)
                mx_add_to_list(pathfinder, mx_pathcpy(path), counter);
            else
                mx_get_paths(pathfinder, path, p, end, counter);
            counter -= p->val;
            mx_poppath_back(&path);
        }
    }
}
