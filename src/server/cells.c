/*
** cells.c for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Tue Jul 12 19:40:38 2016 Loïc GIGOMAS
** Last update Wed Jul 13 10:45:12 2016 Loïc GIGOMAS
*/

#include <stdio.h>
#include "pair.h"
#include "server.h"
#include "server/player.h"

/*
** t_pair *p {server, player}, t_pair *b{buff, offset}
*/
int	cell_empty(NSD t_pair *p, NSD void **c, NSD t_pair *b, NSD size_t pos)
{
  return (0);
}

int	cell_elec(t_pair *p, NSD void **c, NSD t_pair *b, NSD size_t pos)
{
  t_server	*s;
  t_player	*pl;

  s = p->first;
  pl = p->second;
  if (!(s->game.looser))
    s->game.looser = pl->fd;
  else if (s->game.looser != pl->fd)
    s->game.looser = -1;
  return (0);
}

int		cell_coin(t_pair *p, void **cell, t_pair *b, size_t pos)
{
  char		*buff;
  size_t	*offset;
  t_server	*s;
  t_player	*pl;

  buff = b->first;
  offset = b->second;
  s = p->first;
  pl = p->second;
  ++pl->coins;
  *cell = cell_empty;
  snprintf(&buff[*offset], GLBUFF - *offset, "COIN %d %lu %lu\n",
  	   pl->fd, pos % s->game.map->w, 10 - (pos / s->game.map->w) - 1);
  *offset = strlen(buff);
  return (0);
}
