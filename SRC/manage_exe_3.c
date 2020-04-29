/*
** EPITECH PROJECT, 2019
** manage_exe_3.c
** File description:
** manage_exe_3.c
*/

#include "my.h"

int check_or(char **board)
{
    if (my_strcmp(board[ln_arg], "||") != 1) {
        return 0;
    }
    if (output_value != 0) {
        ln_arg++;
        return 0;
    }
    for (; board[ln_arg]; ln_arg++);
    return 1;
}

char **exe_command(arg_t *arg, char **env, char *place)
{
    char *cmd = NULL;

    for (ln_arg = 0; arg->tail != NULL; ln_arg++) {
        prepare_pipe(arg, place);
        if (check_and(arg->tail->board_arg) != 1 && \
        check_or(arg->tail->board_arg) != 1) {
            cmd = take_command(arg->tail->board_arg[ln_arg]);
            if (my_strcmp("setenv", cmd) == 1)
                env = manage_setenv(env, arg->tail->board_arg[ln_arg]);
            else if (my_strcmp("unsetenv", cmd) == 1)
                env = manage_unsetenv(env, arg->tail->board_arg[ln_arg]);
            else
                ln_arg = search_cmd(arg, env, place, ln_arg);
            if (arg->tail->board_arg[ln_arg + 1] == NULL) {
                ln_arg = -1;
                arg->tail = arg->tail->prev;
            }
        }
    }
    return env;
}

int my_strlen_board(char **board)
{
    int i = 0;

    for (; board[i] != NULL; i++);
    return i;
}
