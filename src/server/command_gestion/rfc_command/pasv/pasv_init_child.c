/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** pasv_init_child
*/

#include "my_ftp.h"

static bool start_listening(client_t *client)
{
    if (bind(client->scfd, (struct sockaddr *)&client->child_addr,
            sizeof(client->child_addr)) != 0) {
        perror("bind");
        return false;
    }
    socklen_t len = sizeof(client->child_addr);
    if (getsockname(client->scfd, (struct sockaddr *)
            &client->child_addr, &len) == -1) {
        printf("Couldn't\n");
        return 84;
    }
    if (listen(client->scfd, 1) != 0) {
        perror("listen");
        return false;
    }
    return true;
}

bool pasv_init_child(client_t *client)
{
    client->scfd = socket(AF_INET, SOCK_STREAM, 0);
    if (client->scfd < 0) {
        fprintf(stderr, "Error creating the TCP socket, exiting.\n");
        return false;
    }
    memset(&client->child_peer_addr, 0, sizeof(struct sockaddr_in));
    memset(&client->child_addr, 0, sizeof(struct sockaddr_in));
    client->child_peer_addr_size = sizeof(struct sockaddr_in);
    client->child_addr.sin_family = AF_INET;
    client->child_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    client->child_addr.sin_port = htons(0);
    if (start_listening(client) == false)
        return false;
    return true;
}