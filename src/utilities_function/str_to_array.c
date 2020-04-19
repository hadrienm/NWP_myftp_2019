/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** str_to_arry
*/

#include "my_ftp.h"

static char **malloc_tab(char *str, char separator, int pos)
{
    char **array = NULL;
    int nb_line = 1;
    int index_line = 0;
    int index_char = 0;

    for (int a = 0; str[a] != '\0'; ++a)
        if (str[a] == separator)
            nb_line++;
    array = malloc(sizeof(char *) * (nb_line + 1));
    for (int a = pos; str[a] != '\0'; ++a, ++index_char) {
        if (str[a] == separator || str[a + 1] == '\0') {
            array[index_line] = malloc(sizeof(char) * (index_char + 2));
            memset(array[index_line], '\0', index_char + 2);
            ++index_line;
            index_char = 0;
        }
    }
    array[index_line] = NULL;
    return array;
}

char **str_to_array(char *str, char separator)
{
    int index_char = 0;
    int index_line = 0;
    int pos = 0;
    char **array = NULL;

    array = malloc_tab(str, separator, pos);
    for (; str[pos] != '\0'; ++pos) {
        if (str[pos] == separator) {
            ++index_line;
            index_char = 0;
        } else {
            array[index_line][index_char] = str[pos];
            ++index_char;
        }
    }
    return array;
}
