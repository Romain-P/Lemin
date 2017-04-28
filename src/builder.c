/*
** parser_state.c for Project-Master in /home/romain/projects/CPE_2016_Lemin/src
** 
** Made by romain pillot
** Login   <romain pillot@epitech.eu>
** 
** Started on  Fri Apr 21 00:35:40 2017 romain pillot
** Last update Fri Apr 28 15:45:13 2017 romain pillot
*/

#include <stdlib.h>
#include "util.h"
#include "lemin.h"

bool		build_crossers(t_data *data, char *str)
{
  int		crossers;
  char		**tab;
  t_crosser	*crosser;
  int		id;

  tab = splitstr(strdupl(str), '#');
  str = tab[0];
  if ((crossers = getnbr(str)) <= 0)
    {
      display("error: invalid number of ants.\n", true);
      safe_freesub(tab, true);
      return (false);
    }
  safe_freesub(tab, true);
  id = 0;
  while (crossers--)
    {
      if (!(crosser = malloc(sizeof(t_crosser))))
	return (false);
      crosser->id = ++id;
      crosser->path = NULL;
      crosser->step = 0;
      list_add(data->crossers, crosser);
    }
  return (true);
}

static bool	insert_node(t_data *data, char *label, int posx, int posy)
{
  t_node	*node;
  t_elem	*elem;
  bool		duplicated;

  elem = data->nodes->first;
  while (elem)
    {
      node = (t_node *) elem->get;
      if ((duplicated = equalstr(node->label, label)) ||
	  (node->posx == posx && node->posy == posy))
	{
	  fdisplay_format(duplicated ?
			  "warning: ignored a duplicate '%s'.\n" :
			  "warning: ignored '%s' (same position).\n", label);
	  return (false);
	}
      elem = elem->next;
    }
  if (!(node = malloc(sizeof(t_node))) || !(node->nodes = list_create()))
    return (false);
  node->label = label;
  node->posx = posx;
  node->posy = posy;
  list_add(data->nodes, node);
  return (!(node->used = false) && (node->id = data->nodes->size));
}

bool	build_node(t_data *data, char *str, char node_type)
{
  char	**split;
  char	**comment;
  char	*label;
  int	posx;
  int	posy;
  int	len;

  comment = splitstr(strdupl(str), '#');
  split = splitstr(comment[0], ' ');
  len = tab_length(split);
  posx = len == 3 ? getnbr(split[1]) : 0;
  posy = len == 3 ? getnbr(split[2]) : 0;
  label = len == 3 ? strdupl(split[0]) : NULL;
  safe_freesub(split, true);
  free(comment);
  if (len != 3 || !insert_node(data, label, posx, posy))
    {
      safe_free(label);
      return (false);
    }
  if (node_type == NODE_START)
    data->start = (t_node *) data->nodes->last->get;
  else if (node_type == NODE_END)
    data->end = (t_node *) data->nodes->last->get;
  return (true);
}

static t_node	*find_node(t_list *list, char *label, bool err)
{
  t_elem	*elem;

  elem = list->first;
  while (elem)
    {
      if (equalstr(label, ((t_node *) elem->get)->label))
	return ((t_node *) elem->get);
      elem = elem->next;
    }
  if (err)
    fdisplay_format("warning: node '%s' does not exist.\n", label);
  return (NULL);
}

bool		build_link(t_data *data, char *str)
{
  char		**split;
  t_node	*node_a;
  t_node	*node_b;
  int		len;
  t_link	*link;

  split = splitstr(strdupl(str), '-');
  len = tab_length(split);
  node_a = len == 2 ? find_node(data->nodes, split[0], true) : NULL;
  node_b = len == 2 ? find_node(data->nodes, split[1], true) : NULL;
  if (node_a->id != node_b->id && len == 2 && node_a && node_b)
    {
      if (!(link = malloc(sizeof(t_link))))
	return (false);
      list_add(data->links, link);
      link->node_a = node_a;
      link->node_b = node_b;
      if (find_node(node_a->nodes, node_b->label, false))
	fdisplay_format("warning: link '%s' (already built).\n", str);
      else
	{
	  list_add(node_a->nodes, node_b);
	  list_add(node_b->nodes, node_a);
	}
      len = -1;
    }
  safe_freesub(split, true);
  return (len == -1);
}
