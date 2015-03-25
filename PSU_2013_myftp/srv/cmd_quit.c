/*
** cmd_quit.c for MyFTP in /home/bardet_e/rendu/PSU_2013_myftp
** 
** Made by eliot bardet
** Login   <bardet_e@epitech.net>
** 
** Started on  Fri Apr 11 09:48:00 2014 eliot bardet
** Last update Fri Apr 11 13:24:21 2014 eliot bardet
*/

#include "server.h"

int		cmd_quit(t_session *session)
{
  send_message(session->fd, "Goodbye !");
  return (-1);
}
