/*
** select_loop.h for select_loop in /home/drozdz_b/rendu/jetpack2Tek3/include/client
**
** Made by drozdz_b
** Login   <drozdz_b@epitech.net>
**
** Started on  Tue Jul 12 21:30:31 2016 drozdz_b
** Last update Wed Jul 13 12:37:46 2016 Loïc GIGOMAS
*/

#ifndef SELECT_LOOP_H_
# define SELECT_LOOP_H_

# include <sys/select.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

# ifdef __linux__
typedef int SOCKET;
# endif

# include "client/client_net.h"

typedef struct	s_func
{
  void		*(*fct)(void *params);
  void		*params;
}               t_func;

void	select_loop(t_descr *d, t_func *fctstop, t_func *fctr, t_func *fctw);

int	write_iov(t_descr *s, char *msg);
int	iov_send(t_descr *s);
int	add_commands(t_descr *s);


#endif
