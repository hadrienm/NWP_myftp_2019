/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** pars_command
*/

#include "my_ftp.h"

/* Found carriage inside pending command variable
Return carriage postion or -1 if any carriage hasn't found */
static int found_carriage(char *str)
{
    int pos = 0;

    if (str == NULL)
        return - 1;
    for (int a = 0; str[a] != '\0'; ++a, ++pos) {
        if (str[a] == '\r' && str[a + 1] == '\n') {
            return pos;
        }
    }
    return -1;
}

/* delete useless space of client command */
static void delete_useless_part_of_pending_cmd(client_t *client, int pos)
{
    int new_size = strlen(client->pending_cmd) - (pos + 1);
    char *tmp = alloca(sizeof(char *) * (new_size + 1));

    memset(tmp, '\0', new_size + 1);
    if (client->pending_cmd[pos + 2] == '\0') {
        free(client->pending_cmd);
        client->pending_cmd = NULL;
        return;
    }
    pos += 2;
    for (int a = 0; client->pending_cmd[pos] != '\0'; ++pos, ++a) {
        tmp[a] = client->pending_cmd[pos];
    }
    free(client->pending_cmd);
    client->pending_cmd = strdup(tmp);
}

/* Search inside pending_cmd variable if
there is excutable commmand. */
static void found_excutable_command(client_t *client, int pos)
{
    if (pos == -1)
        return;
    else if (pos == 0) {
        delete_useless_part_of_pending_cmd(client, pos);
        return;
    }
    client->command = malloc(sizeof(char) * (pos + 1));
    memset(client->command, '\0', pos + 1);
    for (int i = 0; i < pos; ++i) {
        client->command[i] = client->pending_cmd[i];
    }
    delete_useless_part_of_pending_cmd(client, pos);
}

/* Pars input user, for found excutable command */
bool pars_command(client_t *client)
{
    if (client == NULL)
        return true;
    if (client->pending_cmd != NULL && client->command == NULL) {
        found_excutable_command(client, found_carriage(client->pending_cmd));
    } else if (client->pending_cmd != NULL && client->command != NULL) {
        my_strcat(&client->pending_cmd, client->command);
        free(client->command);
        client->command = NULL;
        found_excutable_command(client, found_carriage(client->pending_cmd));
    } else if (client->command != NULL) {
        client->pending_cmd = strdup(client->command);
        free(client->command);
        client->command = NULL;
        found_excutable_command(client, found_carriage(client->pending_cmd));
    }
    if (client->command == NULL && found_carriage(client->pending_cmd) == -1)
        return true;
    else
        return false;
}
