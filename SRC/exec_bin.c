/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** exec_bin
*/

#include "my.h"

char *get_filename(char *cmd)
{
    char *filename;
    int fd = 0;

    if (cmd[0] != '.' && cmd[0] != '<' && cmd[0] != '>')
        filename =  my_strcat("/bin/", cmd);
    else
        return NULL;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        filename = my_strcat("/usr/bin/", cmd);
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return NULL;
    return filename;
}

char **str_to_word_array(char *str)
{
    char **board = malloc_my_board(my_strlen(str), my_strlen(str));
    int ln = 0;
    int cln = 0;

    for (int i = 0; str[i] != '\0' && str[i] != '\n'; i++) {
        for (; str[i] == ' ' || str[i] == '\t'; i++);
        if (str[i] == '\n' || str[i] == '\0') {
            board[ln] = NULL;
            return board;
        }
        for (; str[i] != ' ' && str[i] != '\t' && \
            str[i] != '\n' && str[i] != '\0'; i++, cln++)
            board[ln][cln] = str[i];
        board[ln][cln] = '\0';
        ln++;
        cln = 0;
    }
    board[ln] = NULL;
    return board;
}

int manage_echo(char **arg_board)
{
    int new_line = 1;
    char **board = str_to_word_array(arg_board[ln_arg]);

    if (board[1] == NULL) {
        my_putstr("\n");
        return 0;
    }
    if (my_strcmp("-n", board[1]) == 1)
        new_line = 2;
    for (int i = new_line; board[i] != NULL && board[i][0] != '|' && \
    board[i][0] != '>' && board[i][0] != '<' && board[i][0] != '&'; i++) {
        if (my_strcmp("$?", board[i]) == 1)
            my_put_nbr(output_value); else
            my_putstr(board[i]);
        if (board[i + 1] != NULL)
            my_putstr(" ");
    }
    if (new_line == 1)
        my_putstr("\n");
    return 0;
}

char **more_flag_2(char **env, char *cmd, arg_t *arg, char *place)
{
    if (my_strcmp("cd", cmd) == 1)
        output_value = manage_cd(arg->tail->board_arg, arg->home);
    else {
        if (cmd != NULL && cmd[0] == '|') {
            my_putstr("Invalid null command.\n");
            return env;
        }
        if (cmd == NULL || cmd[0] == '\0')
            return env;
        if (get_filename(cmd) == NULL) {
            my_putstr(cmd);
            my_putstr(": Command not found.\n");
            output_value = 1;
            return env;
        }
        arg->pipe_output = manage_exe(arg->tail->board_arg, env, \
        get_filename(cmd), place);
    }
    return env;
}

char **more_flag(char **env, char *cmd, arg_t *arg, char *place)
{
    if (my_strcmp("echo", cmd) == 1) {
        output_value = manage_echo(arg->tail->board_arg);
        return env;
    }
    else if ((cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/') {
        output_value = manage_exe(arg->tail->board_arg, env, cmd, place);
        return env;
    }
    return more_flag_2(env, cmd, arg, place);
}