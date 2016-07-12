/*
** map_accessors.c for jetpack2T3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Thu Jul  7 11:16:16 2016 Loïc GIGOMAS
** Last update Thu Jul  7 11:16:17 2016 Loïc GIGOMAS
*/

#include "map.h"

size_t	map_size(t_map *m)
{
  return (m->size);
}

void		*map_get(t_map *m, void *key)
{
  size_t	i;

  for (i = 0; i < m->size; ++i)
    {
      if (m->array[i] && !m->compar(key, m->array[i]->first))
	return (m->array[i]->second);
    }
  return (m->defVal);
}
