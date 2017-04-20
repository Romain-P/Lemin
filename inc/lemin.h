/*
** lemin.h for  in /home/romain.pillot/projects/CPE_2016_Lemin/inc
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu Apr 20 17:46:54 2017 romain pillot
** Last update Thu Apr 20 21:07:49 2017 romain pillot
*/

#ifndef LEMIN_H_
# define LEMIN_H_

# define EXIT_FAIL	(84)

# include "list.h"
# include <stdbool.h>

typedef struct  s_node
{
  char          *name;
  int           posx;
  int           posy;
  t_list        *nodes;
}               t_node;

typedef struct	s_path
{
  t_node	**nodes;
  int		size;
}		t_path;

typedef struct	s_crosser
{
  int		id;
  t_path	*path;
  int		step;
}		t_crosser;

typedef struct	s_data
{
  t_node	*start;
  t_node	*end;
  t_list	*nodes;
  t_list	*crossers;
  t_list	*paths;
}		t_data;

bool	load_data(t_data *data, int fd);

void	launch_lemin(t_data *world);

#endif /* !LEMIN_H_ */
