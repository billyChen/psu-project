/*
** struct.h for struct in /home/chen_c/rendu/PSU_2013_philo
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Wed Mar 19 17:44:22 2014 Billy CHEN
** Last update Sat Mar 22 19:46:23 2014 Billy CHEN
*/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#ifndef		STRUCT_H
# define       	STRUCT_H

typedef enum State	State;
enum State
  {
    EAT, THINK, REST
  };

typedef struct s_sdl	t_sdl;
struct s_sdl
{
  SDL_Surface	*ecran;
  SDL_Surface	*img;
  SDL_Rect	pos;
};

typedef struct s_ph	t_ph;
struct s_ph
{
  int		x;
  int		y;
  int		num;
  State		state;
  int		life;
  struct s_ph	*next;
  struct s_ph	*prev;
};
  
typedef struct s_headPh t_headPh;
struct s_headPh
{
  struct s_ph	*first;
};


#endif /* !STRUCT_H */
