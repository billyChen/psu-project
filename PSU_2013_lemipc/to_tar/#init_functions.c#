/*
** init_functions.c for init_Functions in /home/chen_c/rendu/PSU_2013_lemipc/to_tar
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Sun Mar 30 18:22:54 2014 Billy CHEN
** Last update Sun Mar 30 20:27:47 2014 Billy CHEN
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

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
  lem->sem_id = semget(lem->key, 1, SHM_W | SHM_R);
  printf("Add one player\n");
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
