/*
** path.c for  in /home/romain.pillot/projects/CPE_2016_Lemin/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Fri Apr 21 13:02:17 2017 romain pillot
** Last update Sun Apr 23 07:45:33 2017 romain pillot
*/

static t_path	*create_path()
{
  t_path	*path;

  path = malloc(sizeof(t_path));
  path->nodes = NULL;
  path->size = 0;
  return (path);
}

static void	add_node(t_path *path, t_node *node)
{
  t_node	**nodes;
  int		i;

  nodes = malloc(sizeof(t_node) * (path->size + 1));
  i = -1;
  while (++i < path->size)
    nodes[i] = path->nodes[i];
  nodes[i] = node;
  free(path->nodes);
  path->nodes = nodes;
  path->size++;
}

bool		build_paths(t_data *data)
{
  
  return (true);
}
