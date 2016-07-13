/*
** list_accessors.c for jetpack2T3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Thu Jul  7 11:16:21 2016 Loïc GIGOMAS
** Last update Thu Jul  7 11:16:21 2016 Loïc GIGOMAS
*/

#include "list.h"

size_t	list_size(t_list *l)
{
  return (l->size);
}

void		*list_get(t_list *m, size_t index)
{
  if (!m || index >= m->size)
    return (NULL);
  return (m->array[index]);
}
