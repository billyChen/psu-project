/*
** nickname.c for nickname in /home/chen_c/rendu/PSU_2013_myirc/serv
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Sun Apr 27 00:41:11 2014 Billy CHEN
** Last update Sun Apr 27 21:16:07 2014 Billy CHEN
*/

#include "struct.h"
#include <string.h>
#include <stdlib.h>

void			write_nickname_msg(t_env *e, int fd, int size)
{
  int			i;

  i = 0;
  while (i < MAX_FD)
    {
      if (e->fd_type[i] == FD_CLIENT && i != fd)
	{
	  write(i, "User ", 5);
	  write(i, i - '0', 1);
	  write(i, " changed his name to ", strlen(" changed his name to "));
	  write(i, e->username[fd], size);
	  write(i, "\n", 1);
	}
      i = i + 1;
    }
}

int			malloc_username(char *buf, int fd, t_env *e, int *mark)
{
  int			size;
  int			i;

  i = 0;
  size = 0;
  while (buf[i] != ' ' && buf[i] && buf[i] != '\n')
    i = i + 1;
  if (buf[i] != ' ')
    {
      write(fd, "[Usage]: /nick [name]\n", strlen("[Usage]: /nick [name]\n"));
      return (-1);
    }
  free(e->username[fd]);
  *mark = i;
  while (buf[i])
    {
      i = i + 1;
      size = size + 1;
    }
  e->username[fd] = malloc((size + 1) * sizeof(*e->username[fd]));
  if (e->username[fd] == NULL)
    {
      write(1, "Malloc error\n", strlen("Malloc error\n"));
      exit(EXIT_FAILURE);
    }
  return (size);
}
