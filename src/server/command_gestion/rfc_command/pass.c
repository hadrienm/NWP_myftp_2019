/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** pass
*/

#include "my_ftp.h"

static void get_passwd(client_t *client)
{
    char * tmp = alloca(sizeof(char) * strlen(client->command));
    int pos = 0;

    memset(tmp, '\0', strlen(client->command));
    if (client->password != NULL) {
        free(client->password);
        client->password = NULL;
    }
    for (pos = 0; client->command[pos] != '\0'; ++pos) {
        if (client->command[pos] == ' ') {
            ++pos;
            break;
        }
    }
    for (int a = 0; client->command[pos] != '\0'; ++a, ++pos)
        tmp[a] = client->command[pos];
    if (strlen(tmp) == 0)
        strcpy(tmp, "default\0");
    client->password = strdup(tmp);
}

static void set_rfc_message(client_t *client)
{
    if (client->username != NULL) {
        log_client(client);
        if (client->connection_status == false) {
            my_const_strcat(&client->write_buffer, rfc_message[CODE_530F]);
        } else {
            my_const_strcat(&client->write_buffer, rfc_message[CODE_230]);
        }
    } else {
        my_const_strcat(&client->write_buffer, rfc_message[CODE_332]);
    }
}

void pass(client_t *client, ftp_t *ftp)
{
    if (client->command == NULL)
        return;
    if (is_function(client, "PASS") == false)
        return;
    get_passwd(client);
    set_rfc_message(client);
    free(client->command);
    client->command = NULL;
}
