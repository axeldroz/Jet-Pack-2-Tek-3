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
  else
    s->game.looser = -1;
  return (0);
}

int		cell_coin(t_pair *p, void **cell, t_pair *b,size_t pos)
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
