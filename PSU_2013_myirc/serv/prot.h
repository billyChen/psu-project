/*
** prot.h for prot in /home/chen_c/rendu/PSU_2013_myirc/serv
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Thu Apr 24 21:47:13 2014 Billy CHEN
** Last update Sun Apr 27 21:08:40 2014 Billy CHEN
*/

#ifndef PROT_H
# define PROT_H

int			nickname(t_env *e, int fd, char *buf);	
int			msg(t_env *e, int fd, char *buf);

#endif /* !PROT_H */ 
