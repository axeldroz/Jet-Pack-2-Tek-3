/*
** graphic3.c for graphic3 in /home/drozdz_b/Documents/testSDL2/test1
**
** Made by drozdz_b
** Login   <drozdz_b@epitech.net>
**
** Started on  Sat Jul 09 18:23:52 2016 drozdz_b
** Last update Wed Jul 13 17:17:55 2016 Loïc GIGOMAS
*/

#include "client/graphic.h"
#include "foreach.h"
#include "client/client_net.h"

void		graph_disp_all(t_window *win, t_descr *descr)
{
  t_graph_item	*player;

  if ((player = MGET(t_graph_item*, descr->players,
		     (void *)((long)descr->id))) == NULL)
    return ;
  graph_display_map(descr, descr->map, player, descr->players);
  graph_display_player(win, player);
}

void		graph_game_loop(t_window *win, t_descr *descr)
{
  SDL_Event	ev;
  int		fire;

  fire = 0;
  while (descr->run)
    {
      cmutex_lock(&descr->lock);
      SDL_RenderClear(win->renderer);
      graph_disp_all(win, descr);
      SDL_RenderPresent(win->renderer);
      cmutex_unlock(&descr->lock);
      if (SDL_PollEvent(&ev))
    	{
	  if (ev.type == SDL_QUIT)
	    descr->run = 0;
	  if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_SPACE
	      && !fire && ((fire = 1) == 1))
	    write_iov(descr, "FIRE 1");
	 if (ev.type == SDL_KEYUP && ev.key.keysym.sym == SDLK_SPACE
	      && fire && ((fire = 0) == 0))
	    write_iov(descr, "FIRE 0");
	}
        usleep(10000);
    }
 
}

void		graph_display_player(t_window *win, t_graph_item *item)
{
  SDL_Rect	rect;
  float		x;
  float		y;

  x = (item->view.x / 4) * item->size.x;
  y = (item->view.y / 2) * item->size.y;
  rect.x = x;
  rect.y = y;
  rect.w = item->size.x;
  rect.h = item->size.y;
  //printf("Player : x=%f y=%f\n", item->pos.x, item->pos.y);
  SDL_RenderCopy(win->renderer, item->texture, NULL, &rect);
}
