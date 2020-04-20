/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** my_ftp
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include <alloca.h>
#include <signal.h>
#include <unistd.h>
#include <sys/select.h>
#include <dirent.h>

#undef EXIT_FAILURE
#define EXIT_FAILURE 84
#define NO_PROBLEM 3
/* Max character who can read or write */
#define MAX_SIZE 2048
/* Max simultaneous connection on this server */
#define MAX_CONNECTION 1024

#ifndef MY_FTP_
#define NY_FTP_

/* Contain all client informations */
typedef struct client_s
{
    /* Next node of the linked list */
    struct client_s *next;
    struct sockaddr_in child_addr;
    struct sockaddr_in child_peer_addr;
    socklen_t child_peer_addr_size;
    /* Contain at incomplet command */
    char *pending_cmd;
    /* Contaon the date to send at user */
    char *write_buffer;
    char *child_write_buffer;
    char *child_read_buffer;
    char *child_rfc_message;
    char *username;
    char *password;
    /* Contain the input of the client */
    char *command;
    /* Contain the past of the home folder of the user*/
    char *path;
    /* Socket number who is using for speak with a user */
    int fd;
    /* fd of child server socket */
    int scfd;
    /* fd client of child server*/
    int ccfd;
    /* Status of connection of the user:
    its is equal true if user is connecting,
    else its is equal at false */
    bool connection_status;
    /* Status of node, if its true the node will be free */
    bool is_free;
    /* status of port mode */
    bool port;
    /* status of pasv mode */
    bool pasv;
    bool connect;
} client_t;

/* Contain all server informations */
typedef struct ftp_s
{
    fd_set rset;
    fd_set wset;
    struct sockaddr_in my_addr;
    struct sockaddr_in peer_addr;
    socklen_t peer_addr_size;
    char *default_path;
    int port;
    int sfd;
    int cfd;
    int return_value;
} ftp_t;

typedef enum rfc_message_s
{
    /* Service ready in nnn minutes. */
    CODE_120,
    /* Data connection already open; transfer starting. */
    CODE_125,
    /* File status okay; about to open data connection. */
    CODE_150,
    /* Command okay. */
    CODE_200,
    /* Help message.
        On how to use the server or the meaning of a particular
        non-standard command.  This reply is useful only to the
        human user. */
    CODE_214,
    /* Service ready for new user. */
    CODE_220,
    /* Service closing control connection.
    Logged out if appropriate.*/
    CODE_221,
    /* Closing data connection.
        Requested file action successful (for example, file
        transfer or file abort). */
    CODE_226,
    /* Entering Passive Mode (h1, h2 , h3, h4 , p1, p2). */
    CODE_227,
    /* User logged in, proceed. */
    CODE_230,
    /* Requested file action okay, completed. */
    CODE_250,
    /* "PATHNAME" created. */
    CODE_257,
    /* User name okay, need password. */
    CODE_331,
    /* Need account for login. */
    CODE_332,
    /* Not logged in. */
    CODE_530,
    /* 530 Login incorrect. */
    CODE_530F,
    /* 500 Unknown command. */
    CODE_500,
    /* 501 Syntax error in parameters or arguments. */
    CODE_501,
    /* 550 Requested action not taken.
        File unavailable (e.g., file not found, no access). */
    CODE_550,
    /* Use PORT or PASV first. */
    CODE_425,
    /* 421 Service not available, closing control connection.
        This may be a reply to any command if the service knows it
        must shut down. */
    CODE_421
} rfc_message_t;

extern const char *default_username;
extern const char *default_password;
extern void (* const rfc_command[])(client_t *client, ftp_t *ftp);
extern const char *rfc_message[];
extern const char *command_name[];
extern const char *command_description[];

void grep_users_command(ftp_t **ftp, client_t **client_list);
void error_gestion(int ac, char **av, ftp_t *ftp);

/* Linked list function */
bool initialise_client_struct(client_t **client_list, int cfd);
bool initialise_ftp_struct(ftp_t **ftp);
bool add_node(int cfd, client_t **list);
bool list_is_empty(client_t *client);
void delete_node(client_t *node, client_t **list);
void display_linked_list_contain(client_t *client_list);

/* Server function */
int server_init(ftp_t **ftp);
int check_connection(ftp_t **ftp, client_t **client_list);
int new_connection(ftp_t **ftp, client_t **client_list);
int port_connection(ftp_t **ftp, client_t **client_list);
int pasv_connection(ftp_t **ftp, client_t **client_list);
int server_loop(ftp_t **ftp, client_t **client_list);
int check_user_log(client_t *client);
int server_set_read_fdlist(ftp_t **ftp, client_t *client_list);
int server_child_set_read_fdlist(ftp_t **ftp, client_t *client_list);
int server_set_write_fdlist(ftp_t **ftp, client_t *client_list);
int server_child_set_write_fdlist(ftp_t **ftp, client_t *client_list);
bool pars_command(client_t *client_list);
void excute_command(client_t **client_list, ftp_t *ftp);
void log_client(client_t *client);
void send_data(client_t **client_list, ftp_t *ftp);
void send_child_data(client_t **client_list, ftp_t *ftp);

/* Utilities function */
char **str_to_array(char *str, char separator);
char *str_cat_command(void);
char *get_str(client_t *client, int pos);
char *get_argument(char *str);
int size_of_array(char **array);
bool my_strcmp(char *str, char *str2);
bool my_str_const_cmp(char *str, const char *str2);
bool directory_exist(char *str);
bool is_path(char *str);
bool check_port_pasv(client_t * client);
bool only_one_argument(client_t *client);
bool is_function(client_t *client, char *name);
void my_strcat(char **str1, char *str2);
void my_const_strcat(char **str1, const char *str2);
void delete_useless_space(client_t *client);
void bad_synthax(client_t *client);
void display_array(char **array);

/* RFC commannd */
void quit(client_t *client, ftp_t *ftp);
void user(client_t *client, ftp_t *ftp);
void pass(client_t *client, ftp_t *ftp);
void pwd(client_t *client, ftp_t *ftp);
void help(client_t *client, ftp_t *ftp);
void noop(client_t *client, ftp_t *ftp);
void cwd(client_t *client, ftp_t *ftp);
void dele(client_t *client, ftp_t *ftp);
void cdup(client_t *client, ftp_t *ftp);
void port(client_t *client, ftp_t *ftp);
void pasv(client_t *client, ftp_t *ftp);
void list(client_t *client, ftp_t *ftp);
void retr(client_t *client, ftp_t *ftp);

char *get_ipadress(client_t *client);
int get_port(client_t *client);
bool port_init_child(client_t *client);
bool pasv_init_child(client_t *client);
bool more_one_argument(client_t *client);
#endif
