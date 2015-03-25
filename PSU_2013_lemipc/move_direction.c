/*
** move_direction.c for move_direction in /home/chen_c/rendu/PSU_2013_lemipc
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Sat Mar 29 18:04:12 2014 Billy CHEN
** Last update Sun Mar 30 15:17:58 2014 Billy CHEN
*/

#include "struct.h"

void		move_right(char *ptr_plateau, t_pion *p, char ally)
{
  if (p->target.y == p->y)
    {
      ptr_plateau[p->totalXY + 1] = ally;
      ptr_plateau[p->totalXY] = '.';
      p->totalXY += 1;
    }
  else if (p->target.y > p->y)
    {
      ptr_plateau[p->totalXY - 9] = ally;
      ptr_plateau[p->totalXY] = '.';
      p->totalXY += 1;
    }
  else
    {
      ptr_plateau[p->totalXY + 1] = ally;
      ptr_plateau[p->totalXY] = '.';
      p->totalXY += 1;
    }
}

void		move_left(char *ptr_plateau, t_pion *p)
{

}

void		move_top_bottom(char *ptr_plateau, t_pion *p)
{

}

void		move_to_target(t_pion *p, char *ptr_plateau, char ally)
{
  if (p->target.x > p->x)
    {
      move_right(ptr_plateau, p, ally);
    }
  else if (p->target.x < p->x)
    {
      move_left(ptr_plateau, p);
    }
  else
    {
      move_top_bottom(ptr_plateau, p);
    }
}
