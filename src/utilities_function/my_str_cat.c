/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** my_str_cat
*/

#include "my_ftp.h"

void my_const_strcat(char **str, const char *str2)
{
    size_t len = 0;
    char *tmp = NULL;
    int index = 0;

    ((*str) == NULL) ? (len = strlen(str2)) :
            (len = strlen(*str) + strlen(str2));
    tmp = alloca(sizeof(char) * (len + 1));
    memset(tmp, '\0', len + 1);
    if (*str != NULL)
        for (int a = 0; (*str)[a] != '\0'; ++a, ++index)
            tmp[index] = (*str)[a];
    for (int a = 0; str2[a] != '\0'; ++a, ++index) {
        tmp [index] = str2[a];
    }
    free(*str);
    (*str) = strdup(tmp);
}

void my_strcat(char **str, char *str2)
{
    size_t len = 0;
    char *tmp = NULL;
    int index = 0;

    ((*str) == NULL) ? (len = strlen(str2)) :
            (len = strlen(*str) + strlen(str2));
    tmp = alloca(sizeof(char) * (len + 1));
    memset(tmp, '\0', len + 1);
    if (*str != NULL)
        for (int a = 0; (*str)[a] != '\0'; ++a, ++index)
            tmp[index] = (*str)[a];
    for (int a = 0; str2[a] != '\0'; ++a, ++index) {
        tmp [index] = str2[a];
    }
    free(*str);
    (*str) = strdup(tmp);
}

char * str_cat_command(void)
{
    char *ret = NULL;

    for (int a = 0; command_name[a] != NULL; ++a) {
        my_const_strcat(&ret, command_name[a]);
        if (command_name[a + 1] != NULL)
            my_strcat(&ret, " ");
        else
            my_strcat(&ret, "\r\n");
    }
    return ret;
}
