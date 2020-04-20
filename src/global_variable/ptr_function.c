/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** ptr_function
*/

#include "my_ftp.h"

void (*const rfc_command[])(client_t *client, ftp_t *ftp) =
    {quit, user, pass, pwd, help, noop, cwd, dele, cdup, port, pasv,
    list, retr, NULL};
