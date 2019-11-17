#ifndef EDGE_H
#define EDGE_H

#include "node.h"

typedef struct s_edge
{
    int val;
    t_node *node;
    struct s_edge *next;
}t_edge;


void mx_add_edge(t_edge **list, t_node *node, int val);

#endif
