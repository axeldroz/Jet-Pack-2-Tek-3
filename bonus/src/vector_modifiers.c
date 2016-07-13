/*
** vector_modifiers.c for jetpack2T3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Thu Jul  7 11:14:21 2016 Loïc GIGOMAS
** Last update Thu Jul  7 11:14:22 2016 Loïc GIGOMAS
*/

#include "vector.h"

void		vec_del(void *ptr)
{
  t_vector	*v;

  if (!ptr)
    return ;
  v = ptr;
  free(v->array);
}

t_vector	*t_vector_new(t_vector_init var)
{
  t_vector	*v;

  if ((v = (t_vector *)new(t_object, sizeof(t_vector), &vec_del)) == NULL)
    return (NULL);
  ++var.size;
  if ((v->array = malloc(sizeof(void *) * var.size)) == NULL)
    return (NULL);
  memset(v->array, 0, var.size * sizeof(void *));
  v->alloc = var.size;
  v->size = 0;
  return (v);
}

int	vector_push_back(t_vector *v, void *elem)
{
  if (!v)
    return (VEC_ARGS);
  if (v->size >= (v->alloc - 1))
    {
      if ((v->array = realloc(v->array,
			      (++v->alloc) * sizeof(void *))) == NULL)
	return (VEC_FUNC);
    }
  v->array[v->size] = elem;
  ++(v->size);
  return (VEC_NOERR);
}

int	vector_pop_back(t_vector *v)
{
  if (!v)
    return (VEC_ARGS);
  if (v->size == 0 || v->alloc == 1)
    return (VEC_NOMORE);
  --v->size;
  if (((v->alloc - 1) - v->size) >= VEC_MAX_DIFF)
    {
      v->alloc = v->size + 1;
      if ((v->array = realloc(v->array,
				 (v->alloc) * sizeof(void *))) == NULL)
	return (VEC_FUNC);
    }
  return (VEC_NOERR);
}

int	vector_set(t_vector *v, size_t index, void *elem)
{
  if (!v || index >= v->size)
    return (VEC_ARGS);
  v->array[index] = elem;
  return (VEC_NOERR);
}
