/*
** list_modifiers.c for jetpack2T3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Thu Jul  7 11:14:45 2016 Loïc GIGOMAS
** Last update Thu Jul  7 11:14:47 2016 Loïc GIGOMAS
*/

#include <string.h>
#include "list.h"

void	list_del(void *ptr)
{
  t_list	*l;

  if (!ptr)
    return ;
  l = ptr;
  free(l->array);
}

t_list	*t_list_new(t_list_init var)
{
  t_list	*l;

  if ((l = (t_list *)new(t_object, sizeof(t_list), &list_del)) == NULL)
    return (NULL);
  ++var.size;
  if ((l->array = malloc(sizeof(void *) * var.size)) == NULL)
    return (NULL);
  memset(l->array, 0, sizeof(void *) * var.size);
  l->alloc = var.size;
  l->size = 0;
  return (l);
}

int		list_add(t_list *l, void *value, size_t index)
{
  size_t	j;

  if (!l || index > l->size)
    return (LIST_ARGS);
  if (l->size >= l->alloc - 1)
    if ((l->array = realloc(l->array,
			    (++l->alloc) * sizeof(void *))) == NULL)
      return (LIST_FUNC);
  l->array[l->size] = NULL;
  for (j = l->size; j && j >= index; --j)
    l->array[j] = l->array[j - 1];
  l->array[index] = value;
  ++l->size;
  return (LIST_NOERR);
}

int		list_remove(t_list *l, size_t index)
{
  size_t	i;

  if (!l || index >= l->size)
    return (LIST_ARGS);
  if (!l->size)
    return (LIST_NOMORE);
  --l->size;
  for (i = index; i < l->size; ++i)
    l->array[i] = l->array[i + 1];
  if (((l->alloc - 1) - l->size) >= LIST_MAX_DIFF)
    {
      l->alloc = (l->size + 1);
      if ((l->array = realloc(l->array,
			      (l->alloc) * sizeof(void *))) == NULL)
	return (LIST_FUNC);
    }
  return (LIST_NOERR);
}
