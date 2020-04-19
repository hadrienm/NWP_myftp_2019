/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** cwd
*/

#include "my_ftp.h"

static void absolut_path(client_t *client, char *word, ftp_t *ftp)
{
    char *tmp = NULL;

    my_strcat(&tmp, ftp->default_path);
    my_strcat(&tmp, word);
    if (directory_exist(tmp) == true) {
        client->write_buffer = strdup(rfc_message[CODE_250]);
        client->path = strdup(tmp);
    } else {
        client->write_buffer = strdup(rfc_message[CODE_550]);
    }
}

static void name(client_t *client, char *word, ftp_t *ftp)
{
    char *tmp = NULL;

    if (client->path == NULL) {
        my_strcat(&tmp, ftp->default_path);
        my_strcat(&tmp, "/");
        my_strcat(&tmp, word);
    } else {
        my_strcat(&tmp, client->path);
        my_strcat(&tmp, "/");
        my_strcat(&tmp, word);
    }
    if (directory_exist(tmp) == false) {
        client->write_buffer = strdup(rfc_message[CODE_550]);
    } else {
        client->path = strdup(tmp);
        client->write_buffer = strdup(rfc_message[CODE_250]);
    }
}

static void found_path(client_t *client, ftp_t *ftp)
{
    char *word = NULL;

    word = get_argument(client->command);
    if (is_path(word) == true)
        absolut_path(client, word, ftp);
    else
        name(client, word, ftp);
    free(word);
}

void cwd(client_t *client, ftp_t *ftp)
{
    if (client->command == NULL || ftp == NULL)
        return;
    if (is_function(client, "CWD") == false)
        return;
    if (check_user_log(client) == EXIT_FAILURE)
        return;
    if (more_one_argument(client) == false)
        return;
    found_path(client, ftp);
    free(client->command);
    client->command = NULL;
}
