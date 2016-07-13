/*
** select_loop.c for select_loop in /home/drozdz_b/rendu/jetpack2Tek3/src/client
**
** Made by drozdz_b
** Login   <drozdz_b@epitech.net>
**
** Started on  Tue Jul 12 21:30:59 2016 drozdz_b
** Last update Tue Jul 12 23:48:00 2016 Loïc GIGOMAS
*/

#include "client/select_loop.h"

void set_fd_value(SOCKET fd, fd_set *readfd, fd_set *writefd, struct timeval *timer)
{
    FD_ZERO(readfd);
    FD_ZERO(writefd);
    FD_SET(fd, readfd);
    FD_SET(fd, writefd);
    *timer = (struct timeval){0, 33333};
}

void select_loop(SOCKET fd, t_func *fctstop, t_func *fctr, t_func *fctw)
{
    fd_set readfd;
    fd_set writefd;
    struct timeval timer;

    set_fd_value(fd, &readfd, &writefd, &timer);
    while (select(fd + 1, &readfd, &writefd, NULL, &timer) != -1
    && !fctstop->fct(fctstop->params))
    {
      if (FD_ISSET(fd, &readfd))
	fctr->fct(fctr->params);
      if (FD_ISSET(fd, &writefd))
	fctw->fct(fctw->params);
      set_fd_value(fd, &readfd, &writefd, &timer);
    }
}
