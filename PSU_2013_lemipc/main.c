/*
** main.c for main in /home/chen_c/rendu/PSU_2013_lemipc
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Tue Mar 25 21:18:20 2014 Billy CHEN
** Last update Sun Mar 30 18:20:02 2014 Billy CHEN
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

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

void		getShm(t_lemipc *lem)
{
  lem->shm_id = shmget(lem->key, 100, SHM_R | SHM_W);
  if (lem->shm_id == -1)
    {
      lem->shm_id = shmget(lem->key, 100, IPC_CREAT | SHM_R | SHM_W);
      printf("Creating plateau [%d]\n", lem->shm_id);
      lem->ptr_plateau = shmat(lem->shm_id, NULL, SHM_R | SHM_W);
      lem->plateau = create_plateau();
      sprintf((char *)lem->ptr_plateau, lem->plateau);
    }
  lem->ptr_plateau = shmat(lem->shm_id, NULL, SHM_R | SHM_W);
}

int		getPiecePos(char *ptr_plateau, t_pion *p)
{
  int		i;
 
  i = 0;
  while (i < 100)
    {
      if (ptr_plateau[i] == 'o')
	{
	  p->x = i % 10;
	  p->y = i / 10;
	  p->team = 2;
	  p->totalXY = i;
	  return (0);
	}
      else if (ptr_plateau[i] == 'x')
	{
	  p->x = i % 10;
	  p->y = i / 10;
	  p->team = 1;
	  p->totalXY = i;
	  return (0);
	}
      i = i + 1;
    }
}

int		search_nearest_piece(char *ptr_plateau, char pion, t_pion *p)
{
  int		i;

  i = 0;
  while (i < 100)
    {
      if (ptr_plateau[i] == pion)
	{
	  p->target.x = i % 10;
	  p->target.y = i / 10;
	  p->target.totalXY = i;
	  return (0);
	}
      i = i + 1;
    }
  return (-1);
}

int		is_near_a_piece(char *ptr_plateau, t_pion *p)
{
  if (p->target.x == p->x - 1 || p->target.x == p->x + 1
      || p->target.y == p->y + 1 || p->target.y == p->y - 1)
    {
      return (0);
    }
  return (1);
}

int		move(char *ptr_plateau, t_pion *p)
{
  char		pion;
  char		ally;

  if (p->team == 1)
    {
      pion = 'o';
      ally = 'x';
    }
  else
    {
      pion = 'x';
      ally = 'o';
    }
  search_nearest_piece(ptr_plateau, pion, p);
  if (get_piece_around(ptr_plateau, p, ally) == -1)
    return (0);
  if (is_near_a_piece(ptr_plateau, p) == 1)
    move_to_target(p, ptr_plateau, ally);
}

void		add_sops(t_lemipc *lem, int id)
{
  lem->sops.sem_num = 0;
  lem->sops.sem_op = 1;
  lem->sops.sem_flg = 0;
  semop(id, &lem->sops, 1);
}

void		delete_sops(t_lemipc *lem, int id)
{
  lem->sops.sem_num = 0;
  lem->sops.sem_op = -1;
  lem->sops.sem_flg = 0;
  semop(id, &lem->sops, 1);
}

void		create_semPlay(int *semPlay_id, int keyplay)
{
  *semPlay_id = semget(keyplay, 1, SHM_W | SHM_R);
  if (*semPlay_id == -1)
    {
      *semPlay_id = semget(keyplay, 1, IPC_CREAT | SHM_W | SHM_R);
      semctl(*semPlay_id, 0, SETVAL, 0);
    }
}

void		init(t_lemipc *lem)
{
  lem->key = ftok("map", 0);
  lem->keyplay = ftok("play", 0);
  getShm(lem);
  printf("PLATEAU: %s\n", lem->ptr_plateau);
  lem->sem_id = semget(lem->key, 1, SHM_W | SHM_R);
  if (lem->sem_id == -1)
    {
      printf("Creating sem\n");
      lem->sem_id = semget(lem->key, 1, IPC_CREAT | SHM_W | SHM_R);
      semctl(lem->sem_id, 0, SETVAL, 1);
    }
  else
      add_sops(lem, lem->sem_id);
  create_semPlay(&lem->semPlay_id, lem->keyplay);  
}

int		main(int argc, char **argv)
{
  t_lemipc	lem;

  init(&lem);
  delete_sops(&lem, lem.semPlay_id);
  getPiecePos((char *)lem.ptr_plateau, &lem.p);
  if (semctl(lem.sem_id, 0, GETVAL) == 1)
    {
      shmctl(lem.shm_id, 0, IPC_RMID);
      semctl(lem.sem_id, 0, IPC_RMID);
      semctl(lem.semPlay_id, 0, IPC_RMID);
    }
  else
    {
      delete_sops(&lem, lem.sem_id);
      add_sops(&lem, lem.semPlay_id);
    }
}
