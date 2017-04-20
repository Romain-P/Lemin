/*
** main.c for  in /home/romain.pillot/projects/CPE_2016_Lemin/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu Apr 20 17:14:37 2017 romain pillot
** Last update Thu Apr 20 20:20:21 2017 romain pillot
*/

#include <stdlib.h>
#include "util.h"
#include "lemin.h"

static t_data	*initialize()
{
  t_data	*data;

  if (!(data = malloc(sizeof(t_data))))
    return (NULL);
  data->start = NULL;
  data->end = NULL;
  data->nodes = list_create();
  data->crossers = list_create();
  data->paths = list_create();
  return (data);
}

static void	free_data(t_data *data)
{
  t_elem	*elem;
  t_elem	*hold;
  t_node	*node;

  elem = data->nodes->first;
  while (elem)
    {
      safe_free(((t_node *) elem->get)->name);
      safe_free(((t_node *) elem->get)->nodes);
      safe_free((t_node *) elem->get);
      hold = elem;
      elem = elem->next;
      free(hold);
    }
  list_removeall(data->crossers, true);
  elem = data->paths->first;
  while (elem)
    {
      free(((t_path *) elem->get)->nodes);
      free((t_path *) elem->get);
      hold = elem;
      elem = elem->next;
      free(hold);
    }
}

int		main()
{
  t_data	*data;

  if (!(data = initialize()))
    return (84);
  
  free_data(data);
  return (0);
}
