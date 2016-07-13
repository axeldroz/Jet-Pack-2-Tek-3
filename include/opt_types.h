/*
** opt_types.h for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Wed Jul 13 16:47:53 2016 Loïc GIGOMAS
** Last update Wed Jul 13 16:47:54 2016 Loïc GIGOMAS
*/

#ifndef OPT_TYPE_H
# define OPT_TYPE_H

# ifndef GET_OPT_H_
#  error "Never use opt_types.h directly; include get_opt.h instead."
# endif

# include <stdlib.h>

extern int	(*const opt_func[])(char *opt, void *type);

extern size_t const	opt_size[];

#endif /* !OPT_TYPE_H */
