/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** linked_list
*/

#include "my_ftp.h"

/* Check if linked list is empty.
Return true if its empty else return false */
bool list_is_empty(client_t *client)
{
    if (client == NULL)
        return true;
    return false;
}

/* Display linked list contain */
void display_linked_list_contain(client_t *client_list)
{
    if (list_is_empty(client_list) == true)
        printf("List is empty\n");
    for (client_t *tmp_list = client_list; tmp_list != NULL;
            tmp_list = tmp_list->next)
    {
        printf("%d\n", tmp_list->fd);
    }
}
