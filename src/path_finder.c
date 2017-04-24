/*
** path.c for  in /home/romain.pillot/projects/CPE_2016_Lemin/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Fri Apr 21 13:02:17 2017 romain pillot
** Last update Mon Apr 24 12:57:53 2017 romain pillot
*/

#include <stdlib.h>
#include "lemin.h"
#include "util.h"

static bool	add_node(t_path *path, t_node *node)
{
  t_node	**nodes;
  int		i;

  if (!path || !(nodes = malloc(sizeof(t_node *) * (path->size + 1))))
    return (false);
  i = -1;
  while (++i < path->size)
    nodes[i] = path->nodes[i];
  nodes[i] = node;
  safe_free(path->nodes);
  path->nodes = nodes;
  path->size++;
  return (true);
}

static t_path	*copy_path(t_path *model)
{
  t_path	*path;
  int		i;

  if (!(path = malloc(sizeof(t_path))) ||
      !(path->nodes = malloc(sizeof(t_node *) * model->size)))
    return (NULL);
  path->size = model->size;
  i = -1;
  while (++i < path->size)
    path->nodes[i] = model->nodes[i];
  return (path);
}

static bool	valid_path(t_data *data, t_path *path, t_node *node)
{
  int		i;

  if (node->id != data->start->id &&
      node->nodes->size == 1 &&
      node->id != data->end->id)
    return (false);
  i = -1;
  while (++i < path->size)
    if (path->nodes[i]->id == node->id)
      return (false);
  return (true);
}

static bool	find_paths(t_data *data, t_node *node, t_path *path)
{
  t_path	*cpy;
  t_elem	*elem;

  if (!valid_path(data, path, node) ||
      !add_node((cpy = copy_path(path)), node))
    return (false);
  if (node->id == data->end->id)
    return (list_add(data->paths, cpy));
  elem = node->nodes->first;
  while (elem)
    {
      node->used = find_paths(data, (t_node *) elem->get, cpy) ? true :
	node->used;
      elem = elem->next;
    }
  free(cpy->nodes);
  free(cpy);
  return (node->used);
}

bool		build_paths(t_data *data)
{
  t_path        *path;

  path = malloc(sizeof(t_path));
  path->nodes = NULL;
  path->size = 0;
  find_paths(data, data->start, path);
  free(path->nodes);
  free(path);
  if (!data->paths->size)
    display("error: no valid path found.\n", true);
  return (data->paths->size);
}
