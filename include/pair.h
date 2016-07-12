/*
** pair.h for jetpack2T3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Thu Jul  7 11:14:57 2016 Loïc GIGOMAS
** Last update Thu Jul  7 11:14:58 2016 Loïc GIGOMAS
*/

#ifndef PAIR_H_
# define PAIR_H_

# include "new.h"

typedef struct	s_pair_init
{
  void		*first;
  void		*second;
}		t_pair_init;

typedef struct	s_pair
{
  t_object	__obj__;
  void		*first;
  void		*second;
}		t_pair;

t_pair		*t_pair_new(t_pair_init var);

#endif /* !PAIR_H_ */
