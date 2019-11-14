#include "pathfinder.h"

int mx_atoi(const char *str)
{
    int num = 0;
    int negative = 0;
    int i = 0; 

    while (str[i] < '0' || str[i] > '9')
    {
        if (str[i] == '-')
            negative = 1;
        ++i;
    }
    while (str[i])
    {
        if (str[i] >= '0' && str[i] <= '9')
            num = num * 10 + str[i] - '0';
        ++i;
    }
    if (negative)
        num *= -1;
    return num;
}

static char *get_digit(char **str)
{
    char *buf = NULL;
    char *s = NULL;
    size_t i = 0;

    while (*(*str))
    {
        if (*(*str) < '0' || *(*str) > '9')
        {
            mx_strdel(&s);
            return NULL;
        }
        buf = mx_realloc(s, i + 2);
        mx_strdel(&s);
        s = buf;
        s[i] = *(*str);
        (*str)++;
        i++;
    }
    if (!i)
        return NULL;
    s[i] = '\0';
    return s;
}

static char *get_word(char **str)
{
    char *buf = NULL;
    char *s = NULL;
    size_t i = 0;

    while (*(*str) != ',' && *(*str) != '-')
    {
        if ((!i && (*(*str) < 'A' || *(*str) > 'Z')) ||
            (i && (*(*str) < 'a' && *(*str) > 'z')) || !(*(*str)))
        {
            mx_strdel(&s);
            return NULL;
        }
        buf = mx_realloc(s, i + 2);
        mx_strdel(&s);
        s = buf;
        s[i] = *(*str);
        (*str)++;
        i++;
    }
    if (!i)
        return NULL;
    s[i] = '\0';
    return s;
}

bool currect_number(char *str)
{
    char *buf = get_digit(&str);

    if (!buf)
        return false;
    mx_strdel(&buf);
    return true;
}

char **parser(char *str)
{
    char **arr = mx_strarrnew(3);
    char *s = NULL;

    if (!str || !(*str))
        return NULL;
    for (int i = 0; i < 3; i++)
    {
        if (i == 2)
            s = get_digit(&str);
        else
            s = get_word(&str);
        if (!s || (!i && *str != '-') || (i == 1 && *str != ','))
        {
            mx_del_strarr(&arr);
            return NULL;
        }
        arr[i] = s;
        str++;
    }
    return arr;
}
