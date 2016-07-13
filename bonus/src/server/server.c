/*
** clients.c for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Fri Jul  8 15:58:20 2016 Loïc GIGOMAS
** Last update Tue Jul 12 19:37:18 2016 Loïc GIGOMAS
*/

#include <stdio.h>
#include "server.h"
#include "server/player.h"
#include "foreach.h"
#include "splited.h"
#include "vector.h"
#include "game_map.h"

void		ser_del(void *ptr)
{
  t_server	*s;

  if (!ptr)
    return ;
  s = ptr;
  delete(s->net);
  delete(s->clients);
  delete(s->commands);
  delete(s->game.origin);
  delete(s->game.map);
}

static int	comp_fd(const void *a, const void *b)
{
  return (((int)(size_t)a) - ((int)(size_t)b));
}

static int	comp_str(const void *a, const void *b)
{
  const char	*_a = a;
  const char	*_b = b;

  if (!a || !b)
    return (-1);
  return (strcmp(_a, _b));
}

static int	no_such_cmd(t_splited *str, t_player *c, t_server *s)
{
  if (!str)
    return (0);
  if (!c || !s)
    return (-1);
  return (0);
}

t_server	*t_server_new(t_server_init var)
{
  t_server	*s;

  if (!var.port ||
      (s = (t_server *)new(t_object, sizeof(t_server), &ser_del)) == NULL ||
      (s->net = new(t_tcpnets, var.port)) == NULL ||
      (s->clients = new(t_map, &comp_fd)) == NULL ||
      (s->commands = new(t_map, &comp_str, 0, &no_such_cmd)) == NULL ||
      (s->game.origin = new(t_game_map)) == NULL ||
      (s->game.map = new(t_game_map)) == NULL)
    return (NULL);
  FD_ZERO(&s->readfds);
  FD_SET(s->net->socket, &s->readfds);
  s->run = 1;
  s->max_fd = s->net->socket;
  s->game.gravity = var.gravity;
  return (s);
}
