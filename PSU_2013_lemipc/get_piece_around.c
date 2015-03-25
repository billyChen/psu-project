/*
** get_piece_aroung.c for get_piece_around in /home/chen_c/rendu/PSU_2013_lemipc
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Sat Mar 29 22:23:40 2014 Billy CHEN
** Last update Sun Mar 30 13:33:26 2014 Billy CHEN
*/

#include "struct.h"

int		get_left_right_piece(t_pion *p, char ally, char *ptr_plateau)
{
  if (p->target.totalXY % 10 == 0)
    {
      if (ptr_plateau[p->target.totalXY - 10] == ally)
	{
	  if (ptr_plateau[p->target.totalXY + 10] == '.')
	    {
	      p->target.totalXY = p->target.totalXY + 10;
	      p->target.x = 0;
	      p->target.y = (p->target.totalXY + 10) / 10;
	    }
	  else if (ptr_plateau[p->target.totalXY + 1] == '.')
	    {
	      p->target.totalXY = p->target.totalXY + 1;
	      p->target.x = 1;
	      p->target.y = (p->target.totalXY) / 10;
	    }
	  else
	    return (-1);
	}
      else if (ptr_plateau[p->target.totalXY + 10] == ally)
	{
	  if (ptr_plateau[p->target.totalXY - 10] == '.')
	    {
	      p->target.totalXY = p->target.totalXY - 10;
	      p->target.x = 0;
	      p->target.y = (p->target.totalXY - 10) / 10;
	    }
	  else if (ptr_plateau[p->target.totalXY + 1] == '.')
	    {
	      p->target.totalXY = p->target.totalXY + 1;
	      p->target.x = 1;
	      p->target.y = (p->target.totalXY) / 10;
	    }
	  else
	    return (-1);
	}
      else
	{
	  if (ptr_plateau[p->target.totalXY - 10] == '.')
	    {
	      p->target.totalXY = p->target.totalXY - 10;
	      p->target.x = 0;
	      p->target.y = (p->target.totalXY - 10) / 10;
	    }
	  else if (ptr_plateau[p->target.totalXY + 10] == '.')
	    {
	      p->target.totalXY = p->target.totalXY + 10;
	      p->target.x = 0;
	      p->target.y = (p->target.totalXY + 10) / 10;
	    }
	  else
	    {
	      if (ptr_plateau[p->target.totalXY + 1] == '.')
		{
		  p->target.totalXY = p->target.totalXY + 1;
		  p->target.x = 1;
		  p->target.y = (p->target.totalXY + 1) / 10;
		}
	      else
		return (-1);
	    }
	}
    }
  else
    {
      if (ptr_plateau[p->target.totalXY - 10] == ally)
	{
	  if (ptr_plateau[p->target.totalXY + 10] == '.')
	    {
	      p->target.totalXY = p->target.totalXY + 10;
	      p->target.x = 9;
	      p->target.y = (p->target.totalXY + 10) / 10;
	    }
	  else if (ptr_plateau[p->target.totalXY - 1] == '.')
	    {
	      p->target.totalXY = p->target.totalXY - 1;
	      p->target.x = 8;
	      p->target.y = (p->target.totalXY) / 10;
	    }
	}
      else if (ptr_plateau[p->target.totalXY + 10] == ally)
	{
	  if (ptr_plateau[p->target.totalXY - 10] == '.')
	    {
	      p->target.totalXY = p->target.totalXY - 10;
	      p->target.x = 9;
	      p->target.y = (p->target.totalXY - 10) / 10;
	    }
	  else if (ptr_plateau[p->target.totalXY - 1] == '.')
	    {
	      p->target.totalXY = p->target.totalXY - 1;
	      p->target.x = 8;
	      p->target.y = (p->target.totalXY) / 10;
	    }
	}
      else
	{
	  if (ptr_plateau[p->target.totalXY - 10] == '.')
	    {
	      p->target.totalXY = p->target.totalXY - 10;
	      p->target.x = 9;
	      p->target.y = (p->target.totalXY - 10) / 10;
	    }
	  else if (ptr_plateau[p->target.totalXY + 10] == '.')
	    {
	      p->target.totalXY = p->target.totalXY + 10;
	      p->target.x = 9;
	      p->target.y = (p->target.totalXY + 10) / 10;
	    }
	  else
	    {
	      if (ptr_plateau[p->target.totalXY - 1] == '.')
		{
		  p->target.totalXY = p->target.totalXY - 1;
		  p->target.x = 8;
		  p->target.y = (p->target.totalXY - 1) / 10;
		}
	      else
		return (-1);
	    }
	}
    }
  return (0);
}

int		get_top_bottom_piece(t_pion *p, char *ptr_plateau, char ally)
{
  if (p->target.totalXY >= 1 && p->target.totalXY <= 8)
    {
      if (ptr_plateau[p->target.totalXY - 1] == ally)
	{
	  if (ptr_plateau[p->target.totalXY + 1] == '.')
	    {
	      p->target.totalXY = p->target.totalXY + 1;
	      p->target.x = p->target.totalXY + 1;
	      p->target.y = (p->target.totalXY) / 10;
	    }
	  else if (ptr_plateau[p->target.totalXY + 10] == '.')
	    {
	      p->target.totalXY = p->target.totalXY + 10;
	      p->target.x = p->target.totalXY % 10;
	      p->target.y = (p->target.totalXY) / 10;
	    }
	  else
	    return (-1);
	}
      else if (ptr_plateau[p->target.totalXY + 1] == ally)
	{
	  if (ptr_plateau[p->target.totalXY - 1] == '.')
	    {
	      p->target.totalXY = p->target.totalXY - 1;
	      p->target.x = p->target.totalXY - 1;
	      p->target.y = (p->target.totalXY) / 10;
	    }
	  else if (ptr_plateau[p->target.totalXY + 10] == '.')
	    {
	      p->target.totalXY = p->target.totalXY + 10;
	      p->target.x = p->target.totalXY % 10;
	      p->target.y = (p->target.totalXY) / 10;
	    }
	  else
	    return (-1);
	}
      else
	{
	  if (ptr_plateau[p->target.totalXY - 1] == '.')
	    {
	      p->target.totalXY = p->target.totalXY - 1;
	      p->target.x = p->target.totalXY - 1;
	      p->target.y = (p->target.totalXY - 10) / 10;
	    }
	  else if (ptr_plateau[p->target.totalXY + 10] == '.')
	    {
	      p->target.totalXY = p->target.totalXY + 10;
	      p->target.x = p->target.totalXY % 10;
	      p->target.y = (p->target.totalXY + 10) / 10;
	    }
	  else
	    {
	      if (ptr_plateau[p->target.totalXY + 1] == '.')
		{
		  p->target.totalXY = p->target.totalXY + 1;
		  p->target.x = p->target.totalXY % 10;
		  p->target.y = (p->target.totalXY + 1) / 10;
		}
	      else
		return (-1);
	    }
	}
    }
  else
    {
      if (ptr_plateau[p->target.totalXY - 1] == ally)
	{
	  if (ptr_plateau[p->target.totalXY + 1] == '.')
	    {
	      p->target.totalXY = p->target.totalXY + 1;
	      p->target.x = p->target.totalXY + 1;
	      p->target.y = (p->target.totalXY) / 10;
	    }
	  else if (ptr_plateau[p->target.totalXY - 10] == '.')
	    {
	      p->target.totalXY = p->target.totalXY - 10;
	      p->target.x = p->target.totalXY % 10;
	      p->target.y = (p->target.totalXY) / 10;
	    }
	}
      else if (ptr_plateau[p->target.totalXY + 1] == ally)
	{
	  if (ptr_plateau[p->target.totalXY - 1] == '.')
	    {
	      p->target.totalXY = p->target.totalXY - 1;
	      p->target.x = p->target.totalXY - 1;
	      p->target.y = (p->target.totalXY) / 10;
	    }
	  else if (ptr_plateau[p->target.totalXY - 10] == '.')
	    {
	      p->target.totalXY = p->target.totalXY - 10;
	      p->target.x = p->target.totalXY % 10;
	      p->target.y = (p->target.totalXY) / 10;
	    }
	}
      else
	{
	  if (ptr_plateau[p->target.totalXY - 1] == '.')
	    {
	      p->target.totalXY = p->target.totalXY - 1;
	      p->target.x = p->target.totalXY - 1;
	      p->target.y = (p->target.totalXY - 10) / 10;
	    }
	  else if (ptr_plateau[p->target.totalXY - 10] == '.')
	    {
	      p->target.totalXY = p->target.totalXY - 10;
	      p->target.x = p->target.totalXY % 10;
	      p->target.y = (p->target.totalXY + 10) / 10;
	    }
	  else
	    {
	      if (ptr_plateau[p->target.totalXY + 1] == '.')
		{
		  p->target.totalXY = p->target.totalXY + 1;
		  p->target.x = p->target.totalXY % 10;
		  p->target.y = (p->target.totalXY + 1) / 10;
		}
	      else
		return (-1);
	    }
	}
    }
  return (0);
}

int		get_middle_piece(t_pion *p, char *ptr_plateau, char ally)
{
  if (ptr_plateau[p->target.totalXY + 1] == '.')
    {
      p->target.totalXY = p->target.totalXY + 1;
      p->target.x = p->target.totalXY % 10;
      p->target.y = (p->target.totalXY + 1) / 10;
    }
  else if (ptr_plateau[p->target.totalXY - 1] == '.')
    {
      p->target.totalXY = p->target.totalXY - 1;
      p->target.x = p->target.totalXY % 10;
      p->target.y = (p->target.totalXY - 1) / 10;
    }
  else
    {
      if (ptr_plateau[p->target.totalXY + 10] == '.')
	{
	  p->target.totalXY = p->target.totalXY + 10;
	  p->target.x = p->target.totalXY % 10;
	  p->target.y = (p->target.totalXY + 10) / 10;
	}
      else if (ptr_plateau[p->target.totalXY - 10] == '.')
	{
	  p->target.totalXY = p->target.totalXY - 10;
	  p->target.x = p->target.totalXY % 10;
	  p->target.y = (p->target.totalXY - 10) / 10;
	}
      else
	return (-1);
    }
  return (0);
}

int		get_piece_around(char *ptr_plateau, t_pion *p, char ally)
{
  int		return_value;

  if (p->target.totalXY == 0 || p->target.totalXY == 9
      || p->target.totalXY == 90 || p->target.totalXY == 99)
    return_value = get_corner_piece(p, ptr_plateau);
  else if (p->target.totalXY % 10 == 0 || p->target.totalXY % 10 == 9)
    return_value = get_left_right_piece(p, ally, ptr_plateau);
  else
    {
      if (p->target.totalXY >= 1 && p->target.totalXY <= 8 ||
	  p->target.totalXY >= 91 && p->target.totalXY <= 98)
	return_value = get_top_bottom_piece(p, ptr_plateau, ally);
      else
	return_value = get_middle_piece(p, ptr_plateau, ally);
    }
  return (return_value);
}
