##
## Makefile for Makefile in /home/chen_c/rendu/PSU_2013_philo
## 
## Made by Billy CHEN
## Login   <chen_c@epitech.net>
## 
## Started on  Wed Mar 19 11:12:49 2014 Billy CHEN
## Last update Sat Mar 22 16:26:33 2014 Billy CHEN
##

SRC =	main.c\

OBJ =	$(SRC:.c=.o)

NAME =	philo

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) -lpthread -lSDL -lSDL_image

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
