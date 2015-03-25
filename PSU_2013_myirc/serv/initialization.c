/*
** initialization.c for initialization in /home/chen_c/rendu/PSU_2013_myirc/serv
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Thu Apr 24 21:03:19 2014 Billy CHEN
** Last update Sun Apr 27 21:07:00 2014 Billy CHEN
*/

#include "struct.h"
#include "prot.h"

void		fill_cmd(char *cmd[2])
{
  int		x;
  int		y;
  
  x = 0;
  y = 0;
  cmd[0] = "/nick";
  cmd[1] = "/msg";
}

void		init_ptr_func(int (*ptr[2])(t_env *, int, char *))
{
  ptr[0] = nickname;
  ptr[1] = msg;
}
