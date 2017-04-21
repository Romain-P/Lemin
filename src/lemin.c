/*
** lemin.c for lemin in /home/raphael.goulmot/rendu/CPE_2016_Lemin
** 
** Made by Raphaël Goulmot
** Login   <raphael.goulmot@epitech.net>
** 
** Started on  Thu Apr 20 20:43:48 2017 Raphaël Goulmot
** Last update Fri Apr 21 12:58:06 2017 Raphaël Goulmot
*/

#include "util.h"
#include "lemin.h"
#include <stdbool.h>

static char	possible_path(t_path *path, t_data *world)
{
  t_elem        *elem;
  t_crosser	*crosser;
  int		i;
  char		check;

  elem = world->crossers->first;
  while (elem)
    {
      crosser = (t_crosser *) elem->get;
      if (!crosser->path || crosser->path->nodes[crosser->step] == world->end)
	continue;
      i = 0;
      check = 1;
      while (check && i < crosser->path->size - crosser->step - 1)
	{
	  if (path->size < i
	      && crosser->path->nodes[crosser->step + i] == path->nodes[i + 1])
	    check = 0;
	  i++;
	}
      if (check)
	return (1);
      elem = elem->next;
    }
  return (0);
}

static void	init_path(t_crosser *crosser, t_data *world)
{
  t_elem	*elem;

  elem = world->paths->first;
  while (elem)
    {
      if (possible_path((t_path *) elem->get, world))
	{
	  display_format("Ant: %d Asssign", crosser->id);
	  crosser->path = (t_path *) elem->get;
	  crosser->step = 1;
	  return;
	}
      elem = elem->next;
    }
}

static void	init_crossers(t_data *world)
{
  t_elem	*elem;

  elem = world->crossers->first;
  while (elem)
    {
      if (!((t_crosser *) elem->get))
	init_path((t_crosser *) elem->get, world);
      elem = elem->next;
    }
}

static char	end_crossers(t_data *world)
{
  t_elem        *elem;
  t_crosser	*crosser;

  elem = world->crossers->first;
  while (elem)
    {
      if (!(crosser = (t_crosser *) elem->get))
	break;
      if (!crosser->path || crosser->path->nodes[crosser->step] != world->end)
	return (0);
      elem = elem->next;
    }
  return (1);
}

void	launch_lemin(t_data *world)
{
  t_elem	*elem;
  t_crosser	*crosser;

  while (!end_crossers(world))
    {
      init_crossers(world);
      elem = world->crossers->first;
      while (elem)
	{
	  crosser = (t_crosser *) elem->get;
	  if (crosser->path && crosser->path->nodes[crosser->step] != world->end)
	    {
	      crosser->step++;
	      display_format("P%d-%s", crosser->id
			     , crosser->path->nodes[crosser->step]->label);
	    }
	  elem = elem->next;
	}
      display_char('\n', false);
    }
}
