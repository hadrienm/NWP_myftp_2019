/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** help
*/

#include "my_ftp.h"

static void grep_command(char *command, int pos, char *str)
{
    memset(str, '\0', strlen(command) + 1);
    if (command[pos] == ' ')
        pos += 1;
    for (int index = 0; command[pos] != '\0'; ++pos, ++index) {
        str[index] = command[pos];
    }
}

static void set_rfc_message(client_t *client, char *str)
{
    char *new_str = NULL;
    int pos = 0;

    if (strlen(str) == 0) {
        new_str = str_cat_command();
        client->write_buffer = strdup(new_str);
        free(new_str);
        my_const_strcat(&client->write_buffer, rfc_message[CODE_214]);
        return;
    }
    for (pos = 0; command_description[pos] != NULL; ++pos)
        if (strcmp(str, command_name[pos]) == 0)
            break;
    if (command_description[pos] != NULL) {
        client->write_buffer = strdup(command_description[pos]);
        my_const_strcat(&client->write_buffer, rfc_message[CODE_214]);
    } else {
        client->write_buffer = strdup(rfc_message[CODE_501]);
    }
}

void help(client_t *client, ftp_t *ftp)
{
    char *tmp = NULL;
    int pos = 0;
    char *str = NULL;

    if (client->command == NULL)
        return;
    tmp = alloca(sizeof(char) * (strlen(client->command) + 1));
    memset(tmp, '\0', strlen(client->command) + 1);
    for (pos = 0; client->command[pos] != '\0'; ++pos) {
        if (client->command[pos] == ' ')
            break;
        tmp[pos] = client->command[pos];
    }
    if (strcmp(tmp, "HELP") != 0 && strcmp(tmp, "help") != 0)
        return;
    str = malloc(sizeof(char) * (strlen(client->command) + 1));
    grep_command(client->command, pos, str);
    set_rfc_message(client, str);
    free(str);
    free(client->command);
    client->command = NULL;
}