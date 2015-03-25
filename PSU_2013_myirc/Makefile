##
## Makefile for Makefile in /home/chen_c/rendu/PSU_2013_myirc
## 
## Made by Billy CHEN
## Login   <chen_c@epitech.net>
## 
## Started on  Thu Apr 17 00:35:14 2014 Billy CHEN
## Last update Sun Apr 27 21:05:05 2014 Billy CHEN
##

NAME_SERV = server

SRC_SERV = 	serv/main.c\
		serv/function.c\
		serv/initialization.c\
		serv/command.c\
		serv/function2.c\
		serv/nickname.c\
		serv/msg.c\

OBJ_SERV = $(SRC_SERV:.c=.o)

NAME_CLIENT = client

SRC_CLIENT =	client/main.c\

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

all: $(NAME_SERV) $(NAME_CLIENT)

$(NAME_SERV): $(OBJ_SERV) $(OBJ_CLIENT)
		gcc -Wall -W -Werror -o serv/$(NAME_SERV) $(OBJ_SERV)
		gcc -Wall -W -Werror -o client/$(NAME_CLIENT) $(OBJ_CLIENT)

clean:
	rm -f $(OBJ_SERV)
	rm -f $(OBJ_CLIENT)

fclean: clean
	rm -f serv/$(NAME_SERV)
	rm -f client/$(NAME_CLIENT)

re: fclean all
