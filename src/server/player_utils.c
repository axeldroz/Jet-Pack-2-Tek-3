/*
** player_utils.c for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Tue Jul 12 19:37:30 2016 Loïc GIGOMAS
** Last update Tue Jul 12 20:00:11 2016 Loïc GIGOMAS
*/

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
  if (IS_READY(p) && s->game.n_ready)
    --s->game.n_ready;
  delete(p);
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

/*
** stats[0] = id winner
** stats[1] = coins winner
** memset : all to -1;
*/
int		end_game(t_server *s)
{
  char		buff[24];
  t_stats	st;

  st = (t_stats){0, 0};
  if (!s->game.looser)
    {
      FOREACH(t_pair *, p, s->clients)
	if (st.id == 0 || ((t_player *)p->second)->coins > st.coins)
	  st = (t_stats){*(int *)p->first, ((t_player *)p->second)->coins};
	else if (st.id != 0 && ((t_player *)p->second)->coins == st.coins)
	  st.id = -1;
    }
  else if (s->game.looser == -1)
    st.id = -1;
  else
    {
      FOREACH(t_pair *, p, s->clients)
	if (*(int *)p->first != s->game.looser)
	  {
	    st.id = *(int *)p->first;
	    break;
	  }
    }
  snprintf(buff, 24, "FINISH %d\n", st.id);
  return (send_to_all(s, buff));
}

int			calc_states(t_server *s, struct timeval *last)
{
  struct timeval	now;
  char			buff[GLBUFF];
  size_t		offset;
  double		time;
  t_player		*p;


  gettimeofday(&now, NULL);
  time = ((now.tv_sec - last->tv_sec) + 1e-6 * (now.tv_usec - last->tv_usec));
  memset(buff, 0, GLBUFF);
  offset = 0;
  FOREACH(t_pair *, tmp, s->clients)
    {
      p = tmp->second;
      if (update_pos(s, p, time) == GAME_FINISHED)
	return (GAME_FINISHED);
      if (check_colliders(s, p, buff, &offset) == GAME_ERROR)
	return (GAME_ERROR);
      snprintf(&buff[offset], GLBUFF - offset, "PLAYER %d %f %f %d\n",
	       p->fd, p->entity->x, p->entity->y, p->coins);
      offset = strlen(buff);
    }
  send_to_all(s, buff);
  return (GAME_RUNNING);
}
