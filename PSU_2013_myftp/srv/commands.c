/*
** commands.c for MyFTP in /home/bardet_e/rendu/PSU_2013_myftp
** 
** Made by eliot bardet
** Login   <bardet_e@epitech.net>
** 
** Started on  Wed Apr  9 14:54:18 2014 eliot bardet
** Last update Fri Apr 11 13:23:16 2014 eliot bardet
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server.h"

int		send_message(int fd, char *msg)
{
  if (write(fd, msg, strlen(msg)) == -1)
    {
      perror("write");
      return (-1);
    }
  else
    return (0);
}

int		run_command(t_session *session, char *cmd)
{
  int		i;
  t_command	functab[] =
    {
      {"quit",	&cmd_quit},
      {"ls",	&cmd_ls},
      {NULL,	NULL}
    };

  i = 0;
  while (functab[i].name != NULL)
    {
      if (strncmp(functab[i].name, cmd, strlen(functab[i].name)) == 0)
	return (functab[i].func(session));
      i++;
    }
  send_message(session->fd, "Unknown command.");
  return (0);
}
