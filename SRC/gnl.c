/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** get_next_line
*/

#include "../include/my.h"

char pick_my_char(int fd)
{
    static int i = 0;
    static int len = 0;
    static char buff[2];
    static char str[2];
    static int j = 0;

    if (len == 0) {
        len = read(fd, buff, 1);
        j = 0;
    }
    str[i] = buff[j];
    len = len - 1;
    j = j + 1;
    i = i + 1;
    return str[i - 1];
}

char *resize_my_str(char *str, char c, int i)
{
    if (c == '\n')
        str[i] = '\0';
    else if (c == '\0')
        str[i - 1] = '\0';
    return str;
}

char *my_realloc(char *src, int len)
{
    char *str;
    int i = 0;

    str = malloc(sizeof(char) * len * 2);
    while (i <= len) {
        str[i] = src[i];
        i++;
    }
    return (str);
}

char *get_next_line(int fd, int type)
{
    char c;
    char *src = malloc(sizeof(char) * 1 + 1);
    int i = 0;

    c = pick_my_char(fd);
    if (c == 0 && type == 0) {
        my_putstr("exit\n");
        exit(0);
    } else if (c == 0)
        return NULL;
    src[0] = c;
    for (; c != '\n' && c != '\0'; src[i] = c) {
        if (i % 1 == 0)
            src = my_realloc(src, 1 + i + 1);
        i = i + 1;
        c = pick_my_char(fd);
    }
    if (src[0] == '\0')
        return NULL;
    src = resize_my_str(src, c, i);
    return src;
}