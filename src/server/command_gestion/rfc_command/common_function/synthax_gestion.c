/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** synthax_gestion
*/

#include "my_ftp.h"

void bad_synthax(client_t *client)
{
    my_const_strcat(&client->write_buffer, rfc_message[CODE_501]);
    free(client->command);
    client->command = NULL;
}

int check_user_log(client_t *client)
{
    if (client->connection_status == false) {
        my_const_strcat(&client->write_buffer, rfc_message[CODE_530]);
        free(client->command);
        client->command = NULL;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

bool check_port_pasv(client_t *client)
{
    if (client->pasv == false && client->port == false) {
        free(client->command);
        client->command = NULL;
        my_const_strcat(&client->write_buffer, rfc_message[CODE_425]);
        return false;
    } else {
        return true;
    }
}

bool only_one_argument(client_t *client)
{
    char **array = NULL;

    array = str_to_array(client->command, ' ');
    if (size_of_array(array) != 1) {
        my_const_strcat(&client->write_buffer, rfc_message[CODE_501]);
        free(client->command);
        client->command = NULL;
        free(array);
        return false;
    }
    free(array);
    return true;
}

bool more_one_argument(client_t *client)
{
    char **array = NULL;

    array = str_to_array(client->command, ' ');
    if (size_of_array(array) < 2) {
        if (is_function(client, "CWD") == false)
            my_const_strcat(&client->write_buffer, rfc_message[CODE_501]);
        else
            my_const_strcat(&client->write_buffer, rfc_message[CODE_550]);
        free(client->command);
        client->command = NULL;
        free(array);
        return false;
    }
    free(array);
    return true;
}
