/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** child_server_init
*/

#include "my_ftp.h"

int get_port(client_t *client)
{
    char **array = NULL;
    char *tmp = get_argument(client->command);
    int port = 0;

    array = str_to_array(tmp, ',');
    port = (atoi(array[4]) * 256) + atoi(array[5]);
    free(array);
    free(tmp);
    return port;
}

char *get_ipadress(client_t *client)
{
    char **array = NULL;
    char * tmp = NULL;
    char *str = get_argument(client->command);

    array = str_to_array(str, ',');
    my_strcat(&tmp, array[0]);
    my_strcat(&tmp, ".");
    my_strcat(&tmp, array[1]);
    my_strcat(&tmp, ".");
    my_strcat(&tmp, array[2]);
    my_strcat(&tmp, ".");
    my_strcat(&tmp, array[3]);
    free(array);
    free(str);
    return tmp;
}

bool port_init_child(client_t *client)
{
    char *adr = get_ipadress(client);
    int port = get_port(client);

    client->scfd = socket(AF_INET, SOCK_STREAM, 0);
    if (client->scfd < 0) {
        fprintf(stderr, "Error creating the TCP socket, exiting.\n");
        return false;
    }
    memset(&client->child_peer_addr, 0, sizeof(struct sockaddr_in));
    memset(&client->child_addr, 0, sizeof(struct sockaddr_in));
    client->child_peer_addr_size = sizeof(struct sockaddr_in);
    client->child_addr.sin_family = AF_INET;
    client->child_addr.sin_addr.s_addr = inet_addr(adr);
    client->child_addr.sin_port = htons(port);
    return true;
}
