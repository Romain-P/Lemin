/*
** gui.c for  in /home/romain.pillot/projects/CPE_2016_Lemin/bonus/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Mon Apr 24 18:11:34 2017 romain pillot
** Last update Mon Apr 24 18:50:09 2017 romain pillot
*/

#include <ncurses.h>
#include <stdbool.h>
#include "lemin.h"

void	display_gui(t_data *data)
{
  initscr();
  while (true)
    {
      mvprintw(10, 10, "hello");
      refresh();
    }
}
