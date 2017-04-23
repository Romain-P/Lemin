/*
** parser.c for  in /home/romain.pillot/projects/CPE_2016_Lemin/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu Apr 20 20:06:21 2017 romain pillot
** Last update Sun Apr 23 12:46:34 2017 romain pillot
*/

#include <stdlib.h>
#include "lemin.h"
#include "util.h"

static bool	valid_data(t_data *data)
{
  if (!data->start || !data->end || !data->crossers->size)
    {
      display(!data->start ?
	      "error: undefined starting node.\n" :
	      !data->end ?
	      "error: undefined ending node.\n" :
	      "error: undefined crossers number.\n", true);
      return (false);
    }
  if (!data->start->nodes->size)
    fdisplay_format("error: starting node '%s' hasn't any link.\n",
		    data->start->label);
  else if (!data->end->nodes->size)
    fdisplay_format("error: ending node '%s' hasn't any link.\n",
		    data->end->label);
  else
    return (true);
  return (false);
}

bool	load_data(t_data *data, int fd)
{
  char	*str;
  char	node_type;

  node_type = NODE_NORMAL;
  while ((str = scan_line(fd)))
    {
      if (start_withstr(str, "#"))
	{
	  node_type = start_withstr(str, "##start") ? NODE_START :
	    start_withstr(str, "##end") ? NODE_END : NODE_NORMAL;
	  free(str);
	  continue;
	}
      if ((data->crossers->size || !build_crossers(data, str)) &&
	  !build_node(data, str, node_type) && !build_link(data, str))
	{
	  fdisplay_format("notice: '%s' stopped the parsing.\n", str);
	  free(str);
	  break;
	}
      node_type = NODE_NORMAL;
      free(str);
    }
  return (valid_data(data));
}
