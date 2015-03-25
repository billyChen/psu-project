/*
** screen.c for screen in /home/chen_c/rendu/PSU_2013_lemipc
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Wed Mar 26 19:15:26 2014 Billy CHEN
** Last update Sun Mar 30 18:34:20 2014 Billy CHEN
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

char		*create_plateau()
{
  char		*plateau;
  int		x;

  x = 0;
  plateau = malloc(101 * sizeof(*plateau));
  if (plateau == NULL)
    {
      printf("Error malloc\n");
      exit(EXIT_FAILURE);
    }
  while (x < 100)
    {
      plateau[x] = '.';
      x = x + 1;
    }
  return (plateau);
}

void		pause()
{
  int		continuer = 1;
  SDL_Event	event;

  while (continuer)
    {
      SDL_WaitEvent(&event);
      if (event.type == SDL_QUIT)
	continuer = 0;
    }
}

void		draw_plateau(SDL_Surface *ecran)
{
  SDL_Surface	*img;
  SDL_Rect	pos;
  int		i;
  int		mod;

  mod = 0;
  i = 0;
  pos.x = 0;
  pos.y = 0;
  img = NULL;
  while (i < 100)
    {
      if (i % 10 == 0 && i > 0)
	{
	  pos.x = 0;
	  pos.y += 102;
	  mod = mod - 1;
	}
      if (mod % 2 == 0)
	img = IMG_Load("img/black.png");
      else
	img = IMG_Load("img/white.png");
      SDL_BlitSurface(img, NULL, ecran, &pos);
      pos.x += 102;
      mod = mod + 1;
      if (mod > 1)
	mod = 0;
      i = i + 1;
    }
  SDL_Flip(ecran);
}

int		check_left(int seat, char *ptr_plateau)
{
  if (seat % 10 == 0)
    return (0);
  if (ptr_plateau[seat - 1] != '.')
    {
      if (seat % 10 >= 2)
	{
	  if (ptr_plateau[seat - 2] != '.')
	    return (2);
	}
      return (1);
    }
  else
    return (0);
}

int		check_right(int seat, char *ptr_plateau)
{
  if (seat % 10 == 9)
    return (0);
  if (ptr_plateau[seat + 1] != '.')
    {
      if (seat % 10 <= 7)
	{
	  if (ptr_plateau[seat + 2] != '.')
	    return (2);
	}
      return (1);
    }
  else
    return (0);
}

int		check_top(int seat, char *ptr_plateau)
{
  if (seat > 9)
    return (0);
  if (ptr_plateau[seat - 10] != '.')
    {
      if (seat >= 20)
	{
	  if (ptr_plateau[seat - 20] != '.')
	    return (2);
	}
      return (1);
    }
  else
    return (0);
}

int		check_bottom(int seat, char *ptr_plateau)
{
  if (seat > 89)
    return (0);
  if (ptr_plateau[seat + 10] != '.')
    {
      if (seat <= 70)
	{
	  if (ptr_plateau[seat - 2] != '.')
	    return (2);
	}
      return (1);
    }
  else
    return (0);
}

int		check_around(int seat, char *ptr_plateau)
{
  int		count;

  count = 0;
  if (seat == -1)
    return (-1);
  count += check_left(seat, ptr_plateau);
  count += check_right(seat, ptr_plateau);
  count += check_top(seat, ptr_plateau);
  count += check_bottom(seat, ptr_plateau);
  if (count > 1)
    return (-1);
  else
    return (0);
}

void		putPiece(SDL_Surface *ecran, char *ptr_plateau)
{
  int		seat;
  SDL_Surface	*img;
  SDL_Rect	pos;
  static int	mod = 0;

  img = NULL;
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

int		main(int argc, char **argv)
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

  i = 0;
  srand(time(NULL));
  ecran = NULL;
  keyplay = ftok("play", 0);
  key = ftok("map", 0);
  shm_id = shmget(key, 100, SHM_R | SHM_W);
  if (shm_id == -1)
    {
      shm_id = shmget(key, 100, IPC_CREAT | SHM_R | SHM_W);
      printf("Creating plateau [%d]\n", shm_id);
      ptr_plateau = shmat(shm_id, NULL, SHM_R | SHM_W);
      plateau = create_plateau();
      sprintf((char *)ptr_plateau, plateau);
    }
  ptr_plateau = shmat(shm_id, NULL, SHM_R | SHM_W);  
  sem_id = semget(key, 1, SHM_W | SHM_R);
  if (sem_id == -1)
    {
      printf("No players ! \n");
      return (0);
    }
  SDL_Init(SDL_INIT_VIDEO);
  ecran = SDL_SetVideoMode(1020, 1020, 32, SDL_HWSURFACE);
  draw_plateau(ecran);
  nbr_players = semctl(sem_id, 0, GETVAL);
  while (i < nbr_players)
    {
      putPiece(ecran, (char *)ptr_plateau);
      i = i + 1;
    }
  semPlay_id = semget(keyplay, 1, SHM_W | SHM_R);
  if (semPlay_id == -1)
    {
      printf("Unitialized semaphore [play]");
      exit(EXIT_FAILURE);
    }
  sops.sem_num = 0;
  sops.sem_op = 1;
  sops.sem_flg = 0;
  semop(semPlay_id, &sops, 1);
  pause();
  SDL_Quit();
  shmctl(shm_id, IPC_RMID, NULL);
  return EXIT_SUCCESS;
}
