/*
** vector_accessors.c for jetpack2T3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Thu Jul  7 11:16:05 2016 Loïc GIGOMAS
** Last update Thu Jul  7 11:16:06 2016 Loïc GIGOMAS
*/

#include "vector.h"

size_t	vector_size(t_vector *v)
{
  if (!v)
    return (0);
  return (v->size);
}

size_t	vector_alloc(t_vector *v)
{
  if (!v)
    return (0);
  return (v->alloc);
}

void	*vector_at(t_vector *v, size_t index)
{
  if (!v || index >= v->size)
    return (NULL);
  return (v->array[index]);
}
