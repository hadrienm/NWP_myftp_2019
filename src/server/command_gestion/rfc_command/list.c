/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** list
*/

#include "my_ftp.h"

static bool list_error_gestion(client_t *client)
{
    if (client->command == NULL)
        return false;
    if (is_function(client, "list") == false)
        return false;
    if (check_user_log(client) == EXIT_FAILURE)
        return false;
    if (check_port_pasv(client) == false)
        return false;
    return true;
}

static char *list_get_argument(client_t *client, ftp_t *ftp, char **array)
{
    char *command = NULL;

    my_const_strcat(&command, "ls -la ");
    if (array[1] != NULL && array[1][0] == '/') {
        my_const_strcat(&command, ftp->default_path);
        my_const_strcat(&command, array[1]);
        return command;
    }
    if (client->path != NULL)
        my_const_strcat(&command, client->path);
    else
        my_const_strcat(&command, ftp->default_path);
    if (array[1] != NULL) {
        my_const_strcat(&command, "/");
        my_strcat(&command, array[1]);
    }
    return command;
}

void list(client_t *client, ftp_t *ftp)
{
    char **array = NULL;
    char *buff = malloc(sizeof(char) * MAX_SIZE);
    char *command = NULL;

    if (list_error_gestion(client) == false)
        return;
    buff = memset(buff, '\0', MAX_SIZE);
    array = str_to_array(client->command, ' ');
    command = list_get_argument(client, ftp, array);
    FILE *file = popen(command, "r");
    while (!feof(file) && (fread(buff, 1, 1, file)) > 0)
        my_strcat(&client->child_write_buffer, buff);
    if (client->child_write_buffer != NULL)
        my_const_strcat(&client->child_rfc_message, rfc_message[CODE_150]);
    else
        my_const_strcat(&client->child_rfc_message, rfc_message[CODE_550]);
    pclose(file);
    free(command);
    free(client->command);
    client->command = NULL;
}
