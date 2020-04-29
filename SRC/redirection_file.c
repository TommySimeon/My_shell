/*
** EPITECH PROJECT, 2019
** redirection file
** File description:
** redirection file
*/

//#include "42sh.h"
#include "../include/my.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *redirect_file(char *str)
{
    char *ret = malloc(sizeof(char) * my_strlen(str));
    char *tmp = malloc(sizeof(char) * my_strlen(str));
    int i = 0;
    int j = 0;

    for (; str[i] != ' ' && str[i] != '\0'; i++)
        tmp[i] = str[i];
    tmp[i] = '\0';
    for (; str[i] != '\0'; i++) {
        ret[j] = str[i];
        j++;
    }
    ret[j] = '\0';
    free(str);
    str = my_strcat(ret, " < ");
    str = my_strcat(str, tmp);
    free(tmp);
    free(ret);
    return str;
}

char *redirection_file(char *str)
{
    if (str != NULL && str[0] == '<') {
        str = &str[1];
        return (redirect_file(str));
    }
    return str;
}