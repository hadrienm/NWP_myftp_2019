/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** connection
*/

#include "my_ftp.h"

/* manages new connection server,
return EXIT_SUCESSS if any error has occured. */
int new_connection(ftp_t **ftp, client_t **client_list)
{
    if (FD_ISSET((*ftp)->sfd, &(*ftp)->rset))
    {
        if (((*ftp)->cfd = accept((*ftp)->sfd,(struct sockaddr *)
                &(*ftp)->peer_addr, &(*ftp)->peer_addr_size)) < 0)
        {
            perror("accept");
            return EXIT_FAILURE;
        }
        printf("new connection %d\n", (*ftp)->cfd);
        if (*client_list == NULL) {
            initialise_client_struct(client_list, (*ftp)->cfd);
        } else {
            add_node((*ftp)->cfd, client_list);
        }
    }
    return EXIT_SUCCESS;
}

/* manages new connection server,
return EXIT_SUCESSS if any error has occured. */
int pasv_connection(ftp_t **ftp, client_t **client_list)
{
    for (client_t *tmp = *client_list; tmp != NULL; tmp = tmp->next) {
        if (FD_ISSET(tmp->scfd, &(*ftp)->rset) && tmp->pasv == true) {
            if ((tmp->ccfd = accept(tmp->scfd, (struct sockaddr *)
                    &tmp->child_peer_addr, &tmp->child_peer_addr_size)) < 0)
            {
                perror("accept");
                return EXIT_FAILURE;
            }
            printf("new pasv connection %d\n", (*ftp)->cfd);
        }
    }
    return EXIT_SUCCESS;
}

int port_connection(ftp_t **ftp, client_t **client_list)
{
    for (client_t *tmp = *client_list; tmp != NULL; tmp = tmp->next) {
        if (FD_ISSET(tmp->scfd, &(*ftp)->rset) && tmp->port == true &&
            tmp->connect == false) {
            if (connect(tmp->scfd, (struct sockaddr *) &tmp->child_addr,
                    sizeof(tmp->child_addr)) == 0)
            {
                tmp->connect = true;
                printf("new port connection\n");
            }
        }
    }
    return EXIT_SUCCESS;
}

void log_client(client_t *client)
{
    if (client->username != NULL &&
            client->password != NULL &&
            my_str_const_cmp(client->username, default_username) == true &&
            my_str_const_cmp(client->password, default_password) == true)
        client->connection_status = true;
    else if (client->username != NULL &&
            client->password != NULL) {
        free(client->username);
        client->username = NULL;
        free(client->password);
        client->password = NULL;
    }
}

int check_connection(ftp_t **ftp, client_t **client_list)
{
    if (new_connection(ftp, client_list) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (port_connection(ftp, client_list) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (pasv_connection(ftp, client_list) == EXIT_FAILURE)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
