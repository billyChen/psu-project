##
## Makefile for Makefile in /home/chen_c/rendu/PSU_2013_myftp
## 
## Made by Billy CHEN
## Login   <chen_c@epitech.net>
## 
## Started on  Sun Apr 13 22:21:30 2014 Billy CHEN
## Last update Sun Apr 13 22:37:36 2014 Billy CHEN
##

NAME_CLIENT = client

NAME_SERVER = serveur

SRC_CLIENT = 	clt/main.c\
		clt/commands.c\
		clt/client.c\
		clt/attach_string.c\

SRC_SERVER =	srv/main.c\
		srv/server.c\
		srv/commands.c\
		srv/cmd_quit.c\
		srv/cmd_ls.c\
		srv/attach_string.c

OBJ_CLIENT =	$(SRC_CLIENT:.c=.o)

OBJ_SERVER =	$(SRC_SERVER:.c=.o)


all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT)
	gcc -o clt/$(NAME_CLIENT) $(OBJ_CLIENT);

$(NAME_SERVER): $(OBJ_SERVER)
		gcc -o $(NAME_SERVER) $(OBJ_SERVER);
clean:
	rm -f $(OBJ_CLIENT)
	rm -f $(OBJ_SERVER)
fclean:	clean

re:



