/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** excute_command
*/

#include "my_ftp.h"

static char * pars_string(client_t *client, int size)
{
    char *tmp = NULL;
    bool space = false;

    tmp = malloc(sizeof(char) * (size + 1));
    memset(tmp, '\0', size + 1);
    for (int a = 0, index = 0; client->command[a] != '\0'; ++a) {
        if (client->command[a] == ' ' && space == false &&
                client->command[a + 1] != '\0') {
            tmp[index] = client->command[a];
            ++index;
            space = true;
        } else if (client->command[a] != ' ') {
            tmp[index] = client->command[a];
            ++index;
            space = false;
        }
    }
    return tmp;
}

void delete_useless_space(client_t *client)
{
    int size = 0;
    char *tmp = NULL;

    size = strlen(client->command);
    tmp = pars_string(client, size);
    free(client->command);
    if (strlen(tmp) != 0)
        client->command = strdup(tmp);
    else
        client->command = strdup(" ");
    free(tmp);
}

void excute_command(client_t **client_list, ftp_t *ftp)
{
    for (client_t *tmp = (*client_list); tmp != NULL; tmp = tmp->next) {
        while (pars_command(tmp) == false) {
            (tmp->command != NULL) ? (delete_useless_space(tmp)) : (0);
            for (int i = 0; rfc_command[i] != NULL; ++i)
                rfc_command[i](tmp, ftp);
            if (tmp->command != NULL) {
                free(tmp->command);
                tmp->command = NULL;
                tmp->write_buffer = strdup(rfc_message[CODE_500]);
            }
            if (tmp->is_free == true)
                break;
        }
        send_data(client_list, ftp);
        send_child_data(client_list, ftp);
    }
}
