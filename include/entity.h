/*
** entity.h for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Fri Jul  8 18:45:30 2016 Loïc GIGOMAS
** Last update Wed Jul 13 17:24:52 2016 Loïc GIGOMAS
*/

#ifndef ENTITY_H_
# define ENTITY_H_

# include "new.h"

# define AIR	(1.2)
# define WATER	(1030.0)
# define IRON	(7870.0)
# define WOOD	(700.0)

# define DRAG_COEFF	(1.0)
# define OBJ_DIAMETER	(1.0)
# define FLUID_DENS	(AIR)
# define OBJ_DENS	((WATER + IRON) / 2.0)

typedef struct	s_entity_init
{
  double	x;
  double	y;
  double	accel_x;
  double	accel_y;
}		t_entity_init;

typedef struct	s_entity
{
  t_object	__obj__;
  double	x;
  double	y;
  double	weight;
  double	speed_x;
  double	speed_y;
  double	accel_x;
  double	accel_y;
  double	speed_max;
  double	width;
  double	height;
}		t_entity;

t_entity	*t_entity_new(t_entity_init var);

#endif /* !ENTITY_H_ */
