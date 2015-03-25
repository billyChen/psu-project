/*
** struct.h for struct in /home/chen_c/rendu/PSU_2013_lemipc
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Sat Mar 29 14:37:45 2014 Billy CHEN
** Last update Sun Mar 30 18:57:52 2014 Billy CHEN
*/

#ifndef STRUCT_H
# define STRUCT_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

typedef struct s_tar t_tar;
struct s_tar
{
  int		x;
  int		y;
  int		totalXY;
};

typedef struct s_pion t_pion;
struct s_pion
{
  int		x;
  int		y;
  int		team;
  int		totalXY;
  struct s_tar	target;
};

typedef struct s_lemipc t_lemipc;
struct s_lemipc
{
  key_t		key;
  key_t		keyplay;
  int		shm_id;
  void		*ptr_plateau;
  char		*plateau;
  struct sembuf	sops;
  int		sem_id;
  int		semPlay_id;
  t_pion	p;
};

typedef struct s_display t_display;
struct s_display
{
  key_t		key;
  key_t		keyplay;
  int		shm_id;
  void		*ptr_plateau;
  char		*plateau;
  SDL_Surface	*ecran;
  int		sem_id;
  int		nbr_players;
  int		i;
  int		semPlay_id;
  struct sembuf	sops;
};

typedef struct s_plat t_plat;
struct s_plat
{
  SDL_Surface	*img;
  SDL_Rect	pos;
  int		i;
  int		mod;
};

#endif /* !STRUCT_H*/
