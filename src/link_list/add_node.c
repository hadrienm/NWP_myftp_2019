/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** add_node
*/

#include "my_ftp.h"

static void add_node_variable(client_t *new_node)
{
    new_node->write_buffer = strdup(rfc_message[CODE_220]);
    new_node->child_write_buffer = NULL;
    new_node->scfd = -1;
    new_node->ccfd = -1;
    new_node->port = false;
    new_node->connect = false;
    new_node->child_rfc_message = NULL;
}

/* Add node inside client linked list
Return false if error has ocurred
Return true if any error has ocurred */
bool add_node(int cfd, client_t **list)
{
    client_t *new_node = malloc(sizeof(*new_node));

    if (new_node == NULL)
        return false;
    new_node->fd = cfd;
    new_node->command = NULL;
    new_node->pending_cmd = NULL;
    new_node->connection_status = false;
    new_node->username = NULL;
    new_node->password = NULL;
    new_node->is_free = false;
    new_node->pasv = false;
    new_node->port = false;
    new_node->next = (*list);
    add_node_variable(new_node);
    (*list) = new_node;
    return true;
}
