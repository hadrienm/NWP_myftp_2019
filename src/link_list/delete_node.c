/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** delete_node
*/

#include "my_ftp.h"

/* Delete the first node of linked list */
static void delete_first_node(client_t **client)
{
    client_t *new_list = (*client);

    if (list_is_empty(new_list) == true)
        return;
    new_list = (*client)->next;
    if ((*client)->command != NULL)
        free((*client)->command);
    if ((*client)->pending_cmd != NULL)
        free((*client)->pending_cmd);
    free((*client));
    (*client) = new_list;
}

/* Delete client node of linked list */
void delete_node(client_t *node, client_t **list)
{
    client_t *new_list = (*list);
    client_t *tmp = malloc(sizeof(client_t));

    if (list_is_empty((*list)) == true)
        return;
    if (new_list == node) {
        delete_first_node(list);
        return;
    }
    for (; new_list->next != NULL; new_list = new_list->next)
        if (new_list->next == node)
            break;
    free(new_list->next->command);
    free(new_list->next->pending_cmd);
    free(new_list->next);
    tmp = new_list->next->next;
    new_list->next = tmp;
}
