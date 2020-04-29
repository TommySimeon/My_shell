/*
** EPITECH PROJECT, 2019
** handling_alias.c
** File description:
** handling alias
*/

#include "my.h"

char *find_alias(char **alias, int i)
{
    char *str = malloc(sizeof(char) * my_strlen(alias[i]));
    int j = 0;

    for (; alias[i][j] != '=' && alias[i][j] != '\0'; j++)
        str[j] = alias[i][j];
    str[j] = '\0';
    return str;
}

char *find_cmd_alias(char **alias, int i)
{
    char *str = malloc(sizeof(char) * my_strlen(alias[i]));
    int j = 0;

    for (; alias[i][j] != '=' && alias[i][j]; j++);
    for (; alias[i][j] != '\0'; j++)
        str[j] = alias[i][j];
    str[j] = '\0';
    return str;
}

alias_s *sort_alias(char **alias, int len)
{
    char *alias_name = NULL;
    char *cmd_name = NULL;
    int i = 0;
    alias_s *alias_struct = malloc(sizeof(*alias_struct) * (len + 1));

    for (; alias[i]; i++) {
        alias_name = find_alias(alias, i);
        cmd_name = find_cmd_alias(alias, i);
        alias_struct[i].alias = my_strcpy(alias_struct[i].alias, alias_name);
        alias_struct[i].cmd = my_strcpy(alias_struct[i].cmd, cmd_name);
        free(alias_name);
        free(cmd_name);
    }
    alias_struct[i].alias = NULL;
    return alias_struct;
}

alias_s *handling_alias(char *path)
{
    char **alias = NULL;
    int i = 0;
    int fd = open(my_strcat(path, "/alias.42rc"), O_RDONLY);
    struct stat size;
    char *buffer = "\0";

    if (fd == -1)
        return NULL;
    stat(my_strcat(path, "/alias.42rc"), &size);
    alias = malloc(sizeof(char *) * (size.st_size + 1));
    for (; buffer != NULL; i++) {
        buffer = my_strcpy(buffer, get_next_line(fd, 1));
        if (buffer == NULL)
            break;
        alias[i] = my_strcpy(alias[i], buffer);
    }
    alias[i] = NULL;
    close(fd);
    return sort_alias(alias, i);
}