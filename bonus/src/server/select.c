/*
** select.c for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Tue Jul 12 19:38:48 2016 Loïc GIGOMAS
** Last update Wed Jul 13 16:30:44 2016 Loïc GIGOMAS
*/

#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include "server.h"
#include "server/player.h"
#include "foreach.h"

static int	player_read(t_player *c, t_server *s)
{
  int		r;
  char		*str;
  t_splited	*cmp;
  int		first;

  str = NULL;
  first = 1;
  while (c && (r = get_next_line(&c->gnl, (first ? c->fd : -1), &str)) < 2)
    {
      if (r == 0 || r == 1)
	{
	  if ((cmp = new(t_splited, str)) == NULL)
	    return (-1);
	  r = MGET(t_command, s->commands,
		   VGETP(char *, cmp->words, 0))(cmp, c, s);
	  free(str);
	  delete(cmp);
	  if (r == -1)
	    return (-1);
	}
      first = 0;
    }
  return (r >= 3 ? -1 : 0);
}

static int	players_loop(t_server *s, fd_set *readfds, fd_set *writefds)
{
  t_player	*pl;

  FOREACH(t_pair *, p, s->clients)
    {
      pl = p->second;
      if (FD_ISSET(pl->fd, writefds) && iov_send(s, pl) == -1)
	return (remove_client(s, pl));
      if (FD_ISSET(pl->fd, readfds) && player_read(pl, s) == -1)
	return (remove_client(s, pl));
    }
  return (0);
}

static int	init_game(t_server *s, struct timeval *lasttime)
{
  size_t	i;

  gettimeofday(lasttime, NULL);
  s->game.started = 1;
  s->game.looser = 0;
  FOREACH(t_pair *, p, s->clients)
    ((t_player *)p->second)->entity->speed_y = s->game.gravity / 2.0;
  s->game.map->cells->size = 0;
  i = 0;
  while (i < s->game.origin->cells->size)
    vector_push_back(s->game.map->cells,
		     vector_at(s->game.origin->cells, i++));
  send_to_all(s, "START\n");
  return (0);
}

static int		game_loop(t_server *s, fd_set *writefds)
{
  int			ret;
  static struct timeval	lasttime;

  if (!s)
    return (-1);
  if (s->game.n_ready < 2)
    {
      while (s->game.started && s->clients->size > 0)
	remove_client(s, VGET(t_pair, (t_vector *)s->clients, 0).second);
      s->game.started = 0;
      return (0);
    }
  if (!s->game.started)
    return (init_game(s, &lasttime));
  if ((ret = calc_states(s, &lasttime)) == GAME_ERROR)
    return (-1);
  if (ret == 1 || s->game.looser != 0)
    {
      end_game(s);
      s->game.n_ready = 0;
    }
  *writefds = s->writefds;
  gettimeofday(&lasttime, NULL);
  return (0);
}

int			select_loop(t_server *s)
{
  fd_set		rfds;
  fd_set		wfds;
  struct timeval	tv;
  int			rs;

  while (s->run)
    {
      rfds = s->readfds;
      wfds = s->writefds;
      tv = (struct timeval){0, 20000};
      if (game_loop(s, &wfds) == -1 ||
	  (rs = select(s->max_fd + 1, &rfds, &wfds, NULL, &tv)) == -1)
	return (-1);
      if (rs == 0)
	continue;
      if (FD_ISSET(s->net->socket, &rfds))
	{
	  if (add_client(s) == -1)
	    return (-1);
	  continue ;
	}
      if (usleep(tv.tv_usec) == -1 || players_loop(s, &rfds, &wfds) == -1)
	return (-1);
    }
  return (0);
}
