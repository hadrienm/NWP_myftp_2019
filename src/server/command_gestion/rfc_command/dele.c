/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** dele
*/

#include "my_ftp.h"

static void send_rfc_message(client_t *client, char *new_str)
{
    if (remove(new_str) == -1)
        my_const_strcat(&client->write_buffer, rfc_message[CODE_550]);
    else
        my_const_strcat(&client->write_buffer, rfc_message[CODE_250]);
}

static char *found_path(client_t *client, ftp_t *ftp)
{
    char *word = NULL;
    char *tmp = NULL;

    word = get_argument(client->command);
    if (is_path(word) == true) {
        my_strcat(&tmp, ftp->default_path);
        my_strcat(&tmp, word);
    } else {
        if (client->path != NULL) {
            my_strcat(&tmp, client->path);
        } else {
            my_strcat(&tmp, ftp->default_path);
        }
        my_strcat(&tmp, "/");
        my_strcat(&tmp, word);
    }
    free(word);
    return tmp;
}

static void delete_file(client_t *client, ftp_t *ftp)
{
    char *str = found_path(client, ftp);

    send_rfc_message(client, str);
    free(str);
}

void dele(client_t *client, ftp_t *ftp)
{
    if (client->command == NULL)
        return;
    if (is_function(client, "DELE") == false)
        return;
    if (check_user_log(client) == EXIT_FAILURE)
        return;
    if (more_one_argument(client) == false)
        return;
    delete_file(client, ftp);
    free(client->command);
    client->command = NULL;
}