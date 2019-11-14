#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "libmx.h"

void mx_print_file_err(int err, char *file);
void mx_print_line_err(int line);
int mx_atoi(const char *str);
bool currect_number(char *str);
char **parser(char *str);


#endif
