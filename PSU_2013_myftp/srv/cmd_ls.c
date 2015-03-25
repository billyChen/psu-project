/*
** cmd_ls.c for MyFTP in /home/bardet_e/rendu/PSU_2013_myftp
** 
** Made by eliot bardet
** Login   <bardet_e@epitech.net>
** 
** Started on  Fri Apr 11 09:49:16 2014 eliot bardet
** Last update Sun Apr 13 22:34:11 2014 Billy CHEN
*/

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include "server.h"
#include "functions.h"

int		cmd_ls(t_session *session)
{
  struct dirent	*entry;
  DIR		*stream;
  char		*result;

  result = NULL;
  if ((stream = opendir("./srv/")) == NULL)
    {
      send_message(session->fd, "Could not list directory.");
      return (0);
    }
  while ((entry = readdir(stream)) != NULL)
    result = atatch_string(result, entry->d_name, ' ');
  if (result == NULL)
    {
      perror("malloc");
      return (0);
    }
  send_message(session->fd, result); 
  free(result);
  closedir(stream);
  return (0);
}
