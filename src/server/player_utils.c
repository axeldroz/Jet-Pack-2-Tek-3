#include <stdio.h>
#include "pair.h"
#include "server/player.h"
#include "foreach.h"

static void	max_fd(t_server *s)
{
  s->max_fd = s->net->socket;
  FOREACH(t_pair *, p, s->clients)
    if (*(int *)p->first > s->max_fd)
      s->max_fd = *(int *)p->first;
}

int	remove_client(t_server *s, t_player *p)
{
  int	fd;

  fd = p->fd;
  if (map_remove(s->clients, &p->fd) != MAP_NOERR)
    return (-1);
  FD_CLR(fd, &s->readfds);
  if (IS_READY(p))
    --s->game.n_ready;
  delete(p);
  printf("Removing client fd = %d\n", fd);
  if (fd == s->max_fd)
    max_fd(s);
  return (0);
}

int	send_to_all(t_server *s, char *str)
{
  FOREACH(t_pair *, p, s->clients)
    if (write_iov(s, p->second, str) == -1)
      return (-1);
  return (0);
}

static int	check_colliders(t_server *s, t_player *p, char *b, size_t *o)
{
  int		ret;
  t_pair	*pair;

  if ((pair = new(t_pair)) == NULL)
    return (GAME_FINISHED);
  FOREACH(t_pair *, p, s->clients)
    {

    }
  return (GAME_RUNNING);
}

int			calc_states(t_server *s, struct timeval *last)
{
  struct timeval	now;
  char			buff[GLBUFF];
  size_t		offset;
  double		time;
  t_player		*p;


  gettimeofday(&now, NULL);
  time = ((now.tv_sec - last->tv_sec) + 1e-6 * (now.tv_usec - last->tv_usec));;
  printf("time = %f\n", time);
  memset(buff, 0, GLBUFF);
  offset = 0;
  FOREACH(t_pair *, tmp, s->clients)
    {
      p = tmp->second;
      if (update_pos(s, p, time) == GAME_FINISHED)
	return (GAME_FINISHED);
      snprintf(&buff[offset], GLBUFF - offset, "PLAYER %d %f %f %d\n",
	       p->fd, p->entity->x, p->entity->y, p->coins);
      offset = strlen(buff);
    }
  send_to_all(s, buff);
  return (GAME_RUNNING);
}
