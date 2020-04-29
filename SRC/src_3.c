/*
** EPITECH PROJECT, 2019
** src_3.c
** File description:
** src_3.c
*/

#include "my.h"

char *int_to_char(int nbr)
{
    int i = 0;
    char *str = malloc(sizeof(char) * nbr + 1);

    while (nbr >= 10) {
        str[i] = (nbr % 10) + 48;
        nbr = nbr / 10;
        i++;
    }
    str[i] = nbr + 48;
    str[i + 1] = '\0';
    str = my_revstr(str);
    return str;
}

char *my_revstr(char *str)
{
    char *tmp = malloc(sizeof(char) * my_strlen(str) + 1);
    int i = my_strlen(str) - 1;
    int j = 0;

    while (i != -1) {
        tmp[j] = str[i];
        i--;
        j++;
    }
    tmp[j] = '\0';
    str = tmp;
    return str;
}
