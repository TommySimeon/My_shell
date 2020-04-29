/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** src
*/

#include "../include/my.h"

char *my_strcpy(char *dest, char *src)
{
    int i = 0;

    if (src == NULL)
        return NULL;
    dest = malloc(sizeof(char) * (my_strlen(src) + 1));
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

int string_to_int(const char *str)
{
    int i = 0;
    int nb = 0;
    int neg = 0;
    int off = 1;

    if (str[0] == '-')
        neg = 1;
    while (str[i] != '\0')
        i++;
    i--;
    while (i >= neg) {
        nb = (str[i] - '0') * off + nb;
        off = off * 10;
        i--;
    }
    if (neg == 1)
        return (nb * (-1));
    return (nb);
}

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_put_nbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        my_put_nbr(nb * (-1));
    }
    else if (nb > 9) {
        my_put_nbr(nb / 10);
        my_putchar(nb % 10 + '0');
    }
    else if (nb <= 9)
        my_putchar('0' + nb);
}
