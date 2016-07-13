/*
** graphic4.c for graphic in /home/drozdz_b/rendu/jetpack2Tek3/src/client
**
** Made by drozdz_b
** Login   <drozdz_b@epitech.net>
**
** Started on  Tue Jul 12 17:33:12 2016 drozdz_b
** Last update Wed Jul 13 23:10:54 2016 Loïc GIGOMAS
*/

#include "client/graphic.h"
#include "foreach.h"

void		display_texture(t_window *win, SDL_Texture *texture,
				float x, float y)
{
  SDL_Rect	rect;

  rect.w = TILE_SIZE;
  rect.h = TILE_SIZE;
  rect.x = x * TILE_SIZE;
  rect.y = win->size_screen.y - y * TILE_SIZE - TILE_SIZE;
  SDL_RenderCopy(win->renderer, texture, NULL, &rect);
}

void		display_texture2(t_window *win, SDL_Texture *texture,
				float x, float y)
{
  SDL_Rect	rect;

  rect.w = TILE_SIZE;
  rect.h = TILE_SIZE;
  rect.x = x * TILE_SIZE;
  rect.y = y * TILE_SIZE - TILE_SIZE;
  SDL_RenderCopy(win->renderer, texture, NULL, &rect);
}

void	graph_disp_others(t_descr *descr, t_cond *cond)
{
  FOREACH(t_pair *, p, descr->players)
    {
      if ((long)p->first != descr->id
	  && ((t_graph_item *)p->second)->pos.x < cond->w
	  && ((t_graph_item *)p->second)->pos.x >= cond->i2
	  && ((t_graph_item *)p->second)->pos.y < cond->h
	  && ((t_graph_item *)p->second)->pos.y >= cond->j2)
	display_texture(&descr->win, ((t_graph_item *)p->second)->texture,
			((t_graph_item *)p->second)->pos.x - cond->i2,
      ((t_graph_item *)p->second)->pos.y - cond->j2 - 1);
    }
}

void			graph_display_map(t_descr *descr, t_game_map *map,
					  t_graph_item *player)
{
  t_cond		cond;
  SDL_Texture		*texture;

  cond.i = 0;
  cond.i2 = player->pos.x - player->view.x / 4.0;
  cond.w = player->pos.x + player->view.x / 4.0 * 3.0;
  cond.j = 0;
  cond.j2 = player->pos.y - player->view.y / 2.0;
  cond.h = player->pos.y + player->view.y / 2.0;
  while (cond.j < map->h)
    {
      while (cond.i < map->w)
        {
	  texture = VGETP(SDL_Texture*, map->cells,
			  (cond.j) * map->w + cond.i);
	  if (texture != (void *)-1 && texture != NULL)
	    display_texture2(&descr->win, texture,
			     cond.i - cond.i2,  cond.j + cond.j2
			     + player->view.y / 2.0  - 1);
	  ++cond.i;
        }
      cond.i = 0;
      ++cond.j;
    }
  graph_disp_others(descr, &cond);
}
