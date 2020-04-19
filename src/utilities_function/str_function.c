/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** str_function
*/

#include "my_ftp.h"

/* Return size of array */
int size_of_array(char **array)
{
    int size = 0;

    for (; array[size] != NULL; ++size);
    return size;
}

/* Display content of array */
void display_array(char **array)
{
    for (int a = 0; array[a] != NULL; ++a) {
        printf("%s\n", array[a]);
    }
}

char *get_str(client_t *client, int pos)
{
    char *tmp = malloc(sizeof(char) * (strlen(client->command)));

    memset(tmp, '\0', strlen(client->command));
    if (client->command[pos] == ' ')
        ++pos;
    for (int a = 0; client->command[pos] != '\0'; ++a, ++pos) {
        tmp[a] = client->command[pos];
    }
    return tmp;
}
