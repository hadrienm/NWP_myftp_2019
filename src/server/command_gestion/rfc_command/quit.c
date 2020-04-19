/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** quit
*/

#include "my_ftp.h"

void quit(client_t *client, ftp_t *ftp)
{
    if (client->command == NULL || ftp == NULL)
        return;
    if (strcmp(client->command, "quit") != 0 &&
            strcmp(client->command, "QUIT") != 0) {
        return ;
    }
    my_const_strcat(&client->write_buffer, rfc_message[CODE_221]);
    client->is_free = true;
    free(client->command);
    client->command = NULL;
}
