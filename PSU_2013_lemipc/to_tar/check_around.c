/*
** check_around.c for check_around in /home/chen_c/rendu/PSU_2013_lemipc/to_tar
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Sun Mar 30 18:33:41 2014 Billy CHEN
** Last update Sun Mar 30 20:18:02 2014 Billy CHEN
*/

int		check_left(int seat, char *ptr_plateau)
{
  if (seat % 10 == 0)
    return (0);
  if (ptr_plateau[seat - 1] != '.')
    {
      if (seat % 10 >= 2)
	{
	  if (ptr_plateau[seat - 2] != '.')
	    return (2);
	}
      return (1);
    }
  else
    return (0);
}

int		check_right(int seat, char *ptr_plateau)
{
  if (seat % 10 == 9)
    return (0);
  if (ptr_plateau[seat + 1] != '.')
    {
      if (seat % 10 <= 7)
	{
	  if (ptr_plateau[seat + 2] != '.')
	    return (2);
	}
      return (1);
    }
  else
    return (0);
}

int		check_top(int seat, char *ptr_plateau)
{
  if (seat > 9)
    return (0);
  if (ptr_plateau[seat - 10] != '.')
    {
      if (seat >= 20)
	{
	  if (ptr_plateau[seat - 20] != '.')
	    return (2);
	}
      return (1);
    }
  else
    return (0);
}

int		check_bottom(int seat, char *ptr_plateau)
{
  if (seat > 89)
    return (0);
  if (ptr_plateau[seat + 10] != '.')
    {
      if (seat <= 70)
	{
	  if (ptr_plateau[seat - 2] != '.')
	    return (2);
	}
      return (1);
    }
  else
    return (0);
}

int		check_around(int seat, char *ptr_plateau)
{
  int		count;

  count = 0;
  if (seat == -1)
    return (-1);
  count += check_left(seat, ptr_plateau);
  count += check_right(seat, ptr_plateau);
  count += check_top(seat, ptr_plateau);
  count += check_bottom(seat, ptr_plateau);
  if (count > 1)
    return (-1);
  else
    return (0);
}
