/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** initialise
*/

#include "my_ftp.h"

static void initialise_client_variable(client_t **client_list)
{
    (*client_list)->pasv = false;
    (*client_list)->port = false;
    (*client_list)->next = NULL;
    (*client_list)->scfd = -1;
    (*client_list)->ccfd = -1;
    (*client_list)->port = false;
    (*client_list)->connect = false;
    (*client_list)->child_rfc_message = NULL;
}

/* Initalise all necessary variable of client structure */
bool initialise_client_struct(client_t **client_list, int cfd)
{
    (*client_list) = malloc(sizeof(client_t));
    if ((*client_list) == NULL)
        return false;
    (*client_list)->pending_cmd = NULL;
    (*client_list)->write_buffer = NULL;
    (*client_list)->username = NULL;
    (*client_list)->password = NULL;
    (*client_list)->command = NULL;
    (*client_list)->write_buffer = strdup(rfc_message[CODE_220]);
    (*client_list)->child_write_buffer = NULL;
    (*client_list)->path = NULL;
    (*client_list)->fd = cfd;
    (*client_list)->connection_status = false;
    (*client_list)->is_free = false;
    initialise_client_variable(client_list);
    return true;
}

/* Initalise all necessary variable of ftp structure */
bool initialise_ftp_struct(ftp_t **ftp)
{
    (*ftp) = malloc(sizeof(ftp_t));
    if ((*ftp) != NULL) {
        (*ftp)->port = 0;
        (*ftp)->return_value = NO_PROBLEM;
        return true;
    }
    return false;
}
