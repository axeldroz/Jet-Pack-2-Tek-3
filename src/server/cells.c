#include "server.h"
#include "server/player.h"

/*
** t_pair *p {server, player}
*/
int	cell_empty(NSD t_server *s, NSD t_player *p, NSD void **cell)
{
  return (0);
}

int	cell_elec(NSD t_server *s, NSD t_player *p, NSD void **cell)
{
  if (!s->game.looser)
    s->game.looser = p->fd;
  else
    s->game.looser = -1;
  return (0);
}

int	cell_coin(NSD t_server *s, t_player *p, void **cell)
{
  ++p->coins;
  *cell = cell_empty;
  return (0);
}
