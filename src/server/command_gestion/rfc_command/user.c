/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** user
*/

#include "my_ftp.h"

static void get_user(char *str, int pos, client_t *client)
{
    char * tmp = alloca(sizeof(char) * strlen(str));
    memset(tmp, '\0', strlen(str));

    if (client->username != NULL) {
        free(client->username);
        client->username = NULL;
    }
    for (int a = 0; str[pos] != '\0'; ++a, ++pos) {
        tmp[a] = str[pos];
    }
    client->username = malloc(sizeof(char) * (strlen(tmp) + 1));
    strcpy(client->username, tmp);
}

static void set_rfc_message(client_t *client)
{
    if (client->password != NULL) {
        log_client(client);
        if (client->connection_status == false) {
            my_const_strcat(&client->write_buffer, rfc_message[CODE_530F]);
        } else {
            my_const_strcat(&client->write_buffer, rfc_message[CODE_230]);
        }
    } else {
        my_const_strcat(&client->write_buffer, rfc_message[CODE_331]);
    }
    free(client->command);
    client->command = NULL;
}

void user(client_t *client, ftp_t *ftp)
{
    char *tmp = NULL;
    int pos = 0;

    if (client->command == NULL)
        return;
    (void)ftp;
    tmp = alloca(sizeof(char) * strlen(client->command) + 1);
    memset(tmp, '\0', strlen(client->command) + 1);
    for (pos = 0; client->command[pos] != '\0'; ++pos) {
        if (client->command[pos] == ' ')
            break;
        tmp[pos] = client->command[pos];
    }
    if (strcmp(tmp, "USER") != 0 && strcmp(tmp, "user") != 0)
        return;
    if (client->command[pos] == '\0') {
        bad_synthax(client);
        return;
    }
    get_user(client->command, pos + 1, client);
    set_rfc_message(client);
}
