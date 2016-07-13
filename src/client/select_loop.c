/*
** select_loop.c for select_loop in /home/drozdz_b/rendu/jetpack2Tek3/src/client
**
** Made by drozdz_b
** Login   <drozdz_b@epitech.net>
**
** Started on  Tue Jul 12 21:30:59 2016 drozdz_b
** Last update Wed Jul 13 17:52:00 2016 Loïc GIGOMAS
*/

#include "client/select_loop.h"

void			select_loop(t_descr *descr,
				    t_func *fctstop,
				    t_func *fctr,
				    t_func *fctw)
{
  fd_set		readfd;
  fd_set		writefd;
  struct timeval	timer;

  readfd = descr->readfd;
  writefd = descr->writefd;
  timer = (struct timeval){0, 33333};
  while (select(descr->cli->socket + 1, &readfd,
		&writefd, NULL, &timer) != -1
	 && !fctstop->fct(fctstop->params))
    {
      if (FD_ISSET(descr->cli->socket, &readfd))
	if (fctr->fct(fctr->params) == -1)
	  return ;
      if (FD_ISSET(descr->cli->socket, &writefd))
	if (fctw->fct(fctw->params) == -1)
	  return ;
      readfd = descr->readfd;
      writefd = descr->writefd;
      timer = (struct timeval){0, 33333};
    }
}
