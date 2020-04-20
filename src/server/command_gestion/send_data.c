/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** send_data
*/

#include "my_ftp.h"

void delete_child(size_t len, client_t *tmp)
{
    if (len == strlen(tmp->child_write_buffer)) {
        free(tmp->child_write_buffer);
        tmp->child_write_buffer = NULL;
        if (tmp->ccfd != -1)
            close(tmp->ccfd);
        close(tmp->scfd);
        tmp->pasv = false;
        tmp->port = false;
        tmp->ccfd = -1;
        tmp->scfd = -1;
    }
}

static void send_child_rfc_code(client_t *tmp, ftp_t *ftp)
{
    size_t len = 0;

    if (FD_ISSET(tmp->fd, &ftp->wset) && tmp->child_rfc_message != NULL) {
        my_const_strcat(&tmp->child_rfc_message, rfc_message[CODE_226]);
        len = write(tmp->fd, tmp->child_rfc_message,
            strlen(tmp->child_rfc_message));
        free(tmp->child_rfc_message);
        tmp->child_rfc_message = NULL;
    }
}

static void send_pasv_data(client_t *tmp, ftp_t *ftp)
{
    size_t len = 0;

    if (tmp->child_write_buffer != NULL &&
            FD_ISSET(tmp->ccfd, &ftp->wset) && tmp->pasv == true) {
        len = write(tmp->ccfd, tmp->child_write_buffer,
            strlen(tmp->child_write_buffer));
        send_child_rfc_code(tmp, ftp);
        delete_child(len, tmp);
    }
}

void send_child_data(client_t **client_list, ftp_t *ftp)
{
    size_t len = 0;

    for (client_t *tmp = *client_list; tmp != NULL; tmp = tmp->next) {
        send_pasv_data(tmp, ftp);
    }
}

void send_data(client_t **client_list, ftp_t *ftp)
{
    size_t len = 0;

    for (client_t *tmp = (*client_list); tmp != NULL; tmp = tmp->next) {
        if (tmp->write_buffer != NULL && FD_ISSET(tmp->fd, &ftp->wset)) {
            len = write(tmp->fd, tmp->write_buffer,
                    strlen(tmp->write_buffer));
            if (len == strlen(tmp->write_buffer)) {
                free(tmp->write_buffer);
                tmp->write_buffer = NULL;
            }
            return;
        }
    }
}