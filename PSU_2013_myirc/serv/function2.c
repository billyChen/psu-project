/*
** function2.c for function in /home/chen_c/rendu/PSU_2013_myirc/serv
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Sun Apr 27 00:35:09 2014 Billy CHEN
** Last update Sun Apr 27 21:08:04 2014 Billy CHEN
*/

#include "struct.h"
#include <string.h>

void			write_user(t_env *e, int fd, char buf[4096])
{
  int			i;

  i = 0;
  while (i < MAX_FD)
    {
      if (e->fd_type[i] == FD_CLIENT && i != fd)
	{
	  write(i, "[", 1);
	  write(i, e->username[fd], strlen(e->username[fd]));
	  write(i, "]: ", 3);
	  write(i, buf, strlen(buf));
	}
      i = i + 1;
    }
}

void			check_ptrfunc(char *cmd[2], char buf[4096], t_env *e, int fd)
{
  int			x;
  int			error;
  int			(*ptr[2])(t_env*, int, char *);

  init_ptr_func(ptr);
  x = 0;
  while (x < 2 && x != -1)
    {
      if (strncmp(cmd[x], buf, strlen(cmd[x])) == 0)
	{
	  error = ptr[x](e, fd, buf);
	  x = -2;
	}
      x = x + 1;
    }
  if (error == 0 && x != -1)
    write_user(e, fd, buf);
}
