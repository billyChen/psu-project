/*
** command.c for command in /home/chen_c/rendu/PSU_2013_myirc/serv
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Thu Apr 24 21:50:52 2014 Billy CHEN
** Last update Sun Apr 27 21:16:11 2014 Billy CHEN
*/

#include "struct.h"
#include <string.h>
#include <stdlib.h>

int			nickname(t_env *e, int fd, char *buf)
{
  int			i;
  int			size;
  int			mark;
  int			x;

  x = 0;
  size = 0;
  i = 0;
  size = malloc_username(buf, fd, e, &mark);
  i = mark + 1;
  while (buf[i] && buf[i] != '\n')
    {
      e->username[fd][x] = buf[i];
      x = x + 1;
      i = i + 1;
    }
  e->username[fd][x] = '\0';
  i = 0;
  write_nickname_msg(e, fd, size);
  return (0);
}

int			msg(t_env *e, int fd, char *buf)
{
  int			i;
  int			size;
  int			mark;
  int			x;
  char			*name;
  char			*msg;

  size = malloc_msg_name(buf, &mark, name, fd);
  i = mark + 1;
  fill_msg_name(buf, &i, name, &mark);  
  malloc_msg(buf, i, msg);
  i = mark;
  fill_msg(buf, i, msg);
  i = 0;
  while (strcmp(e->username[i], name) && i < MAX_FD - 1)
      i = i + 1;
  if (strcmp(e->username[i], name))
    {
      write(fd, "Nickname doesn't found\n", strlen("Nickname doesn't found\n"));
      return (-1);
    }
  write_msg(e, fd, msg, i);
  return (0);
}
