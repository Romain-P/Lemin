/*
** parser_state.c for Project-Master in /home/romain/projects/CPE_2016_Lemin/src
** 
** Made by romain pillot
** Login   <romain pillot@epitech.eu>
** 
** Started on  Fri Apr 21 00:35:40 2017 romain pillot
** Last update Fri Apr 21 02:51:06 2017 romain pillot
*/

#include "lemin.h"
#include <stdlib.h>
#include "util.h"

bool		state_crossers(t_data *data, char *str, t_state *state)
{
  int		crossers;
  t_crosser	*crosser;
  int		id;

  if ((crossers = getnbr(str)) <= 0)
    {
      fdisplay_format("%s: ignored (expected crossers number > 0)\n", str);
      return (true);
    }
  id = 0;
  while (crossers--)
    {
      crosser = malloc(sizeof(t_crosser));
      crosser->id = ++id;
      crosser->path = NULL;
      crosser->step = 0;
      list_add(data->crossers, crosser);
    }
  *state = NODES;
  return (true);
}

bool	state_start(t_data *data, char *str, t_state *state)
{
  
  return (true);
}

bool	state_nodes(t_data *data, char *str, t_state *state)
{

  return (true);
}

bool	state_end(t_data *data, char *str, t_state *state)
{

  return (true);
}

bool	state_links(t_data *data, char *str, t_state *state)
{
  
  return (true);
}
