/*
** parser.c for  in /home/romain.pillot/projects/CPE_2016_Lemin/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu Apr 20 20:06:21 2017 romain pillot
** Last update Fri Apr 28 16:17:46 2017 romain pillot
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
  return (true);
}

static bool	already_defined(t_data *data, char node_type)
{
  bool		start;

  if ((start = data->start && node_type == NODE_START) ||
      (data->end && node_type == NODE_END))
    {
      fdisplay_format("error: %s node already defined.\n",
		      start ? "starting" : "ending");
      return (true);
    }
  return (false);
}

bool	load_data(t_data *data, int fd)
{
  char	*str;
  char	node_type;

  node_type = NODE_NORMAL;
  while ((str = scan_line(fd)) != NULL && *str)
    {
      if (start_withstr(str, "#"))
	{
	  node_type = equalstr(trimstr(str, ' '), "##start") ? NODE_START :
	    equalstr(trimstr(str, ' '), "##end") ? NODE_END : NODE_NORMAL;
	  free(str);
	  continue;
	}
      if (already_defined(data, node_type) ||
	  ((data->crossers->size || !build_crossers(data, str)) &&
	   (!build_node(data, str, node_type) && !build_link(data, str))))
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
