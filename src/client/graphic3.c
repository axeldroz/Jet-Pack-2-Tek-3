/*
** graphic3.c for graphic3 in /home/drozdz_b/Documents/testSDL2/test1
**
** Made by drozdz_b
** Login   <drozdz_b@epitech.net>
**
** Started on  Sat Jul 09 18:23:52 2016 drozdz_b
** Last update Wed Jul 13 09:57:00 2016 drozdz_b
*/

#include "client/graphic.h"
#include "foreach.h"
#include "client/client_net.h"

void            graph_disp_all(t_window *win, t_descr *descr)
{
  t_graph_item *player;
  
  player = MGET(t_graph_item*, descr->players, descr->id);
  graph_display_map(win, map, player);

  graph_display_player(win, player);
}

void		graph_game_loop(t_window *win, t_descr *descr)
{
  SDL_Event	ev;

  while (descr->run)
    {
      SDL_RenderClear(win->renderer);
      graph_disp_all(win, descr);
      SDL_RenderPresent(win->renderer);
      if (SDL_PollEvent(&ev))
    	{
        if (ev.type == SDL_QUIT)
           descr->run = 0;
        else
        {
          if(ev.type != SDL_KEYDOWN && ev.key.keysym.sym==SDLK_SPACE)
             write_iov(descr, "FIRE 1");         
          if(ev.type != SDL_KEYUP && ev.key.keysym.sym==SDLK_SPACE)
            write_iov(descr, "FIRE 0");          
	      }
      }
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
