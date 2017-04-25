/*
** gui.c for  in /home/romain.pillot/projects/CPE_2016_Lemin/bonus/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Mon Apr 24 18:11:34 2017 romain pillot
** Last update Tue Apr 25 15:11:05 2017 romain pillot
*/

#include <stdbool.h>
#include "lemin.h"

static bool	sort_link(t_link *link)
{
  t_node	*swap;

  if (link->node_a->posx < link->node_b->posx)
    return (true);
  swap = link->node_a;
  link->node_a = link->node_b;
  link->node_b = swap;
  return (true);
}

static void	display_links(t_data *data)
{
  t_elem	*elem;
  t_link	*link;
  int		i;

  elem = data->links->first;
  while (elem && sort_link((link = (t_link *) elem->get)))
    {
      i = 0;
      while (++i <= (link->node_b->posx - link->node_a->posx))
	mvprintw(Y - link->node_a->posy, X + link->node_a->posx + i, ".");
      
      elem = elem->next;
    }
}

static void	display_nodes(t_data *data)
{
  t_elem	*elem;
  t_node	*node;

  elem = data->nodes->first;
  while (elem)
    {
      node = (t_node *) elem->get;
      mvprintw(Y - node->posy, X + node->posx, node->label);
      elem = elem->next;
    }
}

void		display_gui(t_data *data)
{
  initscr();
  curs_set(0);
  while (true)
    {
      display_nodes(data);
      display_links(data);
      refresh();
    }
}
