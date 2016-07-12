/*
** entity.c for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Fri Jul  8 18:52:38 2016 Loïc GIGOMAS
** Last update Tue Jul 12 16:05:56 2016 Loïc GIGOMAS
*/

#include <math.h>
#include "entity.h"

double	speed_max(t_entity *t)
{
  double	bsq;

  bsq = ((4.0 * t->accel_y * OBJ_DIAMETER) / (3.0 * DRAG_COEFF))
    * ((OBJ_DENS - FLUID_DENS) / FLUID_DENS);
  return (sqrt((bsq < 0 ? -bsq : bsq)) / 20.0);
}

t_entity	*t_entity_new(t_entity_init var)
{
  t_entity	*e;

  if ((e = (t_entity *)new(t_object, sizeof(t_entity))) == NULL)
    return (NULL);
  e->x = var.x;
  e->y = var.y;
  e->accel_x = var.accel_x;
  e->accel_y = var.accel_y;
  e->weight = 1;
  e->speed_max = speed_max(e);
  e->width = 1;
  e->height = 1;
  return (e);
}
