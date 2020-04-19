/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** cdup
*/

#include "my_ftp.h"

static void create_path(client_t *client, ftp_t *ftp)
{
    char *tmp = NULL;
    int size = 0;

    tmp = strdup(ftp->default_path);
    size = strlen(tmp);
    for (int a = size -1; a != 0; --a) {
        if (tmp[a] == '/') {
            tmp[a] = '\0';
            break;
        }
        tmp[a] = '\0';
    }
    my_const_strcat(&client->write_buffer, rfc_message[CODE_200]);
}

static void update_path(client_t *client)
{
    int size = 0;
    char *tmp = NULL;

    if (is_path(client->path) == false) {
        my_const_strcat(&client->write_buffer, rfc_message[CODE_200]);
        return;
    }
    tmp = strdup(client->path);
    size = strlen(tmp);
    for (int a = size -1; a != 0; --a) {
        if (tmp[a] == '/') {
            tmp[a] = '\0';
            break;
        }
        tmp[a] = '\0';
    }
    client->path = strdup(tmp);
    free(tmp);
    my_const_strcat(&client->write_buffer, rfc_message[CODE_200]);
}

void cdup(client_t *client, ftp_t *ftp)
{
    if (client->command == NULL)
        return;
    if (is_function(client, "CDUP") == false)
        return;
    if (check_user_log(client) == EXIT_FAILURE)
        return;
    if (client->path == NULL)
        create_path(client, ftp);
    else
        update_path(client);
    free(client->command);
    client->command = NULL;
}
