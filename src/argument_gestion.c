/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** argument_gestion
*/

#include "my_ftp.h"

/* Display README
Return EXIT_FAILURE if error has ocurred
Return EXIT_SUCCESS if any error has ocurred */
static int display_usage(void)
{
    char *buffer = alloca(MAX_SIZE);
    char *filename = "README.md";
    FILE *pFile;

    pFile = fopen(filename, "r");
    if (!pFile) {
        fprintf(stderr, "Error trying to open file : %s\n", filename);
        return EXIT_FAILURE;
    }
    while (fgets(buffer, MAX_SIZE, pFile))
        fprintf(stderr,"%s", buffer);
    fclose(pFile);
    return EXIT_SUCCESS;
}

/* Set port number
Return false if error has ocurred
Return true if any error has ocurred */
static bool set_port(char *str, ftp_t *ftp)
{
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] < '0' || str[i] > '9') {
            fprintf(stderr, "Invalid input : %s\n", str);
            display_usage();
            return false;
        }
    }
    ftp->port = atoi(str);
    return true;
}

static bool set_default_path(char *str, ftp_t *ftp)
{
    if (ftp == NULL)
        return false;
    if (directory_exist(str) == false)
        return false;
    ftp->default_path = strdup(str);
    if (ftp->default_path[strlen(ftp->default_path) - 1] == '/')
        ftp->default_path[strlen(ftp->default_path) - 1] = '\0';
    return true;
}

/* Check is all argument is good */
void error_gestion(int ac, char **av, ftp_t *ftp)
{
    if (ac != 3) {
        fprintf(stderr, "Invalid arguments, exiting.");
        display_usage();
        ftp->return_value = EXIT_FAILURE;
        return;
    } else if (strcmp(av[1], "-help") == 0) {
        if (display_usage() == EXIT_FAILURE)
            ftp->return_value = EXIT_FAILURE;
        ftp->return_value = EXIT_SUCCESS;
        return;
    }
    if (set_port(av[1], ftp) == false)
        ftp->return_value = EXIT_FAILURE;
    if (set_default_path(av[2], ftp) == false)
        ftp->return_value = EXIT_FAILURE;
}
