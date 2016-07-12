/*
** entity.h for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Fri Jul  8 18:45:30 2016 Loïc GIGOMAS
** Last update Fri Jul  8 19:03:45 2016 Loïc GIGOMAS
*/

#ifndef ENTITY_H_
# define ENTITY_H_

# include "new.h"

typedef struct	s_entity_init
{
  double	x;
  double	y;
  double	weight;
  double	gravity;
}		t_entity_init;

typedef struct	s_entity
{
  t_object	__obj__;
  double	x;
  double	y;
  double	weight;
  double	gravity;
  double	speed_x;
  double	speed_y;
}		t_entity;

t_entity	*t_entity_new(t_entity_init var);

#endif /* !ENTITY_H_ */
