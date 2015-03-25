/*
** attach_string.c for attach_string in /home/chen_c/rendu/PSU_2013_myftp
** 
** Made by Billy CHEN
** Login   <chen_c@epitech.net>
** 
** Started on  Sun Apr 13 22:12:37 2014 Billy CHEN
** Last update Sun Apr 13 22:37:50 2014 Billy CHEN
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char		*attach_string(char *str1, char *str2, char delim)
{
  char		*str;
  int		count;

  str = NULL;
  if (str1 == NULL)
    return (strdup(str2));
  else
    {
      str = malloc(sizeof(*str) * (strlen(str1) + strlen(str2) + 2));
      if (str == NULL)
	return (NULL);
      str = memset(str, 0, strlen(str1) + strlen(str2) + 2);
      str = strcat(str, str1);
      count = strlen(str);
      str[count] = delim;
      str[count + 1] = '\0';
      str = strcat(str, str2);
      free(str1);
      return (str);
    }
}
