/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** src
*/

#include "../include/my.h"

int verif_arg(char *str)
{
    int i = 0;

    for (; str[i] == ' ' || str[i] == '\t'; i++);
    for (; str[i] != ' ' && str[i] != '\t' && str[i] != '\0'; i++);
    if (str[i] == '\0')
        return 0;
    for (; str[i] != '\0'; i++) {
        for (; str[i] == ' ' || str[i] == '\t'; i++);
        if (str[i] == '\0')
            return 0;
        if (str[i] != '-')
            return 1;
        for (; str[i] != ' ' && str[i] != '\t' && str[i] != '\0'; i++);
    }
    return 0;
}

int check_and(char **board)
{
    if (my_strcmp(board[ln_arg], "&&") != 1)
        return 0;
    if (output_value == 0) {
        ln_arg++;
        return 0;
    }
    for (; board[ln_arg]; ln_arg++);
    return 1;
}

int search_cmd(arg_t *arg, char **env, char *place, int ln_arg)
{
    char *cmd = NULL;

    cmd = take_command(arg->tail->board_arg[ln_arg]);
    if (my_strcmp("exit", cmd) == 1)
        manage_exit(arg->tail->board_arg[ln_arg]);
    else if (my_strcmp("pwd", cmd) == 1)
        manage_pwd();
    else
        env = more_flag(env, cmd, arg, place);
    free(cmd);
    if (arg->pipe_output == 25)
        ln_arg += 2;
    return ln_arg;
}