/*
** parser.c for  in /home/romain.pillot/projects/CPE_2016_Lemin/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu Apr 20 20:06:21 2017 romain pillot
** Last update Fri Apr 21 06:03:36 2017 romain pillot
*/

#include "lemin.h"
#include "util.h"
#include <stdlib.h>

static bool	valid_data(t_data *data)
{
  t_elem	*elem;

  elem = data->nodes->first;
  while (elem)
    {
      if (!((t_node *) elem->get)->nodes->size)
	fdisplay_format("warning: node '%s' hasn't any link.\n",
			((t_node *) elem->get)->label);
      elem = elem->next;
    }
  if (!data->start || !data->end || !data->crossers)
    {
      display(!data->start ?
	      "error: undefined starting node.\n" :
	      !data->end ?
	      "error: undefined ending node.\n" :
	      "error: undefined crossers number.\n", true);
      return (false);
    }
  return (true);
}

bool	load_data(t_data *data, int fd)
{
  char	*str;
  char	node_type;
  bool	start;

  node_type = NODE_NORMAL;
  while ((str = scan_line(fd)))
    {
      if (start_withstr(str, "#"))
	{
	  if ((start = start_withstr(str, "##start")) ||
	      start_withstr(str, "##end"))
	    node_type = start ? NODE_START : NODE_END;
	  free(str);
	  continue;
	}
      if ((data->crossers->size || !build_crossers(data, str)) &&
	  !build_node(data, str, node_type) && !build_link(data, str))
	fdisplay_format("warning: '%s' unknown parsing action.\n", str);
      node_type = NODE_NORMAL;
      free(str);
    }
  return (valid_data(data));
}
