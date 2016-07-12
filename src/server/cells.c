#include <stdio.h>
#include "pair.h"
#include "server.h"
#include "server/player.h"

/*
** t_pair *p {server, player}
*/
int	cell_empty(NSD t_pair *p, NSD void **cell, NSD char *b, NSD size_t *o)
{
  return (0);
}

int	cell_elec(t_pair *p, NSD void **cell, NSD char *b, NSD size_t *o)
{
  if (!(((t_server *)p->first)->game.looser))
    ((t_server *)p->first)->game.looser = ((t_player *)p->second)->fd;
  else
    ((t_server *)p->first)->game.looser = -1;
  return (0);
}

int	cell_coin(t_pair *p, void **cell, NSD char *b, NSD size_t *o)
{
  ++((t_player *)p->second)->coins;
  *cell = cell_empty;
  /* snprintf(&buff[offset], GLBUFF - offset, "COIN %d %f %f\n", */
  /* 	   p->fd, p->entity->x, p->entity->y, p->coins); */
  /* offset = strlen(buff); */

  return (0);
}
