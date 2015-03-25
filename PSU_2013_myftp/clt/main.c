/*
** main.c for MyFTP in /home/bardet_e/rendu/PSU_2013_myftp
** 
** Made by eliot bardet
** Login   <bardet_e@epitech.net>
** 
** Started on  Wed Apr  9 15:54:41 2014 eliot bardet
** Last update Wed Apr  9 18:43:39 2014 eliot bardet
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "client.h"

void		end(t_client *cl)
{
  if (cl != NULL)
    {
      close(cl->sockfd);
      free(cl);
    }
}

int		main(int ac, char **av)
{
  t_client	*cl;

  cl = NULL;
  if (ac < 3)
    printf("Usage : ./client addr port\n");
  else
    {
      if ((cl = malloc(sizeof(*cl))) == NULL)
	{
	  perror("malloc");
	  return (1);
	}
      cl->addr = av[1];
      cl->port = atoi(av[2]);
      if (!(init_client(cl)))
	{
	  end(cl);
	  return (1);
	}
      launch_client(cl);
    }
  read_socket(cl->sockfd);
  end(cl);
  return (0);
}
