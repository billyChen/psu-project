/*
** screen.c for screen in /home/chen_c/rendu/PSU_2013_lemipc
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Wed Mar 26 19:15:26 2014 Billy CHEN
** Last update Sun Mar 30 20:29:15 2014 Billy CHEN
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "struct.h"
#include "my.h"

void		init_plat(t_plat *p)
{
  p->mod = 0;
  p->i = 0;
  p->pos.x = 0;
  p->pos.y = 0;
  p->img = NULL;
}

void		draw_plateau(SDL_Surface *ecran)
{
  t_plat	p;

  init_plat(&p);
  while (p.i < 100)
    {
      if (p.i % 10 == 0 && p.i > 0)
	{
	  p.pos.x = 0;
	  p.pos.y += 102;
	  p.mod = p.mod - 1;
	}
      if (p.mod % 2 == 0)
	p.img = IMG_Load("img/black.png");
      else
	p.img = IMG_Load("img/white.png");
      SDL_BlitSurface(p.img, NULL, ecran, &p.pos);
      p.pos.x += 102;
      p.mod = p.mod + 1;
      if (p.mod > 1)
	p.mod = 0;
      p.i = p.i + 1;
    }
  SDL_Flip(ecran);
}

void		putPiece(SDL_Surface *ecran, char *ptr_plateau)
{
  int		seat;
  SDL_Surface	*img;
  SDL_Rect	pos;
  static int	mod = 0;

  seat = -1;
  while (check_around(seat, ptr_plateau) == -1)
    {
      seat = -1;
      while (ptr_plateau[seat] != '.')
	seat = rand() % 100;
    }
  if (mod % 2 == 0)
    ptr_plateau[seat] = 'o';
  else
    ptr_plateau[seat] = 'x';
  pos.x = (seat % 10) * 102;
  pos.y = (seat / 10) * 102;
  if (mod % 2 == 0)
    img = IMG_Load("img/team2.png");
  else
    img = IMG_Load("img/team1.png");
  mod = mod + 1;
  SDL_BlitSurface(img, NULL, ecran, &pos);
  SDL_Flip(ecran);
}

int		init(t_display *d)
{
  d->i = 0;
  srand(time(NULL));
  d->ecran = NULL;
  d->keyplay = ftok("play", 0);
  d->key = ftok("map", 0);
  d->shm_id = shmget(d->key, 100, SHM_R | SHM_W);
  if (d->shm_id == -1)
    {
      d->shm_id = shmget(d->key, 100, IPC_CREAT | SHM_R | SHM_W);
      printf("Creating plateau [%d]\n", d->shm_id);
      d->ptr_plateau = shmat(d->shm_id, NULL, SHM_R | SHM_W);
      d->plateau = create_plateau();
      sprintf((char *)d->ptr_plateau, d->plateau);
    }
  d->ptr_plateau = shmat(d->shm_id, NULL, SHM_R | SHM_W);
  d->sem_id = semget(d->key, 1, SHM_W | SHM_R);
  if (d->sem_id == -1)
    {
      printf("No players ! \n");
      return (0);
    }
  SDL_Init(SDL_INIT_VIDEO);
}

int		main(int argc, char **argv)
{
  t_display	d;

  init(&d);
  d.ecran = SDL_SetVideoMode(1020, 1020, 32, SDL_HWSURFACE);
  draw_plateau(d.ecran);
  d.nbr_players = semctl(d.sem_id, 0, GETVAL);
  while (d.i < d.nbr_players)
    {
      putPiece(d.ecran, (char *)d.ptr_plateau);
      d.i = d.i + 1;
    }
  d.semPlay_id = semget(d.keyplay, 1, SHM_W | SHM_R);
  if (d.semPlay_id == -1)
    {
      printf("Unitialized semaphore [play]\n");
      exit(EXIT_FAILURE);
    }
  d.sops.sem_num = 0;
  d.sops.sem_op = 1;
  d.sops.sem_flg = 0;
  semop(d.semPlay_id, &d.sops, 1);
  pause();
  SDL_Quit();
  shmctl(d.shm_id, IPC_RMID, NULL);
  return EXIT_SUCCESS;
}
