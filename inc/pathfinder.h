#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "libmx.h"


typedef struct s_path
{
    int val;
    void *node;
    struct s_path *next;
}t_path;

typedef struct s_node
{
    char *name;
    t_path *path;
}t_node;

//node
t_node **mx_createnode(int num);
void mx_add_node(t_node **node, char **arr, int num);
void mx_add_path(t_node *n1, t_node *n2, int val);

//path
void mx_poppath_back(t_path **head);
void mx_add_to_list(t_path **list, void *node, int val);
void mx_pushpath_back(t_path **list, void *node, int val);
void mx_clean_list(t_path **path);

//pathfinder
void mx_clean_pathfinder(t_path **pathfinder);
void mx_get_paths(t_path **pathfinder, t_path *path, t_path *prev, t_node *end, int counter);

//error
void mx_print_file_err(int err, char *file);
void mx_print_line_err(int line);
void mx_invalid_number(t_node **node, char **arr, int num);

//parser
char **parser(char *str);
int mx_atoi(const char *str);
bool currect_number(char *str);

#endif
