/*
** lemin.c for lemin in /home/raphael.goulmot/rendu/CPE_2016_Lemin
** 
** Made by Raphaël Goulmot
** Login   <raphael.goulmot@epitech.net>
** 
** Started on  Thu Apr 20 20:43:48 2017 Raphaël Goulmot
** Last update Fri Apr 28 15:20:03 2017 Raphaël Goulmot
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
  check = 1;
  while (check && elem && (crosser = (t_crosser *) elem->get) && crosser->path)
    {
      elem = elem->next;
      if (crosser->step > 0
			 && crosser->path->nodes[crosser->step] == world->end)
	continue;
      i = 1;
      while (check && i < crosser->step * -1 + crosser->path->size - 1)
	{
	  if (crosser->step + i > 0 && -index + i > 0
	  && crosser->path->nodes[crosser->step + i] == path->nodes[-index + i])
	    check = 0;
	  i++;
	}
    }
  return (check);
}

static void	init_path(t_crosser *crosser, t_data *world, int max, int index)
{
  t_elem	*elem;
  t_path	*send;
  t_path	*current;
  int		i;
  int		min;

  min = -1;
  elem = world->paths->first;
  while (elem && (current = (t_path *)elem->get))
    {
      i = index < 0 ? 0 : index;
      while (i < max + 1 && ++i)
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
  int		size;

  max = 0;
  size = 0;
  elem = world->crossers->first;
  while (elem)
    {
      crosser = (t_crosser *) elem->get;
      if (!crosser->path)
	{
	  init_path(crosser, world, max, max - size);
	  value = crosser->path->size - crosser->step;
	  if (value > max)
	    max = value;
	  if (crosser->path->size > size)
	    size = crosser->path->size;
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
				|| crosser->path->nodes[crosser->step] != world->end)
	      && ++crosser->step && crosser->step > 0 && ++counter)
	    {
	      if (counter > 1)
		display_format(" ");
	      display_format("P%d-%s", crosser->id
			     , crosser->path->nodes[crosser->step]->label);
	      end_crossers += crosser->path->nodes[crosser->step] == world->end;
	    }
	  elem = elem->next;
	}
      display_char('\n', false);
    }
}
