/*
** graphic4.c for graphic in /home/drozdz_b/rendu/jetpack2Tek3/src/client
**
** Made by drozdz_b
** Login   <drozdz_b@epitech.net>
**
** Started on  Tue Jul 12 17:33:12 2016 drozdz_b
** Last update Wed Jul 13 13:46:02 2016 Loïc GIGOMAS
*/

#include "client/graphic.h"
#include "foreach.h"

/*t_graph_item	graph_create_player(t_window *win, SDL_Texture *texture, int zindex)
{
  t_graph_item	item;

  item.pos.x = 0;
  item.size.x = 64;
  item.size.y = item.size.x;
  //item.pos.y = ((float)win->size_screen.y - item.size.y) / 2 / item.size.y;
  item.pos.y = 1;
  item.view.x = ((float)win->size_screen.x) / item.size.x;
  item.view.y = ((float)win->size_screen.y) / item.size.y;
  item.texture = texture;
  item.zindex = zindex;
  return (item);
}*/

void    display_texture(t_window *win, SDL_Texture *texture, float x, float y)
{
    SDL_Rect rect;

    rect.w = 64;
    rect.h = 64;
    rect.x = x * 64;
    rect.y = win->size_screen.y - y * 64 - 64;
    SDL_RenderCopy(win->renderer, texture, NULL, &rect);
}

void graph_disp_others(t_descr *descr, t_cond *cond)
{
  FOREACH(t_pair *, p, descr->players)
  {
    if ((long)p->first != descr->id
	&& ((t_graph_item *)p->second)->pos.x < cond->w
        && ((t_graph_item *)p->second)->pos.x >= cond->i2
	&& ((t_graph_item *)p->second)->pos.y < cond->h
        && ((t_graph_item *)p->second)->pos.y >= cond->j2)
      display_texture(&descr->win, ((t_graph_item *)p->second)->texture,
		      cond->i - cond->w, cond->h - cond->j);
  }
}

void graph_display_map(t_descr *descr, t_game_map *map,
		       t_graph_item *player, t_map *p)
{
    t_cond cond;
    SDL_Texture* texture;

    cond.i = player->pos.x - player->view.x / 4;
    cond.i2 = player->pos.x - player->view.x / 4;
    cond.w = player->pos.x + player->view.x / 4 * 3;
    cond.j = player->pos.y - player->view.y / 2;
    cond.j2 = player->pos.y - player->view.y / 2;
    cond.h = player->pos.y + player->view.y / 2;
    while (cond.j < cond.w)
    {
        while (cond.i < cond.h)
        {
            texture = VGETP(SDL_Texture*, map->cells,
			    cond.j * map->w + (int)cond.i);
            if (texture != (void *)-1 && texture != NULL)
                display_texture(&descr->win, texture,
				cond.i - cond.w, cond.h - cond.j);
            ++cond.i;
        }
        cond.i = 0;
        ++cond.j;
    }
    graph_disp_others(descr, &cond);
}
