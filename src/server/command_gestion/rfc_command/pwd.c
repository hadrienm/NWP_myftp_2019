/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** pwd
*/

#include "my_ftp.h"

static void make_message(client_t *client, char *str)
{
    char *word = malloc(sizeof(char) * strlen(str));
    char *tmp = NULL;
    size_t len = 0;
    bool begin = false;

    memset(word, '\0', strlen(str));
    word[0] = '/';
    for (int a = 0, index = 1; str[a] != '\0'; ++a) {
        if (str[a] == '/' && begin == false)
            begin = true;
        else if (begin == true) {
            word[index] = str[a];
            ++index;
        }
    }
    len = strlen(rfc_message[CODE_257]) + strlen(word) + 1;
    tmp = malloc(sizeof(char) * (len));
    sprintf(tmp, "257 \"%s\" created.\r\n", word);
    my_strcat(&client->write_buffer, tmp);
    free(tmp);
    free(word);
}

static void set_rfc_message(client_t *client, ftp_t *ftp)
{
    if (client->path != NULL) {
        make_message(client, client->path);
    } else {
        make_message(client, ftp->default_path);
    }
}

void pwd(client_t *client, ftp_t *ftp)
{
    if (client->command == NULL)
        return;
    if (is_function(client, "PWD") == false)
        return;
    if (check_user_log(client) == EXIT_FAILURE)
        return;
    set_rfc_message(client, ftp);
    free(client->command);
    client->command = NULL;
}