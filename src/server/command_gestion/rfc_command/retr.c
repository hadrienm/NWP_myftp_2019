/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** retr
*/

#include "my_ftp.h"

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

static void sendFile(client_t *client, ftp_t *ftp) {
    char buff[MAX_SIZE] = {0};
    char *filename = found_path(client, ftp);
    FILE *pFile;

    pFile = fopen(filename, "r");
    if (!pFile) {
        fprintf(stderr, "Error trying to open file : %s\n", filename);
        return;
    }
    while (fgets(buff, MAX_SIZE, pFile))
        my_strcat(&client->child_write_buffer, buff);
    fclose(pFile);
}

static bool retr_error_gestion(client_t *client, ftp_t *ftp)
{
    if (client->command == NULL || ftp == NULL)
        return false;
    if (is_function(client, "RETR") == false)
        return false;
    if (check_user_log(client) == EXIT_FAILURE)
        return false;
    if (more_one_argument(client) == false)
        return false;
    if (check_port_pasv(client) == false)
        return false;
    return true;
}

void retr(client_t *client, ftp_t *ftp)
{
    if (retr_error_gestion(client, ftp) == false)
        return;
    sendFile(client, ftp);
    if (client->child_write_buffer != NULL)
        my_const_strcat(&client->child_rfc_message, rfc_message[CODE_150]);
    else
        my_const_strcat(&client->child_rfc_message, rfc_message[CODE_550]);
    free(client->command);
    client->command = NULL;
}
