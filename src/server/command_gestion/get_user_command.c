/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** command_gestion
*/

#include "my_ftp.h"

/* Read user socket for get user command */
static void read_user_command(client_t *node)
{
    char *buffer = alloca(sizeof(char) * MAX_SIZE);

    memset(buffer, '\0', MAX_SIZE);
    if (node == NULL)
        return;
    size_t size = read(node->fd, buffer, MAX_SIZE);
    if (size <= 0) {
        close(node->fd);
        node->is_free = true;
    } else {
        node->command = strdup(buffer);
    }
}

static void read_child_client(client_t *node)
{
    char *buffer = alloca(sizeof(char) * MAX_SIZE);

    memset(buffer, '\0', MAX_SIZE);
    if (node == NULL)
        return;
    size_t size = read(node->ccfd, buffer, MAX_SIZE);
    if (size <= 0) {
        close(node->ccfd);
    } else {
        node->child_read_buffer = strdup(buffer);
    }
}

/* Pars of the all fd read list, for get user command.
The command is sent in the variable "command",
located in the structure "client_t".*/
void grep_users_command(ftp_t **ftp, client_t **client_list)
{
    if (*client_list == NULL || *ftp == NULL)
        return;
    for (client_t *tmp = (*client_list); tmp != NULL; tmp = tmp->next) {
        if (FD_ISSET(tmp->fd, &(*ftp)->rset))
            read_user_command(tmp);
        if (FD_ISSET(tmp->ccfd, &(*ftp)->rset))
            read_child_client(tmp);
    }
}
