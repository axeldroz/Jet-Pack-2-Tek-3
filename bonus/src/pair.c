/*
** pair.c for jetpack2T3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Thu Jul  7 11:14:31 2016 Loïc GIGOMAS
** Last update Thu Jul  7 11:14:32 2016 Loïc GIGOMAS
*/

#include "pair.h"

t_pair		*t_pair_new(t_pair_init var)
{
  t_pair	*p;

  if ((p = (t_pair *)new(t_object, sizeof(t_pair))) == NULL)
    return (NULL);
  p->first = var.first;
  p->second = var.second;
  return (p);
}
