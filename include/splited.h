/*
** slited.h for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Thu Jul  7 15:52:46 2016 Loïc GIGOMAS
** Last update Thu Jul  7 15:59:35 2016 Loïc GIGOMAS
*/

#ifndef SPLITED_H_
# define SPLITED_H_

# include "new.h"
# include "vector.h"

typedef struct	s_splited_init
{
  char		*str;
  char		*splitchars;
}		t_splited_init;

typedef struct	s_splited
{
  t_object	__obj__;
  t_vector	*words;
  char		*ptr;
}		t_splited;

t_splited		*t_splited_new(t_splited_init var);

#endif /* !SPLITED_H_ */
