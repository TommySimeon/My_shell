/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** my shell
*/

#include "my.h"

void manage_pwd(void)
{
    char *folder = getcwd(NULL, 5000);

    if (folder == NULL)
        my_put_error(":(");
    else
        my_putstr(folder);
    write(1, "\n", 1);
}

void display_my_prompt(void)
{
    char *folder;

    my_putstr("\033[0;32m[~");
    folder = getcwd(NULL, 5000);
    if (folder == NULL)
        my_putstr(":(");
    else
        my_putstr(folder);
    my_putstr("]<>[");
    my_putstr("]\n\033[0;34m8========> : ");
    my_putstr("\033[0;37m");
}

char *add_pipe_arg(char *str, char *place)
{
    char *new_str = malloc(sizeof(char) * (my_strlen(str) \
        + my_strlen(place) + 40));
    char *path = add_place("/manage_pipe/pipe.tmp", place);
    int i = 0;
    int j = 0;

    for (; str[i] != '\0'; i++)
        new_str[i] = str[i];
    new_str[i] = ' ';
    i++;
    for (; path[j] != '\0'; j++, i++)
        new_str[i] = path[j];
    new_str[i] = '\0';
    return new_str;
}

int my_sh(char **env, char *place)
{
    char *str;
    char *home = take_home(env);
    arg_t *arg;

    while (1) {
        display_my_prompt();
        str = get_next_line(0, 0);
        if (output_value > 255 || output_value < -255)
            output_value = 0;
        arg = slash_cmd(str);
        arg->home = home;
        arg->pipe_output = 0;
        env = exe_command(arg, env, place);
    }
}