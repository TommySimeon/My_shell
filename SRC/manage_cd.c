/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** main
*/

#include "my.h"

char *my_strcat(char *dest, char *src)
{
    char *tmp;
    int i = 0;
    int k = 0;

    if (src == NULL || dest == NULL)
        return NULL;
    tmp = malloc(sizeof(char) * (my_strlen(dest) + my_strlen(src)) + 1);
    for (; dest[i] != '\0'; i++)
        tmp[i] = dest[i];
    while (src[k] != '\0') {
        tmp[i + k] = src[k];
        k++;
    }
    tmp[i + k] = '\0';
    return (tmp);
}

int check_cd_arg(char *str)
{
    int i = 0;
    int save = 0;

    for (; str[i] == ' ' || str[i] == '\t'; i++);
    for (; str[i] != ' ' && str[i] != '\t' && str[i] != '\0'; i++);
    for (; str[i] == ' ' || str[i] == '\t'; i++);
    save = i;
    for (; str[i] != ' ' && str[i] != '\0' && str[i] != '\t'; i++);
    for (; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            my_put_error("cd: Too many arguments.\n");
            return -1;
        }
    }
    return save;
}

char *take_cd_arg(char *str, int i)
{
    int j = 0;
    char *arg = malloc(sizeof(char) * my_strlen(str));

    for ( ;str[i] != '\t' && str[i] != ' ' && str[i] != '\0'; i++) {
        arg[j] = str[i];
        j++;
    }
    arg[j] = '\0';
    return arg;
}

int manage_cd(char **board, char *home)
{
    char *arg;
    int status = 0;
    struct stat file;

    if (check_cd_arg(board[ln_arg]) == -1)
        return 1;
    arg = take_cd_arg(board[ln_arg], check_cd_arg(board[ln_arg]));
    if (arg[0] == '\0') {
        status = 1;
        arg = home;
    }
    if (arg[0] == '.')
        status = 1;
    if (status != 1 && stat(arg, &file) == -1) {
        my_put_error(arg);
        my_put_error(": No such file or directory.\n");
        return 1;
    }
    chdir(arg);
    return 0;
}