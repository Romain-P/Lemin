/*
** lemin.h for  in /home/romain.pillot/projects/CPE_2016_Lemin/inc
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu Apr 20 17:46:54 2017 romain pillot
** Last update Sat Apr 22 18:05:50 2017 romain pillot
*/

#ifndef LEMIN_H_
# define LEMIN_H_

# include "list.h"
# include <stdbool.h>

# define EXIT_FAIL      (84)

/* parsing node types */
# define NODE_START	(0)
# define NODE_END	(1)
# define NODE_NORMAL	(2)

typedef struct  s_node
{
  char          *label;
  int           posx;
  int           posy;
  t_list	*nodes;
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

typedef struct	s_link
{
  t_node	*node_a;
  t_node	*node_b;
}		t_link;

typedef struct	s_data
{
  t_node	*start;
  t_node	*end;
  t_list	*nodes;
  t_list	*crossers;
  t_list	*paths;
  t_list	*links;
}		t_data;

/* parsing */
bool	load_data(t_data *data, int fd);

bool	build_crossers(t_data *data, char *str);

bool	build_node(t_data *data, char *str, char node_type);

bool	build_link(t_data *data, char *str);

/* display */
void	display_data(t_data *data);

/* path */
void	build_paths(t_data *data);

/* launching */
void	launch_lemin(t_data *world);

#endif /* !LEMIN_H_ */
