/*
** main.c for  in /home/romain.pillot/projects/CPE_2016_Lemin/src
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu Apr 20 17:14:37 2017 romain pillot
** Last update Fri Apr 21 12:59:09 2017 Raphaël Goulmot
*/

#include <stdlib.h>
#include "util.h"
#include "lemin.h"
#include <fcntl.h>
#include <unistd.h>

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
  data->links = list_create();
  return (data);
}

static void	free_data(t_data *data, int fd)
{
  list_removeall(data->crossers, true);
  free(data->crossers);
  list_removeall(data->links, true);
  free(data->links);
  free(data->nodes);
  free(data->paths);
  if (fd != 0)
    close(fd);
  free(data);
}

static int	free_all(t_data *data, int fd, int status)
{
  t_elem	*elem;
  t_elem	*hold;

  elem = data->nodes ? data->nodes->first : NULL;
  while ((hold = elem))
    {
      safe_free(((t_node *) elem->get)->label);
      list_removeall(((t_node *) elem->get)->nodes, false);
      safe_free(((t_node *) elem->get)->nodes);
      safe_free((t_node *) elem->get);
      elem = elem->next;
      safe_free(hold);
    }
  elem = data->paths ? data->paths->first : NULL;
  while ((hold = elem))
    {
      safe_free(((t_path *) elem->get)->nodes);
      safe_free((t_path *) elem->get);
      elem = elem->next;
      safe_free(hold);
    }
  free_data(data, fd);
  return (status);
}

/* bonus: read a file passed as argument */
static int	get_file(char **args, int *file)
{
  *file = 0;
  if (args[1] && (*file = open(args[1], O_RDONLY)) == -1)
    fdisplay_format("%s: can't open the file '%s'\n", args[0], args[1]);
  return (*file == -1 ? (*file = 0) : *file);
}

int		main(int ac, char **args)
{
  t_data	*data;
  int		fd;

  (void) ac;
  if (!(data = initialize()) ||
      !load_data(data, get_file(args, &fd)))
    return (free_all(data, fd, EXIT_FAIL));
  display_data(data);
  //launch_lemin(data);
  return (free_all(data, fd, EXIT_SUCCESS));
}
