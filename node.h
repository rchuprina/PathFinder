#ifndef NODE_H
#define NODE_H

#include "edge.h"

typedef struct s_node
{
    char *name;
    t_edge *edges;
}t_node;

#endif
