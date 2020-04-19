/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** server_set
*/

#include "my_ftp.h"

/* Set client readlist client and client writelist */
int server_set_read_fdlist(ftp_t **ftp, client_t *client_list)
{
    if ((*ftp) == NULL)
        return EXIT_FAILURE;
    FD_ZERO(&(*ftp)->rset);
    FD_SET((*ftp)->sfd, &(*ftp)->rset);
    for (client_t *tmp = client_list; tmp != NULL; tmp = tmp->next)
    {
        FD_SET(tmp->fd, &(*ftp)->rset);
    }
    return EXIT_SUCCESS;
}

int server_child_set_read_fdlist(ftp_t **ftp, client_t *client_list)
{
    if ((*ftp) == NULL)
        return EXIT_FAILURE;
    for (client_t *tmp = client_list; tmp != NULL; tmp = tmp->next)
    {
        if (tmp->pasv == true)
        {
            FD_SET(tmp->scfd, &(*ftp)->rset);
            (tmp->ccfd != -1) ? (FD_SET(tmp->ccfd, &(*ftp)->rset)) : (0);
        }
        if (tmp->port == true)
            FD_SET(tmp->scfd, &(*ftp)->rset);
    }
    return EXIT_SUCCESS;
}

int server_set_write_fdlist(ftp_t **ftp, client_t *client_list)
{
    if ((*ftp) == NULL)
        return EXIT_FAILURE;
    FD_ZERO(&(*ftp)->wset);
    FD_SET((*ftp)->sfd, &(*ftp)->wset);

    for (client_t *tmp = client_list; tmp != NULL; tmp = tmp->next)
    {
        if (tmp->write_buffer != NULL)
        {
            FD_SET(tmp->fd, &(*ftp)->wset);
        }
    }
    return EXIT_SUCCESS;
}

int server_child_set_write_fdlist(ftp_t **ftp, client_t *client_list)
{
    if ((*ftp) == NULL)
        return EXIT_FAILURE;
    for (client_t *tmp = client_list; tmp != NULL; tmp = tmp->next)
    {
        if (tmp->pasv == true)
        {
            FD_SET(tmp->scfd, &(*ftp)->wset);
            (tmp->ccfd != -1 && tmp->child_write_buffer != NULL) ?
                    (FD_SET(tmp->ccfd, &(*ftp)->wset)) : (0);
        }
        if (tmp->port == true && tmp->child_write_buffer != NULL)
            FD_SET(tmp->scfd, &(*ftp)->wset);
    }
    return EXIT_SUCCESS;
}
