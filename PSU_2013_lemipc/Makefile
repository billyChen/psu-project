##
## Makefile for Makefile in /home/chen_c/rendu/PSU_2013_lemipc
## 
## Made by Billy CHEN
## Login   <chen_c@epitech.net>
## 
## Started on  Tue Mar 25 21:18:40 2014 Billy CHEN
## Last update Sun Mar 30 18:13:24 2014 Billy CHEN
##

SRC = 	main.c\
	move_direction.c\
	get_piece_around.c\
	get_corner_place.c\

SRC_DISPLAY = screen.c\

OBJ = $(SRC:.c=.o)

OBJ_DISPLAY = $(SRC_DISPLAY:.c=.o)

NAME = lemipc

NAME_DISPLAY = display

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_DISPLAY)
	gcc -o $(NAME) $(OBJ)
	gcc -o $(NAME_DISPLAY) $(OBJ_DISPLAY) -lSDL -lSDL_image

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_DISPLAY)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_DISPLAY)

re: fclean all


