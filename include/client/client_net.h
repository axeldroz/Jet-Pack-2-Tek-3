/*
** client_net.h for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Wed Jul 13 16:51:02 2016 Loïc GIGOMAS
** Last update Wed Jul 13 16:51:15 2016 Loïc GIGOMAS
*/

#ifndef CLIENT_NET_H_
#define CLIENT_NET_H_

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "client/graphic.h"
#include "gnl.h"
#include "map.h"
#include "game_map.h"
#include "tcpnetc.h"
#include "thread.h"
#include "cross_mutex.h"

typedef struct	s_descr
{
  t_game_map	*map;
  t_map		*players;
  int		id;
  t_tcpnetc	*cli;
  t_map		*commands;
  t_gnl		gnl;
  fd_set	readfd;
  fd_set	writefd;
  int		run;
  struct iovec	io[16];
  int		iovcnt;
  t_map		*obj;
  t_window	win;
  t_cmutex	lock;
}               t_descr;

typedef int	(*t_command)(t_splited *, t_descr *);

t_cth_ret	net_routine(t_cth_params params);

int	write_iov(t_descr *s, char *msg);
int	iov_send(t_descr *s);

#endif
