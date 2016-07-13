#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "client/graphic.h"
#include "client/client_net.h"
#include "vector.h"
#include "tcpnetc.h"
#include "get_opt.h"
#include "thread.h"

int		main(int ac, char **av)
{
  t_descr	des;
  t_graph_item	*player;
  SDL_Rect	rect;
  int		ret;
  t_tcpnetc *cli;
  t_getopt *opt;
  int port;
  char *host;
  t_thread *th;

  if ((opt = new(t_getopt)) == NULL
       || opt_register(opt, 'p', INT, MANDATORY) != OPT_NOERR
       || opt_register(opt, 'h', PCHAR, MANDATORY) != OPT_NOERR)
    return (84);
  if (opt_parse_params(opt, ac, av) != OPT_NOERR
      || opt_getvar(opt, 'p', &port) != OPT_NOERR
      || opt_getvar(opt, 'h', &host) != OPT_NOERR)
        return (84);
  if (!(cli = new(t_tcpnetc, host, port)))
    return (84);;
 
  memset(&des, 0, sizeof(des));
  graph_init();
  des.obj = graph_create_decor(win->renderer);
  ret = graph_create_window(&des.win, (SDL_Rect)
			    {MAP_WIDTH, MAP_HEIGH, SCREEN_WIDTH, SCREEN_HEIGHT}, TILE_SIZE);
  rect.x = 0;
  rect.y = 0;
  rect.w = 64;
  rect.h = 64;
  des.cli = cli;
  th = new(t_thread, net_routine, &des);
  if(ret >= 0)
    {
      graph_game_loop(&des.win, des);
      SDL_DestroyTexture(player->texture);
      SDL_DestroyRenderer(des.win.renderer);
      SDL_DestroyWindow(des.win.window);
    }
    else
    {
      fprintf(stderr,"Erreur de création de la fenêtre: %s\n", SDL_GetError());
    }
  SDL_Quit();
  return 0;
}
