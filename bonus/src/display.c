/*
** display.c for  in /home/romain.pillot/projects/CPE_2016_Lemin/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Fri Apr 21 07:37:25 2017 romain pillot
** Last update Fri Apr 21 12:35:36 2017 romain pillot
*/

#include "lemin.h"
#include "util.h"

static void	display_nodes(t_data *data)
{
  t_elem	*elem;
  t_node	*node;

  display("#rooms\n", false);
  elem = data->nodes->first;
  while (elem)
    {
      node = (t_node *) elem->get;
      if (equalstr(node->label, data->start->label))
	display("##start\n", false);
      else if (equalstr(node->label, data->end->label))
	display("##end\n", false);
      display_format("%s %d %d\n", node->label, node->posx, node->posy);
      elem = elem->next;
    }
}

static void	display_links(t_list *links)
{
  t_elem        *elem;

  display("#tunnels\n", false);
  elem = links->first;
  while (elem)
    {
      display_format("%s-%s\n", ((t_link *) elem->get)->node_a->label,
		     ((t_link *) elem->get)->node_b->label);
      elem = elem->next;
    }
}

void		display_data(t_data *data)
{
  display_format("#number_of_ants\n%d\n", data->crossers->size);
  display_nodes(data);
  display_links(data->links);
  display("#moves\n", false);
}
