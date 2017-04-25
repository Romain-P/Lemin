/*
** gui.c for  in /home/romain.pillot/projects/CPE_2016_Lemin/bonus/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Mon Apr 24 18:11:34 2017 romain pillot
** Last update Mon Apr 24 19:25:09 2017 romain pillot
*/

#include <stdbool.h>
#include "lemin.h"

static void	display_nodes(t_data *data)
{
  
}

void		display_gui(t_data *data)
{
  initscr();
  curs_set(0);
  while (true)
    {
      display_nodes(data);
      refresh();
    }
}
