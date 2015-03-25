/*
** create_plateau.c for create_plateau in /home/chen_c/rendu/PSU_2013_lemipc/to_tar
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Sun Mar 30 20:11:43 2014 Billy CHEN
** Last update Sun Mar 30 20:16:56 2014 Billy CHEN
*/

#include <stdlib.h>
#include <stdio.h>

char		*create_plateau()
{
  char		*plateau;
  int		x;

  x = 0;
  plateau = malloc(101 * sizeof(*plateau));
  if (plateau == NULL)
    {
      printf("Error malloc\n");
      exit(EXIT_FAILURE);
    }
  while (x < 100)
    {
      plateau[x] = '.';
      x = x + 1;
    }
  return (plateau);
}
