/*
** parser.c for  in /home/romain.pillot/projects/CPE_2016_Lemin/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu Apr 20 20:06:21 2017 romain pillot
** Last update Fri Apr 21 02:48:19 2017 romain pillot
*/

#include "lemin.h"
#include "util.h"
#include <stdlib.h>

static bool	(* const states[])(t_data *data, char *str, t_state *state) =
{
  &state_crossers,
  &state_start,
  &state_nodes,
  &state_end,
  &state_links
};

static t_bool	ignore_line(t_data *data, char *str, t_state *state)
{
  if (start_withstr(str, "##start"))
    {
      if (*state == CROSSERS_NUMBER)
	fdisplay_format("%s: error (expected a crosser number first)\n", str);
      else if (data->start)
	fdisplay_format("%s: ignored (starting node already defined)\n", str);
      else
	*state = START_NODE;
      return (*state == CROSSERS_NUMBER ? ERROR : TRUE);
    }
  else if (start_withstr(str, "##end"))
    {
      if (*state == CROSSERS_NUMBER)
	fdisplay_format("%s: error (expected a crosser number first)\n", str);
      else if (data->end)
	fdisplay_format("%s: ignored (ending node already defined)\n", str);
      else
	*state = END_NODE;
      return (*state == CROSSERS_NUMBER ? ERROR : TRUE);
    }
  else if (start_withstr(str, "#"))
    return (TRUE);
  return (FALSE);
}

static void	show_warnings(t_data *data)
{
  t_elem	*elem;

  elem = data->nodes->first;
  while (elem)
    {
      if (!((t_node *) elem->get)->nodes->size)
	fdisplay_format("warning: node '%s' has not any link.\n",
			((t_node *) elem->get)->label);
      elem = elem->next;
    }
}

bool		load_data(t_data *data, int fd)
{
  char		*str;
  t_state	state;
  bool		valid;
  t_bool	ignore;

  state = CROSSERS_NUMBER;
  while ((str = scan_line(fd)))
    {
      if ((ignore = ignore_line(data, str, &state)) == FALSE)
	valid = states[state](data, str, &state);
      free(str);
      if (ignore == ERROR || !valid)
	return (false);
    }
  if (!data->start || !data->end || state != LINKS)
    {
      fdisplay_format(!data->start ?
		      "error: undefined starting node.\n" :
		      !data->end ?
		      "error: undefined ending node.\n" :
		      "error: expected valid input data");
      return (false);
    }
  show_warnings(data);
  return (true);
}
