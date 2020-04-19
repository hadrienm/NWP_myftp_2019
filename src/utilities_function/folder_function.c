/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** folder_function
*/

#include "my_ftp.h"

bool directory_exist(char *str)
{
    DIR* dir = opendir(str);
    if (dir) {
        closedir(dir);
    } else if (ENOENT == errno) {
        fprintf(stderr, "Directory %s does not exist.\r\n", str);
        return false;
    } else {
        fprintf(stderr, "Can not open directory\r\n");
        return false;
    }
    return true;
}
