/*
** cmd.c for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Wed Jul 13 17:11:06 2016 Loïc GIGOMAS
** Last update Wed Jul 13 17:11:30 2016 Loïc GIGOMAS
*/

#include <stdlib.h>
#include "game_map.h"
#include "map.h"
#include "client/cmd.h"

int	com_id(t_splited *str, t_descr *descr)
{
  if (str->words->size >= 2)
    descr->id = atoi(VGETP(char *, str->words, 1));
  if (descr->map->cells->size != 0)
    {
      write_iov(descr, "READY\n");
      cmutex_unlock(&descr->lock);
    }
  return (0);
}

int	com_map(t_splited *str, t_descr *descr)
{
  if (map_from_split(descr->map, str, descr->obj) != 0)
    return (-1);
  if (descr->id != -1)
    {
      write_iov(descr, "READY\n");
      cmutex_unlock(&descr->lock);
    }
  return (0);
}

int		com_player(t_splited *str, t_descr *descr)
{
  t_graph_item	*player;
  long		id;

  cmutex_lock(&descr->lock);
  id = atoi(VGETP(char *, str->words, 1));
  player = MGET(t_graph_item *, descr->players, (void *)id);
  if (player == NULL)
    {
      player = graph_create_player(&descr->win,
				   MGET(SDL_Texture *, descr->obj,
					(void *)((long)'p')),
				   (descr->id == id) ? 1 : 0);
      map_add(descr->players, (void *)id, player);
    }
  player->pos.x = atof(VGETP(char *, str->words, 2));
  player->pos.y = atof(VGETP(char *, str->words, 3));
  player->coins = atoi(VGETP(char *, str->words, 4));
  cmutex_unlock(&descr->lock);
  return (0);
}

int	com_start(t_splited *str, t_descr *descr)
{
  (void) str;
  (void) descr;
  return (0);
}

int	com_coin(t_splited *str, t_descr *descr)
{
  int	x;
  int	y;

  if (str->words->size < 4)
    return (0);
  x = atoi(VGETP(char *, str->words, 2));
  y = atoi(VGETP(char *, str->words, 3));
  descr->map->cells->array[(descr->map->h - y - 1)
			   * descr->map->w + x] = (void *)-1;
  return (0);
}
