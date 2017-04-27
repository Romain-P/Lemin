/*
** display.c for  in /home/romain.pillot/projects/CPE_2016_Lemin/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Fri Apr 21 07:37:25 2017 romain pillot
** Last update Thu Apr 27 15:52:47 2017 romain pillot
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
      if (data->start && node->id == data->start->id)
	display("##start\n", false);
      else if (data->end && node->id == data->end->id)
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

void		display_data(t_data *data, bool works)
{
  bool		error;

  if (!(error = !data->crossers->size))
    display_format("#number_of_ants\n%d\n", data->crossers->size);
  if (!error && !(error = !data->nodes->size))
    display_nodes(data);
  if (!error && !(error = !data->links->size))
    display_links(data->links);
  if (works)
    display("#moves\n", false);
}
