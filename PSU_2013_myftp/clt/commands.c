/*
** commands.c for MyFTP in /home/bardet_e/rendu/PSU_2013_myftp
** 
** Made by eliot bardet
** Login   <bardet_e@epitech.net>
** 
** Started on  Wed Apr  9 17:29:07 2014 eliot bardet
** Last update Wed Apr  9 18:42:06 2014 eliot bardet
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "client.h"

int		send_request(int fd, char *cmd)
{
  if (write(fd, cmd, strlen(cmd)) == -1)
    {
      perror("write");
      return (-1);
    }
  return (0);
}

int		run_command(int fd, char *cmd)
{
  if (send_request(fd, cmd) == -1)
    return (-1);
  if (strncmp(cmd, "quit", 4) == 0)
    return (-1);
  return (0);
}
