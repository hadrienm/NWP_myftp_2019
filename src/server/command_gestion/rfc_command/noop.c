/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** noop
*/

#include "my_ftp.h"

void noop(client_t *client, ftp_t *ftp)
{
    if (client->command == NULL)
        return;
    if (strcmp(client->command, "NOOP") != 0 &&
            strcmp(client->command, "noop") != 0) {
        return;
    }
    if (check_user_log(client) == EXIT_FAILURE) {
        return;
    }
    my_const_strcat(&client->write_buffer, rfc_message[CODE_200]);
    free(client->command);
    client->command = NULL;
}
