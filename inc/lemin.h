/*
** lemin.h for  in /home/romain.pillot/projects/CPE_2016_Lemin/inc
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu Apr 20 17:46:54 2017 romain pillot
** Last update Fri Apr 21 02:46:27 2017 romain pillot
*/

#ifndef LEMIN_H_
# define LEMIN_H_

# include "list.h"
# include <stdbool.h>

# define EXIT_FAIL      (84)

/* 3 states boolean */
typedef enum	e_bool
{
  TRUE = 1,
  FALSE = 0,
  ERROR = -1
}		t_bool;

/* parsing states */
typedef enum	e_state
{
  CROSSERS_NUMBER = 0,
  START_NODE = 1,
  NODES = 2,
  END_NODE = 3,
  LINKS = 4
}		t_state;

typedef struct  s_node
{
  char          *label;
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

/* parsing */
bool	load_data(t_data *data, int fd);

bool	state_crossers(t_data *data, char *str, t_state *state);

bool    state_start(t_data *data, char *str, t_state *state);

bool    state_nodes(t_data *data, char *str, t_state *state);

bool    state_end(t_data *data, char *str, t_state *state);

bool    state_links(t_data *data, char *str, t_state *state);

/* launching */
void	launch_lemin(t_data *world);

#endif /* !LEMIN_H_ */
