/*
** msg.c for msg in /home/chen_c/rendu/PSU_2013_myirc/serv
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Sun Apr 27 01:16:38 2014 Billy CHEN
** Last update Sun Apr 27 21:08:46 2014 Billy CHEN
*/

#include "struct.h"
#include <stdlib.h>
#include <string.h>

int			malloc_msg_name(char *buf, int *mark, char *name, int fd)
{
  int			i;
  int			size;

  size = 0;
  i = 0;
  while (buf[i] != ' ' && buf[i])
      i = i + 1;
  if (buf[i] != ' ')
    {
      write(fd, "/msg [name] [msg]\n", strlen("/msg [name] [msg]\n"));
      return (-1);
    }
  *mark = i;
  while (buf[i])
    {
      i = i + 1;
      size = size + 1;
    }
  name = malloc((size + 1) * sizeof(*name));
  if (name == NULL)
    {
      write(1, "Malloc error\n", strlen("Malloc error\n"));
      exit(EXIT_FAILURE);
    }
  return (size);
}

void			fill_msg_name(char *buf, int *i, char *name, int *mark)
{
  int			x;

  x = 0;
  while (buf[*i] && buf[*i] != ' ')
    {
      name[x] = buf[*i];
      x = x + 1;
      *i = *i + 1;
    }
  name[x] = '\0';
  *mark = *i;
  *i = *i + 1;
}

void			malloc_msg(char *buf, int i, char *msg)
{
  int			size;

  size = 0;
  while (buf[i] != '\n' && buf[i])
    {
      size = size + 1;
      i = i + 1;
    }
  msg = malloc((size + 1) * sizeof(*msg));
  if (msg == NULL)
    {
      write(1, "Malloc error\n", strlen("Malloc error\n"));
      exit(EXIT_FAILURE);
    }
}

void			fill_msg(char *buf, int i, char *msg)
{
  int			x;

  x = 0;
  while (buf[i] != '\n' && buf[i])
    {
      msg[x] = buf[i];
      i = i + 1;
      x = x + 1;
    }
  msg[x] = 0;
}

void			write_msg(t_env *e, int fd, char *msg, int i)
{
  write(i, "[", 1);
  write(i, e->username[fd], strlen(e->username[fd]));
  write(i, "]: ", 3);
  write(i, msg, strlen(msg));
  write(i, "\n", 1);
}
