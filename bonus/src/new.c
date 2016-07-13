/*
** new.c for jetpack2T3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Thu Jul  7 11:16:10 2016 Loïc GIGOMAS
** Last update Thu Jul  7 11:16:11 2016 Loïc GIGOMAS
*/

#include <string.h>
#include "new.h"

static t_object	*new_front = NULL;

static	void clean_at_exit()
{
  while (new_front)
    delete(new_front);
}

t_object	*t_object_new(t_object_init var)
{
  t_object	*new;
  static char	first = 1;

  if (!var.obj_size)
    return (NULL);
  if ((new = malloc(var.obj_size)) == NULL)
    return (NULL);
  memset(new, 0, var.obj_size);
  if (first)
    {
      atexit(clean_at_exit);
      first = 0;
    }
  new->__delete__ = var.del;
  new->next = NULL;
  new->prev = NULL;
  _reg_object(new);
  return (new);
}

void	_delete(t_object *obj)
{
  if (!obj)
    return ;
  if (obj->__delete__)
    obj->__delete__(obj);
  _unreg_object(obj);
  free(obj);
}

void	_reg_object(t_object *obj)
{
  if (!obj)
    return ;
  if (new_front == NULL) {
    obj->next = obj;
    obj->prev = obj->next;
    new_front = obj;
  }else{
    obj->next = new_front;
    obj->prev = new_front->prev;
    obj->next->prev = obj;
    obj->prev->next = obj;
  }
}

void	_unreg_object(t_object *obj)
{
  if (!obj)
    return ;
  if (obj->prev == obj && obj->next == obj) {
    new_front = NULL;
  } else {
    obj->prev->next = obj->next;
    obj->next->prev = obj->prev;
    new_front = obj->next;
  }
}
