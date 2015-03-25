/*
** server.c for MyFTP in /home/bardet_e/rendu/PSU_2013_myftp
** 
** Made by eliot bardet
** Login   <bardet_e@epitech.net>
** 
** Started on  Wed Apr  9 09:48:20 2014 eliot bardet
** Last update Fri Apr 11 13:25:17 2014 eliot bardet
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "server.h"
#include "functions.h"

int		init_server(t_server *s)
{
  printf("\nInitializing server...\n");
  if ((s->pe = getprotobyname("TCP")) == NULL)
    {
      perror("getprotobyname");
      return (0);
    }
  if ((s->sockfd = socket(AF_INET, SOCK_STREAM, s->pe->p_proto)) == -1)
    {
      perror("socket");
      return (0);
    }
  s->sin.sin_family = AF_INET;
  s->sin.sin_port = htons(s->port);
  s->sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(s->sockfd, (const struct sockaddr *)&(s->sin), sizeof(s->sin)) == -1)
    {
      perror("bind");
      return (0);
    }
  if (listen(s->sockfd, MAX_QUEUE) == -1)
    {
      perror("listen");
      return (0);
    }
  return (1);
}

char	       	*get_message(int clientfd)
{
  char 		buffer[MAX_READ_SIZE + 1];
  int  		len;
  char 		*msg;
  
  if ((len = read(clientfd, buffer, MAX_READ_SIZE)) == -1)
    {
      perror("read");
      return (NULL);
    }
  if (len == 0)
    return (NULL);
  buffer[len] = '\0';
  if ((msg = strndup(buffer, strlen(buffer))) == NULL)
    perror("strndup");
  return (msg);
}

t_session	*new_session(int clientfd)
{
  t_session	*new;

  if ((new = malloc(sizeof(*new))) == NULL)
    {
      perror("malloc");
      return (NULL);
    }
  new->fd = clientfd;
  if ((new->wdir = strdup("./srv/")) == NULL)
    {
      perror("malloc");
      return (NULL);
    }
  return (new);
}

void		handle_client(int clientfd)
{
  int	       	cont;
  char	       	*msg;
  t_session	*session;

  cont = 1;
  msg = NULL;
  if ((session = new_session(clientfd)) == NULL)
    return ;
  if (send_message(clientfd, "Welcome !\n") == -1)
    cont = 0;
  while (cont)
    {
      if (msg != NULL)
	free(msg);
      if ((msg = get_message(clientfd)) == NULL)
	cont = 0;
      else
	if (run_command(session, msg) == -1)
	  cont = 0;
    }
  if (msg != NULL)
    free(msg);
}

void			launch_server(t_server *s)
{
  int			clientfd;
  int			client_len;
  struct sockaddr_in	sin_client;
  pid_t			pid;

  printf("Server launched.\n\n");
  while (42)
    {
      if ((clientfd = accept(s->sockfd, (struct sockaddr *)&sin_client,
			     (socklen_t *)&client_len)) == -1)
	perror("Connection failure.");
      else
	{
	  
	  pid = fork();
	  if (pid == 0)
	    {
	      printf("[+] Connection opened on socket : %d\n", clientfd);
	      handle_client(clientfd);
	      close(clientfd);
	      printf("[-] Connection closed on socket : %d\n", clientfd);
	      return ;
	    }
	}
    }
}
