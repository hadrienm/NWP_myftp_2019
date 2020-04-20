##
## EPITECH PROJECT, 2020
## NWP_myftp_2019
## File description:
## Makefile
##

NAME	= myftp

CC	= gcc

RM	= rm -f

SRCS	= ./main.c \
	  ./src/argument_gestion.c \
	  ./src/global_variable/command_description.c \
	  ./src/global_variable/default_parameter.c \
	  ./src/global_variable/ptr_function.c \
	  ./src/global_variable/rfc_message.c \
	  ./src/link_list/add_node.c \
	  ./src/link_list/delete_node.c \
	  ./src/link_list/initialise.c \
	  ./src/link_list/linked_list.c \
	  ./src/server/command_gestion/excute_command.c \
	  ./src/server/command_gestion/get_user_command.c \
	  ./src/server/command_gestion/pars_command.c \
	  ./src/server/command_gestion/rfc_command/cdup.c \
	  ./src/server/command_gestion/rfc_command/common_function/synthax_gestion.c \
	  ./src/server/command_gestion/rfc_command/common_function/utilities_function.c \
	  ./src/server/command_gestion/rfc_command/cwd.c \
	  ./src/server/command_gestion/rfc_command/dele.c \
	  ./src/server/command_gestion/rfc_command/help.c \
	  ./src/server/command_gestion/rfc_command/list.c \
	  ./src/server/command_gestion/rfc_command/noop.c \
	  ./src/server/command_gestion/rfc_command/pass.c \
	  ./src/server/command_gestion/rfc_command/pasv/pasv.c \
	  ./src/server/command_gestion/rfc_command/pasv/pasv_init_child.c \
	  ./src/server/command_gestion/rfc_command/port/child_port_init.c \
	  ./src/server/command_gestion/rfc_command/port/port.c \
	  ./src/server/command_gestion/rfc_command/pwd.c \
	  ./src/server/command_gestion/rfc_command/quit.c \
	  ./src/server/command_gestion/rfc_command/retr.c \
	  ./src/server/command_gestion/rfc_command/user.c \
	  ./src/server/command_gestion/send_data.c \
	  ./src/server/connection.c \
	  ./src/server/server_init.c \
	  ./src/server/server_loop.c \
	  ./src/server/server_set.c \
	  ./src/utilities_function/folder_function.c \
	  ./src/utilities_function/my_str_cat.c \
	  ./src/utilities_function/str_function.c \
	  ./src/utilities_function/str_to_array.c \
	  ./src/utilities_function/strcmp.c

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./include/
CFLAGS += -g -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
