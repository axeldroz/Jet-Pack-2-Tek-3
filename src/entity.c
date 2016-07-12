/*
** entity.c for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Fri Jul  8 18:52:38 2016 Loïc GIGOMAS
** Last update Fri Jul  8 19:09:53 2016 Loïc GIGOMAS
*/

#include "entity.h"

/* void	ent_del(void *ptr) */
/* { */
/*   t_entity	*e; */

/*   if (!ptr) */
/*     return ; */
/*   e = ptr; */
/* } */

t_entity	*t_entity_new(t_entity_init var)
{
  t_entity	*e;

  if ((e = (t_entity *)new(t_object, sizeof(t_entity))) == NULL)
    return (NULL);
  e->x = var.x;
  e->y = var.y;
  e->weight = var.weight;
  e->gravity = var.gravity;
  return (e);
}
