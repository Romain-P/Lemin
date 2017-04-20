/*
** lemin.h for  in /home/romain.pillot/projects/CPE_2016_Lemin/inc
** 
** Made by romain pillot
** Login   <romain.pillot@epitech.net>
** 
** Started on  Thu Apr 20 17:46:54 2017 romain pillot
** Last update Thu Apr 20 22:26:52 2017 Raphaël Goulmot
*/

#ifndef LEMIN_H_
# define LEMIN_H_

# include "list.h"

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

void	launch_lemin(t_data *world);

#endif /* !LEMIN_H_ */
