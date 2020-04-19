/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** port
*/

#include "my_ftp.h"

static bool port_error_gestion(client_t *client, ftp_t *ftp)
{
    char ** array = NULL;
    char *tmp = NULL;

    if (client->command == NULL || ftp == NULL)
        return false;
    if (is_function(client, "PORT") == false)
        return false;
    if (check_user_log(client) == EXIT_FAILURE)
        return false;
    tmp = get_argument(client->command);
    array = str_to_array(tmp, ',');
    free(tmp);
    if (size_of_array(array) != 6) {
        bad_synthax(client);
        free(array);
        return false;
    }
    free(array);
    return true;
}

static void send_rfc_message(client_t *client, bool status)
{
    if (status == true) {
        my_const_strcat(&client->write_buffer, rfc_message[CODE_200]);
    } else {
        my_const_strcat(&client->write_buffer, rfc_message[CODE_421]);
    }
    free(client->command);
    client->command = NULL;
}

void port(client_t *client, ftp_t *ftp)
{
    bool status = false;

    if (port_error_gestion(client, ftp) == false)
        return;
    status = port_init_child(client);
    send_rfc_message(client, status);
    client->port = true;
}
