/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** strcmp
*/

#include "my_ftp.h"

bool my_strcmp(char *str, char *str2)
{
    int size1 = 0;
    int size2 = 0;

    if (str == NULL || str2 == NULL) {
        return false;
    }
    size1 = strlen(str);
    size2 = strlen(str2);
    if (size1 != size2)
        return false;
    for (int a = 0; a != size1 -1; ++a) {
        if (str[a] != str2[a])
            return false;
    }
    return true;
}

bool my_str_const_cmp(char *str, const char *str2)
{
    int size1 = 0;
    int size2 = 0;

    if (str == NULL || str2 == NULL) {
        return false;
    }
    size1 = strlen(str);
    size2 = strlen(str2);
    if (size1 != size2)
        return false;
    for (int a = 0; a != size1 -1; ++a) {
        if (str[a] != str2[a])
            return false;
    }
    return true;
}