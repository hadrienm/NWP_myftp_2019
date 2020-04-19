/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** rfc_message
*/

#include "my_ftp.h"

const char *rfc_message[] = {
    "120 Service ready in nnn minutes.\r\n",
    "125 Data connection already open; transfer starting.\r\n",
    "150 File status okay; about to open data connection.\r\n",
    "200 Command okay.\r\n",
    "214 Help message. "
    "On how to use the server or the meaning of a particular "
    "non-standard command. his reply is useful only to the "
    "human user.\r\n",
    "220 Service ready for new user.\r\n",
    "221 Service closing control connection. "
    "Logged out if appropriate.\r\n",
    "226 Closing data connection."
    "Requested file action successful (for example, file"
    "transfer or file abort).\r\n",
    "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).\r\n",
    "230 User logged in, proceed.\r\n",
    "250 Requested file action okay, completed.\r\n",
    "257 \"\" created.\r\n",
    "331 User name okay, need password.\r\n",
    "332 Need account for login.\r\n",
    "530 Not logged in.\r\n",
    "530 Login incorrect.\r\n",
    "500 Unknown command.\r\n",
    "501 Syntax error in parameters or arguments.\r\n",
    "550 Requested action not taken. "
    "File unavailable (e.g., file not found, no access).\r\n",
    "425 Use PORT or PASV first.\r\n",
    "421 Service not available, closing control connection. "
    "This may be a reply to any command if the service knows it "
    "must shut down.\r\n"};