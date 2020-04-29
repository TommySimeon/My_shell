/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** src
*/

#include "../include/my.h"

void print_my_board(char **board)
{
    for (int i = 0; board[i] != NULL; i++) {
        if (board[i][0] != -1) {
            my_putstr(board[i]);
            my_putstr("\n");
        }
    }
}

void manage_env(char **env, char *str)
{
    int i = 0;
    int j = 0;
    char *cmd = malloc(sizeof(char) * my_strlen(str));

    for (; str[i] == ' ' || str[i] == '\t'; i++);
    for (; str[i] != ' ' && str[i] != '\0'; i++);
    for (; str[i] == ' ' || str[i] == '\t'; i++);
    for (; str[i] != '\0' && str[i] != ' ' && str[i] != '\t'; i++) {
        cmd[j] = str[i];
        j++;
    }
    cmd[j] = '\0';
    if (cmd[0] != '\0') {
        my_put_error("env: '");
        my_put_error(cmd);
        my_put_error("': No such file or directory.\n");
    }
    else
        print_my_board(env);
}

int check_env(char *env, char *flag)
{
    int i = 0;
    char *name = malloc(sizeof(char) * my_strlen(env));

    if (env[0] == -1)
        return -1;
    for (; env[i] != '='; i++)
        name[i] = env[i];
    name[i] = '\0';
    if (my_strcmp(flag, name) == 1) {
        free(name);
        return 1;
    }
    free(name);
    return -1;
}

void my_put_error(char *str)
{
    write(2, str, my_strlen(str));
}