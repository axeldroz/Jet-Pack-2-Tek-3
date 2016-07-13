/*
** select_loop.c for select_loop in /home/drozdz_b/rendu/jetpack2Tek3/src/client
**
** Made by drozdz_b
** Login   <drozdz_b@epitech.net>
**
** Started on  Tue Jul 12 21:30:59 2016 drozdz_b
** Last update Wed Jul 13 17:18:40 2016 Loïc GIGOMAS
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
	fctr->fct(fctr->params);
      if (FD_ISSET(descr->cli->socket, &writefd))
	fctw->fct(fctw->params);
      readfd = descr->readfd;
      writefd = descr->writefd;
      timer = (struct timeval){0, 33333};
    }
}
