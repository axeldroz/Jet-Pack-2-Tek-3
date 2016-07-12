#include <SDL2/SDL.h>
//#include <SDL/SDL_image.h>

#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "client/graphic.h"
#include "vector.h"
#include "tcpnetc.h"

int		main(int ac, char **av)
{
  t_window	win;
  t_graph_item	player;
  SDL_Rect	rect;
  int		ret;
  t_vector	*vect;
  t_tcpnetc *cli;


  vect = new(t_vector);
  graph_init();
  ret = graph_create_window(&win, (SDL_Rect)
			  {MAP_WIDTH, MAP_HEIGH, SCREEN_WIDTH, SCREEN_HEIGHT}, TILE_SIZE);
  graph_add_texture(vect, win.renderer, "sprites/rocketmouse_run04@2x.png");
  rect.x = 0;
  rect.y = 0;
  rect.w = 64;
  rect.h = 64;
  player = graph_create_player(&win, VGETP(SDL_Texture*, vect, 0), 1);
  if(ret >= 0)
    {
      graph_game_loop(&win, &player);
      SDL_DestroyTexture(player.texture);
      SDL_DestroyRenderer(win.renderer);
      SDL_DestroyWindow(win.window);
    }
    else
    {
      fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
    }
  SDL_Quit();
  return 0;
}
