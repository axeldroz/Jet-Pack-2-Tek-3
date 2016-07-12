/*
** graphic3.c for graphic3 in /home/drozdz_b/Documents/testSDL2/test1
**
** Made by drozdz_b
** Login   <drozdz_b@epitech.net>
**
** Started on  Sat Jul 09 18:23:52 2016 drozdz_b
** Last update Tue Jul 12 17:37:19 2016 drozdz_b
*/

#include "client/graphic.h"
#include "foreach.h"

void		graph_game_loop(t_window *win, t_graph_item *player)
{
  SDL_Event	ev;
  t_game_map *map;
  t_map *obj;
  
  obj = graph_create_decor(win->renderer);
  map = new(t_game_map);
  printf("ret = %d\n", map_from_file(map, "map/1.map", obj));
  printf("map h = %lu, w = %lu\n", map->h, map->w);
  FOREACH(SDL_Texture *, t, map->cells)
    printf("obj : val=%p\n", t);
  SDL_RenderClear(win->renderer);
  win->size_map.x = map->w;
  win->size_map.y = map->h;
  graph_display_player(win, player);
  while(!SDL_PollEvent(&ev));
  while (ev.type != SDL_QUIT)
    {
      if (ev.type != SDL_KEYDOWN)
	    { 
	       if(ev.key.keysym.sym==SDLK_DOWN)
	         graph_item_set_pos(player, player->pos.x, player->pos.y - 0.5F);
	       else if (ev.key.keysym.sym==SDLK_UP)
  	       graph_item_set_pos(player, player->pos.x, player->pos.y + 0.5F);
	       else if (ev.key.keysym.sym==SDLK_LEFT)
	          graph_item_set_pos(player, player->pos.x - 0.5F, player->pos.y);
	       else if (ev.key.keysym.sym==SDLK_RIGHT)	  
	        graph_item_set_pos(player, player->pos.x + 0.5F, player->pos.y);
	    }
      SDL_RenderClear(win->renderer);
      graph_display_map(win, map, player);
      graph_display_player(win, player);
        SDL_RenderPresent(win->renderer);
      while(!SDL_PollEvent(&ev));
    }
}

float		graph_calc_scroll(t_graph_item *player, t_window *win)
{
  float a;
  

    a = player->view.y / 2 + 0.5F; 
  return (a);  
}

float		graph_calc_scroll_x(t_graph_item *player, t_window *win)
{
  float a;

    a = player->view.x / 4 + 0.25F; 
  return (a);
}

void		graph_display_player(t_window *win, t_graph_item *item)
{
  SDL_Rect	rect;
  float x;
  float y;

  x = graph_calc_scroll_x(item, win) * item->size.x;
  y = win->size_screen.y - graph_calc_scroll(item, win) * item->size.y; 
  rect.x = x;
  rect.y = y;
  rect.w = item->size.x;
  rect.h = item->size.y;   
  SDL_RenderCopy(win->renderer, item->texture, NULL, &rect);
}
