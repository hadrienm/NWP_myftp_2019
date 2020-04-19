/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** excute_command
*/

#include "my_ftp.h"

static void delete_child(size_t len, client_t *tmp)
{
    if (len == strlen(tmp->child_write_buffer)) {
        free(tmp->child_write_buffer);
        tmp->child_write_buffer = NULL;
        if (tmp->ccfd != -1)
            close(tmp->ccfd);
        close(tmp->scfd);
        tmp->pasv = false;
        tmp->port = false;
        tmp->ccfd = -1;
        tmp->scfd = -1;
    }
}

static void send_child_data(client_t **client_list, ftp_t *ftp)
{
    size_t len = 0;

    for (client_t *tmp = *client_list; tmp != NULL; tmp = tmp->next) {
        if (tmp->child_write_buffer != NULL &&
                FD_ISSET(tmp->ccfd, &ftp->wset) && tmp->pasv == true) {
            len = write(tmp->ccfd, tmp->child_write_buffer,
                strlen(tmp->child_write_buffer));
            delete_child(len, tmp);
            return;
        }
        if (tmp->child_write_buffer != NULL &&
                FD_ISSET(tmp->scfd, &ftp->wset) &&
                tmp->port == true && tmp->connect == true) {
            len = write(tmp->scfd, tmp->child_write_buffer,
                strlen(tmp->child_write_buffer));
            delete_child(len, tmp);
            return;
        }
    }
}

static void send_data(client_t **client_list, ftp_t *ftp)
{
    size_t len = 0;

    for (client_t *tmp = (*client_list); tmp != NULL; tmp = tmp->next) {
        if (tmp->write_buffer != NULL && FD_ISSET(tmp->fd, &ftp->wset)) {
            len = write(tmp->fd, tmp->write_buffer,
                    strlen(tmp->write_buffer));
            if (len == strlen(tmp->write_buffer)) {
                free(tmp->write_buffer);
                tmp->write_buffer = NULL;
            }
            return;
        }
    }
}

void delete_useless_space(client_t *client)
{
    int size = 0;
    char *tmp = NULL;
    bool space = false;

    size = strlen(client->command);
    tmp = alloca(sizeof(char) * (size + 1));
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
    free(client->command);
    client->command = strdup(tmp);
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
