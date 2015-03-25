/*
** sdl_function.c for sdl_function in /home/chen_c/rendu/PSU_2013_lemipc/to_tar
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Sun Mar 30 18:54:21 2014 Billy CHEN
** Last update Sun Mar 30 20:23:57 2014 Billy CHEN
*/

#include <SDL/SDL.h>

void		pause()
{
  int		continuer;
  SDL_Event	event;

  continuer = 1;
  while (continuer)
    {
      SDL_WaitEvent(&event);
      if (event.type == SDL_QUIT)
	continuer = 0;
    }
}
