/*
** function.c for functions in /home/chen_c/rendu/PSU_2013_myirc/serv
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Thu Apr 24 20:55:51 2014 Billy CHEN
** Last update Sun Apr 27 01:06:15 2014 Billy CHEN
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

void			client_read(t_env *e, int fd)
{
  int			r;
  char			buf[4096];
  int			i;
  char			*cmd[9];

  fill_cmd(cmd);
  i = 0;
  r = read(fd, buf, 4096);
  if (r > 0)
    {
      buf[r] = '\0';
      check_ptrfunc(cmd, buf, e, fd);
    }
  else
    {
      printf("%d: Connection closed\n");
      close(fd);
      e->fd_type[fd] = FD_FREE;
    }
}

void			add_client(t_env *e, int s)
{
  int			cs;
  struct sockaddr_in	client_sin;
  int			client_sin_len;

  client_sin_len = sizeof(client_sin);
  cs = accept(s, (struct sockaddr *)&client_sin, &client_sin_len);
  e->fd_type[cs] = FD_CLIENT;
  e->fct_read[cs] = client_read;
}

void			server_read(t_env *e, int fd)
{
  printf("New client\n");
  add_client(e, fd);
}

void			add_server(t_env *e)
{
  int			s;
  struct sockaddr_in	sin;
  int			i;

  i = 0;
  s = socket(PF_INET, SOCK_STREAM, 0);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(e->port);
  sin.sin_addr.s_addr = INADDR_ANY;
  bind(s, (struct sockaddr*)&sin, sizeof(sin));
  listen(s, 42);
  e->fd_type[s] = FD_SERVER;
  e->fct_read[s] = server_read;
  while (i < MAX_FD)
    {
      e->username[i] = malloc(10 * sizeof(*e->username[i]));
      if (e->username[i] == NULL)
	{
	  write(1, "Malloc error : ", strlen("Malloc error : "));
	  write(1, "function.c: line 107\n",strlen("function.c: line 107\n"));
	  exit(EXIT_FAILURE);
	}
      strcpy(e->username[i], "Anonymous");
      i = i + 1;
    }
}
