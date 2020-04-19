/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** server_init
*/

#include "my_ftp.h"

static void set_variable(ftp_t **ftp)
{
    memset(&(*ftp)->my_addr, 0, sizeof(struct sockaddr_in));
    memset(&(*ftp)->peer_addr, 0, sizeof(struct sockaddr_in));
    (*ftp)->peer_addr_size = sizeof(struct sockaddr_in);
    (*ftp)->my_addr.sin_family = AF_INET;
    (*ftp)->my_addr.sin_port = htons((*ftp)->port);
    (*ftp)->my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
}

/* Set all server parameter,
Return EXIT_FAILURE if error has ocurred, else return EXIT_SUCCESS */
int server_init(ftp_t **ftp)
{
    (*ftp)->sfd = socket(AF_INET, SOCK_STREAM, 0);
    if ((*ftp)->sfd < 0) {
        fprintf(stderr, "Error creating the TCP socket, exiting.\n");
        return EXIT_FAILURE;
    }
    set_variable(ftp);
    if (bind((*ftp)->sfd, (struct sockaddr *)&(*ftp)->my_addr,
            sizeof((*ftp)->my_addr)) != 0) {
        perror("bind");
        return EXIT_FAILURE;
    }
    if (listen((*ftp)->sfd, MAX_CONNECTION) != 0) {
        perror("listen");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
