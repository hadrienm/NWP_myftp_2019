/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** utilities_function
*/

#include "my_ftp.h"

bool is_path(char *str)
{
    for (int a = 0; str[a] != '\0'; ++a)
        if (str[a] == '/')
            return true;
    return false;
}

bool is_function(client_t *client, char *name)
{
    char **array = NULL;

    array = str_to_array(client->command, ' ');
    if (strcasecmp(array[0], name) != 0)
        return false;
    return true;
}

char *get_argument(char *str)
{
    char *tmp = malloc(sizeof(char) * (strlen(str)));
    bool space = false;

    memset(tmp, '\0', strlen(str));
    for (int a = 0, index = 0; str[a] != '\0'; ++a) {
        if (str[a] == ' ' && space == false) {
            space = true;
        } else if (space == true) {
            tmp[index] = str[a];
            ++index;
        }
    }
    return tmp;
}
