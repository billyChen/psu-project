/*
** main.c for main in /home/chen_c/rendu/PSU_2013_myirc/client
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Sat Apr 26 15:31:21 2014 Billy CHEN
** Last update Sun Apr 27 01:16:26 2014 Billy CHEN
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int			init_client_socket(char *ip, char **av, struct protoent *pe, int *fd)
{
  int			port;

  ip = av[1];
  port = atoi(av[2]);
  pe = getprotobyname("TCP");
  if (!pe)
    return (1);
  *fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  if (*fd == -1)
    return (1);
  return (port);
}

int			init_connect(struct sockaddr_in *s_in, char *ip, int port, int fd)
{
  int			error;

  s_in->sin_family = AF_INET;
  s_in->sin_port = htons(port);
  s_in->sin_addr.s_addr = inet_addr(ip);
  error = connect(fd, (const struct sockaddr *)&s_in, sizeof(s_in));
  if (error == -1)
    {
      if (close(fd) == -1)
	return (1);
      return (1);
    }
  return (0);
}

int			main(int ac, char **av)
{
  struct protoent	*pe;
  int			fd;
  struct sockaddr_in	s_in;
  int			port;
  char			*ip;
  int			error;
  int			r;
  char			c[300];

  if (ac != 3)
    return (1);
  port = init_client_socket(ip, av, pe, &fd);
  init_connect(&s_in, ip, port, fd);
  if (close(error) == -1)
    return (1);
  if (close(fd) == -1)
    return (1);
  return (0);
}
