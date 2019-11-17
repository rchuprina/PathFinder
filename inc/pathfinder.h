#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "libmx.h"

typedef struct s_node
{
    char *name;
    void *edges;
}t_node;

typedef struct s_edge
{
    int val;
    t_node *node;
    struct s_edge *next;
}t_edge;

//node
t_node **mx_createnode(int num);
void mx_add_node(t_node **node, char **arr, int num);

//edge
void mx_add_edge(t_node *n1, t_node *n2, int val);

//error
void mx_print_file_err(int err, char *file);
void mx_print_line_err(int line);
void mx_invalid_number(t_node **node, char **arr, int num);

//parser
char **parser(char *str);
int mx_atoi(const char *str);
bool currect_number(char *str);

#endif
