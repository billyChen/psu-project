/*
** main.c for MyFTP in /home/bardet_e/rendu/PSU_2013_myftp
** 
** Made by eliot bardet
** Login   <bardet_e@epitech.net>
** 
** Started on  Wed Apr  9 09:33:25 2014 eliot bardet
** Last update Wed Apr  9 13:25:46 2014 eliot bardet
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "server.h"

void		end(t_server *s)
{
  if (s != NULL)
    {
      close(s->sockfd);
      free(s);
    }
}

int		main(int ac, char **av)
{
  t_server	*s;

  s = NULL;
  if (ac < 2)
    printf("Usage : ./serveur port\n");
  else
    {
      if ((s = malloc(sizeof(*s))) == NULL)
	{
	  perror("malloc");
	  return (1);
	}
      s->port = atoi(av[1]);
      if (!(init_server(s)))
	{
	  end(s);
	  return (1);
	}
      launch_server(s);
    }
  end(s);
  return (0);
}
