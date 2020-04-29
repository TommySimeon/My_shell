/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** main
*/

#include "my.h"

int main(int ac, char **av, char **env)
{
    char *place = take_place(env);

    if (ac != 1) {
        write(2, av[1], my_strlen(av[1]));
        write(2, ": No such file or directory.\n", 29);
        return 1;
    }
    if (env == NULL)
        return 0;
    return my_sh(env, place);
}

char *add_place(char *path, char *place)
{
    char *path_file = malloc(sizeof(char) * \
    (my_strlen(place) + 2 + my_strlen(path)));
    int i = 0;
    int j = 0;

    for (; place[i] != '\0'; i++, j++)
        path_file[j] = place[i];
    for (i = 0; path[i] != '\0'; i++, j++)
        path_file[j] = path[i];
    path_file[j] = '\0';
    return path_file;
}

char *take_place(char **env)
{
    int ln = 0;
    int i = 0;
    int j = 0;
    char *place;

    for (; env[ln] != NULL && check_env(env[ln], "PWD") != 1; ln++);
    if (env[ln] ==  NULL)
        exit(0);
    place = malloc(sizeof(char) * my_strlen(env[ln]));
    for (; env[ln][j] != '='; j++);
    for (j = j + 1; env[ln][j] != '\0'; j++, i++)
        place[i] = env[ln][j];
    place[i] = '\0';
    return place;
}

char *take_home(char **env)
{
    int i = 0;
    int j = 0;
    int k = 0;
    char *home;

    for ( ;env[i] != NULL && check_env(env[i], "HOME") != 1; i++);
    if (env[i] == NULL)
        return ".";
    home = malloc(sizeof(char) * my_strlen(env[i]));
    for (; env[i][j] != '='; j++);
    j++;
    for (; env[i][j] != '\0'; j++) {
        home[k] = env[i][j];
        k++;
    }
    home[k] = '\0';
    return home;
}