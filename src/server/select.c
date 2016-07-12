#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include "server.h"
#include "server/player.h"
#include "foreach.h"

static int	max_fd(t_server *s)
{
  s->max_fd = s->net->socket;
  FOREACH(t_pair *, p, s->clients)
    if (*(int *)p->first > s->max_fd)
      s->max_fd = *(int *)p->first;
  return (0);
}

static int	player_read(t_player *c, t_server *s)
{
  int		r;
  char		*str;
  t_splited	*cmp;

  str = NULL;
  if (c && (r = get_next_line(&c->gnl, c->fd, &str)) < 3)
    {
      if (r == 0 || r == 1)
	{
	  if ((cmp = new(t_splited, str)) == NULL)
	    return(-1);
	  r = MGET(t_command, s->commands,
		   VGETP(char *, cmp->words, 0))(cmp, c, s);
	  free(str);
	  delete(cmp);
	  if (r == -1)
	    return (-1);
	}
      return (0);
    }
  return (-1);
}

static int	players_loop(t_server *s, fd_set *readfds, fd_set *writefds)
{
  t_player	*pl;
  int		fd;

  FOREACH(t_pair *, p, s->clients)
    {
      pl = p->second;
      if (FD_ISSET(pl->fd, readfds))
	{
	  if (player_read(pl, s) == -1)
	    {
	      fd = *(int *)p->first;
	      map_remove(s->clients, &pl->fd);
	      FD_CLR(pl->fd, &s->readfds);
	      if (IS_READY(pl))
		--s->game.n_ready;
	      delete(pl);
	      if (fd == s->max_fd)
		return (max_fd(s));
	    }
	}
      if (FD_ISSET(pl->fd, writefds))
	if (iov_send(s, pl) == -1)
	  return (-1);
    }
  return (0);
}

static int		game_loop(t_server *s)
{
  static clock_t	lasttime;

  if (!s)
    return (-1);
  if (s->game.n_ready < 2)
    {
      s->game.started = 0;
      return (0);
    }
  if (!s->game.started)
    {
      lasttime = clock();
      s->game.started = 1;
      printf("Starting new game.\n");
      send_to_all(s, "START\n");
    }
  if (calc_states(s, lasttime) == -1 ||
      send_states(s) == -1)
    return (-1);
  printf("{%f}[%f] Game loop.\n", (double)clock(), ((double)clock()) / (double)CLOCKS_PER_SEC);
  return (0);
}

int			select_loop(t_server *s)
{
  fd_set		readfds;
  fd_set		writefds;
  struct timeval	tv;
  int			rs;

  while (s->run)
    {
      readfds = s->readfds;
      writefds = s->writefds;
      tv = (struct timeval){0, 50000};
      if ((rs = select(s->max_fd + 1, &readfds, &writefds, NULL, &tv)) == -1 ||
	  game_loop(s) == -1)
	return (-1);
      if (rs == 0)
	continue;
      if (FD_ISSET(s->net->socket, &readfds))
	{
	  if (add_client(s) == -1)
	    return (-1);
	  continue ;
	}
      if (players_loop(s, &readfds, &writefds) == -1)
	return (-1);
    }
  return (0);
}
