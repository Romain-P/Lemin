/*
** lemin.c for lemin in /home/raphael.goulmot/rendu/CPE_2016_Lemin
** 
** Made by Raphaël Goulmot
** Login   <raphael.goulmot@epitech.net>
** 
** Started on  Thu Apr 20 20:43:48 2017 Raphaël Goulmot
** Last update Wed Apr 26 16:34:41 2017 Raphaël Goulmot
*/

#include <stdbool.h>
#include "util.h"
#include "lemin.h"

static char	possible_path(t_path *path, t_data *world, int index)
{
  t_elem        *elem;
  t_crosser	*crosser;
  int		i;
  char		check;

  elem = world->crossers->first;
  while ((check = 1) && elem && (crosser = (t_crosser *) elem->get))
    {
      elem = elem->next;
      if (!crosser->path || (crosser->step > 0
			 && crosser->path->nodes[crosser->step] == world->end))
	continue;
      i = 1;
      while (check && i < crosser->step * -1 + crosser->path->size - 1)
	{
	  if (crosser->step + i > 0 && -index + i > 0
	  && crosser->path->nodes[crosser->step + i] == path->nodes[-index + i])
	    check = 0;
	  i++;
	}
      if (!check)
	return (0);
    }
  return (1);
}

static void	init_path(t_crosser *crosser, t_data *world, int max)
{
  t_elem	*elem;
  t_path	*send;
  t_path	*current;
  int		i;
  int		min;

  min = -1;
  elem = world->paths->first;
  while (elem && (current = (t_path *)elem->get) && !(i = 0))
    {
      while (i < max && ++i)
	{
	  if ((min == -1 || min > current->size + (i - 1))
	      && possible_path(current, world, i - 1)
	      && (send = current))
	    min = current->size + (i - 1);
	 }
      elem = elem->next;
    }
  if (min && send)
    {
      crosser->path = send;
      crosser->step = -(min - send->size);
    }
}

static void	init_crossers(t_data *world, int *end_crossers)
{
  t_elem	*elem;
  t_crosser	*crosser;
  int		max;
  int		value;

  max = 1;
  elem = world->crossers->first;
  while (elem)
    {
      crosser = (t_crosser *) elem->get;
      if (!crosser->path)
	{
	  init_path(crosser, world, max);
	  if (crosser->path)
	    {
	      value = crosser->path->size + crosser->step * -1;
	      if (value > max)
		max = value;
	    }
	}
      elem = elem->next;
    }
  *end_crossers = 0;
}

void	launch_lemin(t_data *world)
{
  t_elem	*elem;
  t_crosser	*crosser;
  int		end_crossers;
  int		counter;

  init_crossers(world, &end_crossers);
  while (end_crossers != world->crossers->size && !(counter = 0))
    {
      elem = world->crossers->first;
      while (elem && (crosser = (t_crosser *)elem->get))
	{
	  if (crosser->path && (crosser->step < 0
     || crosser->path->nodes[crosser->step] != world->end) && ++crosser->step)
	    {
	      if (crosser->step > 0)
		display_format("%cP%d-%s", counter ? ' ' : '\0', crosser->id
	       , crosser->path->nodes[crosser->step]->label);
	      end_crossers += crosser->step > 0
		&& crosser->path->nodes[crosser->step] == world->end ? 1 : 0;
	      counter++;
	    }
	  elem = elem->next;
	}
      display_char('\n', false);
    }
}
