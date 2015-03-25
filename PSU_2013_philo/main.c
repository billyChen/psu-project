/*
** main.c for main in /home/chen_c/rendu/PSU_2013_philo
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Wed Mar 19 11:14:21 2014 Billy CHEN
** Last update Fri Jun 20 00:11:03 2014 Billy CHEN
*/

#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include "struct.h"
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define		NBR_PHILO 5
#define		SLEEPING_TIME 15000
#define		EATING_TIME 20000
#define		THINKING_TIME 5000
#define		GENERAL_TIME 150000
#define		AVERAGE_TIME 1

pthread_cond_t	mutex_cond[NBR_PHILO] = PTHREAD_COND_INITIALIZER;
pthread_mutex_t	mutex_stick[NBR_PHILO] = PTHREAD_MUTEX_INITIALIZER;	

void		eat(t_ph *philo)
{
  if (philo->num == NBR_PHILO && NBR_PHILO > 1)
    {
      printf("Le philosophe %d attend les baguettes\n", philo->num);
      pthread_mutex_lock(&mutex_stick[philo->num - 1]);
      pthread_mutex_lock(&mutex_stick[0]);
    }
  else
    {
      printf("Le philosophe %d attend les baguettes\n", philo->num);
      pthread_mutex_lock(&mutex_stick[philo->num - 1]);
      pthread_mutex_lock(&mutex_stick[philo->num]);
    }
  printf("Le philosophe %d prend les baguettes et mange\n", philo->num);
  usleep(SLEEPING_TIME);
  philo->life += 5;
  printf("Le philosophe %d relâche les baguettes, il lui reste %d vies\n", philo->num, philo->life);
  if (philo->num == NBR_PHILO && NBR_PHILO > 1)
    {
      philo->state = REST;
      pthread_mutex_unlock(&mutex_stick[philo->num - 1]);
      pthread_mutex_unlock(&mutex_stick[0]);
    }
  else
    {
      philo->state = REST;
      pthread_mutex_unlock(&mutex_stick[philo->num - 1]);
      pthread_mutex_unlock(&mutex_stick[philo->num]);
    }
}

void		think(t_ph *philo)
{  
  printf("Le philosophe %d attend une baguette avant de réfléchir\n", philo->num);
  pthread_mutex_lock(&mutex_stick[philo->num - 1]);
  printf("Le philosophe %d prend une baguette et commence à réfléchit\n", philo->num);
  usleep(THINKING_TIME);
  philo->state = EAT;
  printf("Le philosophe %d relâche une baguette, il lui reste %d vies\n", philo->num, philo->life);
  pthread_mutex_unlock(&mutex_stick[philo->num - 1]);
  philo->life -= (AVERAGE_TIME + 1) * 15;
}

void		rest(t_ph *philo)
{
  printf("Le philosophe %d relâche les baguettes et commence à dormir\n", philo->num);
  usleep(SLEEPING_TIME);
  printf("Le philosophe %d se régénère de 15 points de vie, il lui reste %d vies\n", philo->num, philo->life);
  philo->life += 15;
  if (philo->prev->state == THINK)
    philo->state = EAT;
  else
  philo->state = THINK;
}

void		*philo(void *n)
{
  int		nbrPhilo;
  t_ph		*philo;

  philo = (t_ph*) n;
  while (philo->life > 0)
    {
      if (philo->state == EAT)
	eat(philo);
      else if (philo->state == THINK)
	think(philo);
      else
	rest(philo);
      printf("\n");
      usleep(GENERAL_TIME);
    }
  printf("\n\nLe philosophe %d est mort\n", philo->num);
  pthread_exit(NULL);
}

void		MallocError(char *msg)
{
  printf("%s\n", msg);
  exit(EXIT_FAILURE);
}

t_headPh       	*init_list()
{
  t_headPh     	*head;
  t_ph		*ph;

  head = malloc(sizeof(*head));
  if (head == NULL)
    MallocError("Malloc error: head -> line 34");
  ph = malloc(sizeof(*ph));
  if (ph == NULL)
    MallocError("Malloc error: ph -> line 43");
  ph->num = 1;
  ph->state = REST;
  ph->life = 100 * (AVERAGE_TIME + 1);
  if (ph->life < 0)
    ph->life = ph->life * -1;
  ph->next = NULL;
  ph->prev = NULL;
  head->first = ph;
  return (head);
}

void		addPhilo(t_headPh *head, int num)
{
  t_ph		*newph;
  t_ph		*current;

  newph = malloc(sizeof(*newph));
  if (newph == NULL)
    MallocError("Malloc error: newph -> line 58");
  current = head->first;
  while (current->next != NULL)
    current = current->next;
  newph->state = REST;
  newph->num = num;
  newph->life = 100;
  if (num == NBR_PHILO + 1)
    {
      newph->next = head->first;
      head->first->prev = newph;
    }
  else
    newph->next = NULL;
  newph->prev = current;
  current->next = newph;
}

int		main(int argc, char **argv)
{
  int		i;
  pthread_t	th_philo[NBR_PHILO];
  t_headPh     	*ph;
  t_ph		*current;
  t_sdl		s;
 
  ph = init_list();
  i = 2;
  while (i <= NBR_PHILO + 1)
    {
      addPhilo(ph, i);
      i = i + 1;
    }
  current = ph->first;
  i = 1;
  while (i <= NBR_PHILO)
    {
      pthread_create(&th_philo[i], NULL, philo, current);
      i = i + 1;
      current = current->next;
    }
  pthread_exit(NULL);
}
