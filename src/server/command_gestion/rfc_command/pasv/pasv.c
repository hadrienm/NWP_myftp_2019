/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** pasv
*/

#include "my_ftp.h"

static bool pasv_error_gestion(client_t *client)
{
    char **array = NULL;

    if (client->command == NULL)
        return false;
    array = str_to_array(client->command, ' ');
    if (strcasecmp(array[0], "pasv") != 0)
        return false;
    if (check_user_log(client) == EXIT_FAILURE)
        return false;
    return true;
}

static void send_rfc_message(client_t *client, bool status)
{
    char *tmp = malloc(sizeof(char) * MAX_SIZE);

    if (status == true) {
        sprintf(tmp, "Entering passive mode (127,0,0,1,%d,%d).\r\n",
                ntohs(client->child_addr.sin_port) / 256,
                ntohs(client->child_addr.sin_port) % 256);
        my_const_strcat(&client->write_buffer, tmp);
    } else {
        my_const_strcat(&client->write_buffer, rfc_message[CODE_421]);
    }
    free(client->command);
    free(tmp);
    client->command = NULL;
}

void pasv(client_t *client, ftp_t *ftp)
{
    bool status = false;

    if (pasv_error_gestion(client) == false)
        return;
    status = pasv_init_child(client);
    send_rfc_message(client, status);
    client->pasv = true;
}
