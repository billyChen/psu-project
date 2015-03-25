/*
** server.h for MyFTP in /home/bardet_e/rendu/PSU_2013_myftp
** 
** Made by eliot bardet
** Login   <bardet_e@epitech.net>
** 
** Started on  Wed Apr  9 09:38:25 2014 eliot bardet
** Last update Sun Apr 13 16:24:33 2014 eliot bardet
*/

#ifndef _SERVER_H_
# define _SERVER_H_

# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/socket.h>

# define MAX_QUEUE	(10)
# define MAX_READ_SIZE	(255)

typedef struct		s_server
{
  int			port;
  struct protoent	*pe;
  int			sockfd;
  struct sockaddr_in	sin;
}			t_server;

typedef struct	s_session
{
  int		fd;
  char		*wdir;
}		t_session;

typedef struct	s_command
{
  char		*name;
  int		(*func)(t_session *);
}		t_command;

int		init_server(t_server *);
void		launch_server(t_server *);
char		*strndup(const char *, size_t);
int		run_command(t_session*, char *);
int		send_message(int, char *);
int		cmd_quit(t_session *);
int		cmd_ls(t_session *);
int		cmd_pwd(t_session *);

#endif /* !_SERVER_H_ */
