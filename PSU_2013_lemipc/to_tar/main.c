/*
** main.c for main in /home/chen_c/rendu/PSU_2013_lemipc
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Tue Mar 25 21:18:20 2014 Billy CHEN
** Last update Sun Mar 30 20:27:53 2014 Billy CHEN
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "my.h"

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
      printf("Last player has left the game\n");
    }
  else
    {
      delete_sops(&lem, lem.sem_id);
      add_sops(&lem, lem.semPlay_id);
      printf("A player has left the game\n");
    }
}
