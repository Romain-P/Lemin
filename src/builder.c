/*
** parser_state.c for Project-Master in /home/romain/projects/CPE_2016_Lemin/src
** 
** Made by romain pillot
** Login   <romain pillot@epitech.eu>
** 
** Started on  Fri Apr 21 00:35:40 2017 romain pillot
** Last update Fri Apr 21 08:17:43 2017 romain pillot
*/

#include "lemin.h"
#include <stdlib.h>
#include "util.h"

bool		build_crossers(t_data *data, char *str)
{
  int		crossers;
  t_crosser	*crosser;
  int		id;

  if (!start_withstr(str, "Number of ants: ") ||
      (crossers = getnbr(str + 16)) <= 0)
    return (false);
  id = 0;
  while (crossers--)
    {
      crosser = malloc(sizeof(t_crosser));
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
  node = malloc(sizeof(t_node));
  node->label = label;
  node->posx = posx;
  node->posy = posy;
  node->nodes = list_create();
  list_add(data->nodes, node);
  return (true);
}

bool	build_node(t_data *data, char *str, char node_type)
{
  char	**split;
  char	*label;
  int	posx;
  int	posy;
  int	len;

  split = splitstr(strdupl(str), ' ');
  label = NULL;
  if ((len = tab_length(split)) >= 3 &&
      (posx = getnbr(split[1])) >= 0 &&
      (posy = getnbr(split[2])) >= 0)
    label = strdupl(split[0]);
  safe_freesub(split, true);
  if (len < 3 || !label || !insert_node(data, label, posx, posy))
    {
      len = len >= 3 && label;
      safe_free(label);
      return (len);
    }
  if (node_type == NODE_START)
    data->start = (t_node *) data->nodes->last;
  else if (node_type == NODE_END)
    data->end = (t_node *) data->nodes->last;
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

  split = splitstr(strdupl(str), '-');
  if ((len = tab_length(split)) < 2 ||
      !(node_a = find_node(data->nodes, split[0], true)) ||
      !(node_b = find_node(data->nodes, split[1], true)))
    {
      safe_freesub(split, true);
      return (len >= 2);
    }
  if (find_node(node_a->nodes, node_b->label, false))
    fdisplay_format("warning: ignored link '%s' (already built).\n", str);
  else
    {
      list_add(node_a->nodes, node_b);
      list_add(node_b->nodes, node_a);
    }
  safe_freesub(split, true);
  return (true);
}
