/*
** tab_util.c for  in /home/romain.pillot/projects/PSU_2016_minishell1/src/util
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Wed Mar  8 13:58:37 2017 romain pillot
** Last update Sun Apr 23 12:50:14 2017 romain pillot
*/

#include <stdlib.h>
#include <stdbool.h>
#include "util.h"

int	tab_length(char **tab)
{
  int	i;

  i = 0;
  while (tab && tab[i] && ++i);
  return (i);
}

char	*tab_start_withstr(char **tab, char *charset)
{
  while (tab && *tab)
    if (start_withstr(*tab++, charset))
      return (*(tab - 1));
  return (NULL);
}

bool	tab_containstr(char **tab, char *str)
{
  while (tab && *tab)
    if (equalstr(*tab++, str))
      return (true);
  return (false);
}

char    **filltab(char **tab, void *e, int size)
{
  int	i;

  if (!tab)
    return (NULL);
  i = -1;
  while (++i < size)
    tab[i] = e;
  return (tab);
}
