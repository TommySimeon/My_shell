/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** manage_unsetenv
*/

#include "../include/my.h"

char **malloc_my_board(int ln, int cln)
{
    char **board = malloc(sizeof(char *) * (ln + 1));
    int i = 0;

    for (; i != ln; i++)
        board[i] = malloc(sizeof(char) * (cln + 1));
    board[i] = NULL;
    return board;
}

char **remove_flag(char *flag, char **env)
{
    int i = 0;

    for (; env[i] != NULL && check_env(env[i], flag) != 1; i++);
    if (env[i] == NULL)
        return env;
    env[i][0] = -1;
    env[i][1] = '\0';
    return env;
}

char **manage_unsetenv(char **env, char *str)
{
    int i = 0;
    char *flag;

    for (; str[i] == ' ' || str[i] == '\t'; i++);
    for (; str[i] != ' ' && str[i] != '\t'; i++);
    for (; str[i] == ' ' || str[i] == '\t'; i++);
    for (int j = 0; str[i] != '\0'; j = 0) {
        flag = malloc(sizeof(char) * my_strlen(str));
        for (; str[i] == ' ' || str[i] == '\t'; i++);
        for (; str[i] != ' ' && str[i] != '\0' && str[i] != '\t'; i++) {
            flag[j] = str[i];
            j++;
        }
        flag[j] = '\0';
        env = remove_flag(flag, env);
    }
    return env;
}