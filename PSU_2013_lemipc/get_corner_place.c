/*
** get_corner_place.c for get_corner_place in /home/chen_c/rendu/PSU_2013_lemipc
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Sun Mar 30 01:17:57 2014 Billy CHEN
** Last update Sun Mar 30 13:32:12 2014 Billy CHEN
*/

#include "struct.h"

int             get_corner_piece(t_pion *p, char *ptr_plateau)
{
  if (p->target.totalXY == 0)
    {
      if (ptr_plateau[p->target.totalXY + 1] == '.')
        {
          p->target.totalXY = 1;
          p->target.x = 1;
          p->target.y = 0;
        }
      else if (ptr_plateau[p->target.totalXY + 10] == '.')
        {
          p->target.totalXY = 10;
          p->target.x = 0;
          p->target.y = 1;
        }
      else
        return (-1);
    }
  else if (p->target.totalXY == 9)
    {
      if (ptr_plateau[p->target.totalXY - 1] == '.')
        {
          p->target.totalXY = p->target.totalXY - 1;
          p->target.x = 8;
          p->target.y = 0;
        }
      else if (ptr_plateau[p->target.totalXY + 10] == '.')
        {
          p->target.totalXY = 19;
          p->target.x = 9;
          p->target.y = 1;
        }
      else
        return (-1);
    }
  else
    {
      if (p->target.totalXY == 90)
        {
          if (ptr_plateau[p->target.totalXY - 10] == '.')
            {
              p->target.totalXY = 80;
              p->target.x = 0;
              p->target.y = 8;
            }
          else if (ptr_plateau[p->target.totalXY + 1] == '.')
            {
              p->target.totalXY = 91;
              p->target.x = 1;
              p->target.y = 9;
            }
          else
            return (-1);
        }
      else
        {
          if (ptr_plateau[p->target.totalXY - 1] == '.')
            {
              p->target.totalXY = 98;
              p->target.x = 8;
              p->target.y = 9;
            }
          else if (ptr_plateau[p->target.totalXY - 10] == '.')
            {
              p->target.totalXY = 89;
              p->target.x = 9;
              p->target.y = 8;
            }
          else
            return (-1);
        }
    }
  return (0);
}
