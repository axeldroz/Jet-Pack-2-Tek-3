#include <stdlib.h>
#include "game_map.h"
#include "map.h"
#include "client/cmd.h"

int	com_id(t_splited *str, t_descr *descr)
{
  if (str->words->size >= 2)
    descr->id = atoi(VGETP(char *, str->words, 1));
  return (0);
}

int	com_map(t_splited *str, t_descr *descr)
{
  map_from_split(descr->map, str, descr->obj);
  return (0);
}

int	com_player(t_splited *str, t_descr *descr)
{
  t_graph_item *player;
  long id;

  id = atoi(VGETP(char *, str->words, 1));
  player = MGET(t_graph_item *, descr->players, (void *)id);
  if (player == NULL)
    {
      player = graph_create_player(&descr->win, MGET(SDL_Texture *, descr->obj, (void *)((long)'p')),
				   (descr->id == id) ? 1 : 0);
      map_add(descr->players, (void *)id, player);
    }
  player->pos.x = atof(VGETP(char *, str->words, 2));
  player->pos.y = atof(VGETP(char *, str->words, 3));
  player->coins = atoi(VGETP(char *, str->words, 4));
  return (0);
}

int	com_start(t_splited *str, t_descr *descr)
{
  return (0);
}

int	com_coin(t_splited *str, t_descr *descr)
{
  return (0);
}
