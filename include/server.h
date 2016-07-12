/*
** server.h for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Fri Jul  8 15:58:13 2016 Loïc GIGOMAS
** Last update Tue Jul 12 14:16:49 2016 Loïc GIGOMAS
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <sys/select.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

# include "new.h"
# include "tcpnets.h"
# include "map.h"
# include "game_map.h"

# define GAME_RUNNING	(0)
# define GAME_FINISHED	(1)

# define NSD	__attribute__((unused))

typedef struct	s_player	t_player;

typedef struct	s_game
{
  t_game_map	*map;
  float		gravity;
  int		n_ready;
  int		started;
  int		looser;
}		t_game;

typedef struct	s_server_init
{
  int		port;
  float		gravity;
}		t_server_init;

typedef struct	s_server
{
  t_object	__obj__;
  t_tcpnets	*net;
  t_map		*clients;
  t_map		*commands;
  fd_set	readfds;
  fd_set	writefds;
  int		run;
  int		max_fd;
  t_game	game;
}		t_server;

typedef int	(*t_command)(t_splited *, t_player *, t_server *);

t_server	*t_server_new(t_server_init var);

int	select_loop(t_server *s);

# include "server/player.h"

#endif /* !SERVER_H_ */
