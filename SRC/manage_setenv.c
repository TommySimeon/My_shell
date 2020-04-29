/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** manage_setenv
*/

#include "my.h"

char **add_name_env(char **env, char *arg1)
{
    int i = 0;
    int j = 0;

    if (arg1[0] == '\0') {
        print_my_board(env);
        return env;
    }
    for (; env[i] != NULL && check_env(env[i], arg1) != 1; i++);
    if (env[i] != NULL) {
        for (; env[i][j] != '='; j++);
        env[i][j + 1] = '\0';
        return env;
    }
    env = realloc_my_board(env);
    env[i] = malloc(sizeof(char) * my_strlen(arg1) + 2);
    for (; arg1[j] != '\0'; j++)
        env[i][j] = arg1[j];
    env[i][j] = '=';
    env[i][j + 1] = '\0';
    return env;
}

char **add_new_value_env_2(char **env, char *arg1, char *arg2, int i)
{
    int k = 0;
    int j = 0;

    env = realloc_my_board(env);
    env[i] = malloc(sizeof(char) * my_strlen(arg2) + my_strlen(arg1) + 2);
    for (; arg1[j] != '\0'; j++)
        env[i][j] = arg1[j];
    env[i][j] = '=';
    for (j = j + 1; arg2[k] != '\0'; k++) {
        env[i][j] = arg2[k];
        j++;
    }
    env[i][j] = '\0';
    return env;
}

char **add_new_value_env(char **env, char *arg1, char *arg2)
{
    int i = 0;
    int j = 0;
    int k = 0;

    for (; env[i] != NULL && check_env(env[i], arg1) != 1; i++);
    if (env[i] != NULL) {
        env[i] = my_realloc(env[i], my_strlen(arg2) + 2);
        for (; env[i][j] != '='; j++);
        j++;
        for (; arg2[k] != '\0'; k++) {
            env[i][j] = arg2[k];
            j++;
        }
        env[i][j + 1] = '\0';
        return env;
    }
    return add_new_value_env_2(env, arg1, arg2, i);
}

char **check_value_env(char **env, char *arg1, int i, char *str)
{
    char *arg2 = malloc(sizeof(char) * my_strlen(str));
    int k  = 0;

    for (; str[i] != ' ' && str[i] != '\0' && str[i] != '\t'; i++) {
        arg2[k] = str[i];
        k++;
    }
    arg2[k] = '\0';
    for (; str[i] == ' ' || str[i] == '\t'; i++);
    if (str[i] != '\0') {
        my_put_error("setenv: Too many arguments.\n");
        output_value = 1;
    }
    else
        return add_new_value_env(env, arg1, arg2);
    return env;
}

char **manage_setenv(char **env, char *str)
{
    int i = 0;
    int j = 0;
    char *arg1 = malloc(sizeof(char) * my_strlen(str));

    for (; str[i] == ' ' || str[i] == '\t'; i++);
    for (; str[i] != ' ' && str[i] != '\0' && str[i] != '\t'; i++);
    for (; str[i] == ' ' || str[i] == '\t'; i++);
    for (; str[i] != ' ' && str[i] != '\0' && str[i] != '\t'; i++) {
        arg1[j] = str[i];
        j++;
    }
    arg1[j] = '\0';
    if (verif_name_env(arg1) == -1)
        return env;
    for (; str[i] == ' ' || str[i] == '\t'; i++);
    if (str[i] == '\0')
        return add_name_env(env, arg1);
    return check_value_env(env, arg1, i, str);
}