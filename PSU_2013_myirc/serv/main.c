/*
** main.c for main in /home/chen_c/rendu/PSU_2013_myirc/serv
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Wed Apr 23 13:33:21 2014 Billy CHEN
** Last update Sun Apr 27 21:11:49 2014 Billy CHEN
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "struct.h"
#include <stdlib.h>

void			set_fd(t_env *e, int *fd_max, fd_set *fd_read)
{
  int			i;

  i = 0;
  while (i < MAX_FD)
    {
      if (e->fd_type[i] != FD_FREE)
	{
	  FD_SET(i, fd_read);
	  *fd_max = i;
	}
      i = i + 1;
    }
}

void			isset_fd(t_env *e, fd_set *fd_read)
{
  int			i;

  i = 0;
  while (i < MAX_FD)
    {
      if (FD_ISSET(i, fd_read))
	e->fct_read[i](e, i);
      i = i + 1;
    }
}

void			check_arg(int argc)
{
  if (argc != 2)
    {
      write(1, "[USAGE]: /server [port]\n", strlen("[USAGE]: /server [port]\n"));
      exit(EXIT_FAILURE);
    }
}

int			main(int argc, char **argv)
{
  t_env			e;
  int			i;
  int			fd_max;
  fd_set		fd_read;
  struct timeval	tv;

  check_arg(argc);
  memset(e.fd_type, FD_FREE, MAX_FD);
  e.port = atoi(argv[1]);
  add_server(&e);
  tv.tv_sec = 20;
  tv.tv_usec = 0;
  while (1)
    {
      FD_ZERO(&fd_read);
      fd_max = 0;
      i = 0;
      set_fd(&e, &fd_max, &fd_read);
      if (select(fd_max + 1, &fd_read, NULL, NULL, &tv) == -1)
	perror("select");
      isset_fd(&e, &fd_read);
    }
  return (0);
}
