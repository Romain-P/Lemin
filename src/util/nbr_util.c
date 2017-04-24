/*
** my_getnbr.c for my_getnbr in /home/romain.pillot/projects/CPool_Day04
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Fri Oct  7 21:03:32 2016 romain pillot
** Last update Mon Apr 24 20:29:40 2017 Raphaël Goulmot
*/

#include <stdbool.h>
#include "util.h"

static bool	is_digit(char c)
{
  return (c >= '0' && c <= '9');
}

static int     my_getnbr_sub(char *str, int i, int n, int s)
{
  if ((str[i] == '-' || str[i] == '+') && (i == 0 || !is_digit(str[i - 1])))
    return (my_getnbr_sub(str, i + 1, n, str[i] == '-' ? s * - 1 : s));
  else if (is_digit(str[i]))
    if ((((long)n * 10) + (str[i] - 48)) > 2147483647)
      return (0);
    else
      return (my_getnbr_sub(str, i + 1, (n * 10) + (str[i] - 48), s));
  else if (n == 0)
    return (-1);
  else
    return (n * s);
}

int     getnbr(char *str)
{
  if (str && *str == '0' && !(str[1]))
    return (0);
  return (my_getnbr_sub(str, 0, 0, 1));
}

void	putnbr(int nbr, bool err)
{
  if (nbr < 0)
    display_char('-', err);
  nbr = nbr < 0 ? nbr * -1 : nbr;
  if (nbr > 9)
    putnbr(nbr / 10, err);
  display_char(nbr % 10 + 48, err);
}
