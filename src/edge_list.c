#include "pathfinder.h"

static t_edge *mx_create_edge(t_node *node, int val)
{
    t_edge *edge = (t_edge *)malloc(sizeof(t_edge));

    edge->node = node;
    edge->val = val;
    edge->next = NULL;
    return edge;
}

static void mx_pushedge_front(void **list, t_node *node, int val)
{
    t_edge *edge = mx_create_edge(node, val);

    edge->next = *(t_edge **)list;
    *(t_edge **)list = edge;
}

static void mx_add_to_list(void **list, t_node *node, int val)
{
    t_edge *edge = *(t_edge **)list;
    t_edge *buf = NULL;

    if (edge)
    {
        if (edge->val > val)
            mx_pushedge_front(list, node, val);
        else
        {
            while (edge->next && edge->val < val)
                edge = edge->next;
            if (!edge->next)
                edge->next = mx_create_edge(node, val);
            else
            {
                buf = edge->next;
                edge->next = mx_create_edge(node, val);
                edge->next->next = buf;                
            }
        }
    }
    else
        *list = mx_create_edge(node, val);
}

void mx_add_edge(t_node *n1, t_node *n2, int val)
{
    mx_add_to_list(&n1->edges, n2, val);
    mx_add_to_list(&n2->edges, n1, val);
}
