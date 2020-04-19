/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** main
*/

#include "my_ftp.h"

int main(int ac, char **av)
{
    ftp_t *ftp = NULL;
    client_t *client_list = NULL;

    if (initialise_ftp_struct(&ftp) == false)
    {
        fprintf(stderr, "Error creating ftp server.\n");
        return EXIT_FAILURE;
    }
    error_gestion(ac, av, ftp);
    if (ftp->return_value != NO_PROBLEM)
        return ftp->return_value;
    if (server_init(&ftp) == EXIT_FAILURE)
        return EXIT_FAILURE;
    server_loop(&ftp, &client_list);
    close(ftp->sfd);
    return 0;
}
