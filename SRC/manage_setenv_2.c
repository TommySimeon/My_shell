/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** manage_setenv_2
*/

#include "../include/my.h"

int verif_name_env(char *name)
{
    for (int i = 0; name[i] != '\0';) {
        if ((name[i] >= 'A' && name[i] <= 'Z') ||
        (name[i] >= 'a' && name[i] <= 'z'))
            i++;
        else {
            my_put_error("setenv: Variable name must \
contain alphanumeric characters.\n");
            output_value = 1;
            return -1;
        }
    }
    return 1;
}