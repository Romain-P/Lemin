/*
** path_handler.c for  in /home/romain.pillot/projects/CPE_2016_Lemin/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Mon Apr 24 10:15:07 2017 romain pillot
** Last update Mon Apr 24 13:36:15 2017 romain pillot
*/

#include "lemin.h"
#include "util.h"

void		sort_paths(t_list *paths)
{
  t_elem	*elem;
  
  elem = paths->first;
  while (elem)
    {
      
      elem = elem->next;
    }
  paths = paths;
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
