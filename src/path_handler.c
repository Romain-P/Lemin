/*
** path_handler.c for  in /home/romain.pillot/projects/CPE_2016_Lemin/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Mon Apr 24 10:15:07 2017 romain pillot
** Last update Mon Apr 24 15:28:30 2017 romain pillot
*/

#include "lemin.h"
#include "util.h"
#include <stdlib.h>

void		sort_paths(t_data *data)
{
  t_elem	*elem;
  t_list	*sort;
  t_elem	*lower;

  sort = list_create();
  while (data->paths->size)
    {
      elem = data->paths->first;
      lower = NULL;
      while (elem)
	{
	  if (!lower || ((t_path *) lower->get)->size > ((t_path *) elem->get)->size)
	    lower = elem;
	  elem = elem->next;
	}
      list_add(sort, list_eremove(data->paths, lower));
    }
  free(data->paths);
  data->paths = sort;
}

void		display_warnings(t_data *data)
{
  t_elem	*elem;
  t_node	*node;

  elem = data->nodes->first;
  while (elem)
    {
      node = (t_node *) elem->get;
      if (node->id != data->start->id &&
	  node->id != data->end->id &&
	  !node->used)
	fdisplay_format("warning: node '%s' belongs to a circular path"
			" (useless node).\n", node->label);
      elem = elem->next;
    }
}
