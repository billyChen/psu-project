/*
** client.c for MyFTP in /home/bardet_e/rendu/PSU_2013_myftp
** 
** Made by eliot bardet
** Login   <bardet_e@epitech.net>
** 
** Started on  Wed Apr  9 16:33:43 2014 eliot bardet
** Last update Sun Apr 13 22:36:43 2014 Billy CHEN
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "client.h"

int		init_client(t_client *cl)
{
  if ((cl->pe = getprotobyname("TCP")) == NULL)
    {
      perror("getprotobyname");
      return (0);
    }
  if ((cl->sockfd = socket(AF_INET, SOCK_STREAM, cl->pe->p_proto)) == -1)
    {
      perror("socket");
      return (0);
    }
  cl->sin.sin_family = AF_INET;
  cl->sin.sin_port = htons(cl->port);
  cl->sin.sin_addr.s_addr = inet_addr(cl->addr);
  if (connect(cl->sockfd, (const struct sockaddr *)&(cl->sin), sizeof(cl->sin)) == -1)
    {
      perror("connect");
      return (0);
    }
  return (1);
}

char		*get_user_input()
{
  char		buffer[MAX_READ_SIZE + 1];
  int		len;
  char		*input;

  printf("$> ");
  fflush(stdout);
  if ((len = read(0, buffer, MAX_READ_SIZE)) == -1)
    {
      perror("read");
      return (NULL);
    }
  if (len == 0 || strncmp(buffer, "\n", 1) == 0 ||
      strncmp(buffer, " ", 1) == 0)
    {
      if ((input = strdup("Unknown")) == NULL)
	perror("strdup");
    }
  else
    {
      buffer[len - 1] = '\0';
      if ((input = strndup(buffer, strlen(buffer))) == NULL)
	perror("strndup");
    }
  return (input);
}

int		read_socket(int	sockfd)
{
  char		buffer[MAX_READ_SIZE + 1];
  int		len;

  if ((len = read(sockfd, buffer, MAX_READ_SIZE)) == -1)
    {
      perror("read");
      return (-1);
    }
  if (len == 0)
    {
      printf("Distant connection closed.\n");
      return (-1);
    }
  buffer[len] = '\0';
  printf("Server : %s\n", buffer);
  return (0);
}

void		launch(t_client *cl)
{
  int		cont;
  char		*cmd;

  cont = 1;
  cmd = NULL;
  if (read_socket(cl->sockfd) == -1)
    cont = 0;
  while (cont)
    {
      if ((cmd = get_user_input()) == NULL)
	cont = 0;
      if (cont)
	{
	  if (run_command(cl->sockfd, cmd) == -1)
	    cont = 0;
	}
      if (cont)
	{
	  if (read_socket(cl->sockfd) == -1)
	    cont = 0;
	}
      if (cmd != NULL)
	free(cmd);
    }
}
