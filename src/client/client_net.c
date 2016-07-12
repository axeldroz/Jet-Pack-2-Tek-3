#include "client/client_net.h"
#include "tcpnetc.h"
#include "thread.h"

t_cth_ret net_routine(t_cth_params var)
{

    return (NULL);
}

/*void  get_map(t_tcpnetc *cli)
{
    t_splited split;


    split = new(t_splited, )
}*/

static int	player_read(t_descr *c, t_map *fct)
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
	    return(-1);
	  r = MGET(t_command, fct,
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

int			select_loop(t_descr *s)
{
  fd_set		readfds;
  fd_set		writefds;
  struct timeval	tv;
  int			rs;

  while (s->run)
    {
      readfds = s->readfds;
      writefds = s->writefds;
      tv = (struct timeval){0, 33333};
      if (game_loop(s) == -1 ||
	  (rs = select(s->cli->socket + 1, &readfds, &writefds, NULL, &tv)) == -1)
	return (-1);
      if (rs == 0)
	continue;
      if (FD_ISSET(s->cli->socket, &readfds))
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
