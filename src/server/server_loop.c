/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** server_loop
*/

#include "my_ftp.h"

/* free logout client node */
void free_useless(client_t **client_list)
{
    client_t * current = (*client_list);
    client_t * next;

    while (current != NULL)
    {
        next = current->next;
        if (current->is_free == true &&
                current->write_buffer == NULL) {
            close(current->fd);
            delete_node(current, client_list);
        }
        current = next;
    }
}

/* contains the server execution thread */
int server_loop(ftp_t **ftp, client_t **client_list)
{
    while (1)
    {
        free_useless(client_list);
        server_set_read_fdlist(ftp, (*client_list));
        server_child_set_read_fdlist(ftp, (*client_list));
        server_set_write_fdlist(ftp, (*client_list));
        server_child_set_write_fdlist(ftp, (*client_list));
        if (select(FD_SETSIZE, &(*ftp)->rset, &(*ftp)->wset, NULL, NULL) == 0)
        {
            perror("select");
            return EXIT_FAILURE;
        }
        if (check_connection(ftp, client_list) == EXIT_FAILURE)
            return EXIT_FAILURE;
        grep_users_command(ftp, client_list);
        excute_command(client_list, *ftp);
    }
    return EXIT_SUCCESS;
}
