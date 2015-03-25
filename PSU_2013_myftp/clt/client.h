/*
** client.h for MyFTP in /home/bardet_e/rendu/PSU_2013_myftp
** 
** Made by eliot bardet
** Login   <bardet_e@epitech.net>
** 
** Started on  Wed Apr  9 16:06:45 2014 eliot bardet
** Last update Wed Apr  9 18:44:36 2014 eliot bardet
*/

#ifndef _CLIENT_H_
# define _CLIENT_H_

# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/socket.h>

# define MAX_READ_SIZE	(255)

typedef struct		s_client
{
  char			*addr;
  int			port;
  struct protoent	*pe;
  int			sockfd;
  struct sockaddr_in	sin;
}			t_client;

int		init_client(t_client *);
void		launch_client(t_client *);
char		*strdup(const char *);
char		*strndup(const char*, size_t);
int		run_command(int, char *);
int		read_socket(int);


#endif /* !_CLIENT_H_ */
