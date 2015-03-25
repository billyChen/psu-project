/*
** struct.h for struct in /home/chen_c/rendu/PSU_2013_myirc/serv
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Thu Apr 24 20:52:40 2014 Billy CHEN
** Last update Fri Apr 25 16:00:28 2014 Billy CHEN
*/

#ifndef		STRUCT_H
# define	STRUCT_H

#define	       	FD_FREE 0
#define		FD_CLIENT 1
#define	       	FD_SERVER 2
#define		MAX_FD 255
#define		NBR_FUNC 9


typedef	       	void(*fct)();

typedef	       	struct s_env
{
  char 		fd_type[MAX_FD];
  fct  		fct_read[MAX_FD];
  char		*username[MAX_FD];
  int  		port;
}      		t_env;

typedef	       	struct s_ptr
{
  int 		(*ptr)(t_env*);
  char 		*str;
}      		t_ptr;

#endif /* !STRUCT_H */
