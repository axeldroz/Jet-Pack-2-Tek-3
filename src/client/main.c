#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "client/graphic.h"
#include "client/client_net.h"
#include "vector.h"
#include "tcpnetc.h"
#include "get_opt.h"
#include "thread.h"

static int	comp_id(const void *a, const void *b)
{
  return (a - b);
}

int		main(int ac, char **av)
{
  t_descr	*des;
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
  if (!(des = malloc(sizeof(*des))) || !(cli = new(t_tcpnetc, host, port)))
    return (84);
  memset(des, 0, sizeof(*des));
  des->map = new(t_game_map);
  des->players = new(t_map, &comp_id);
  des->cli = cli;
  des->run = 1;
  cmutex_init(&des->lock);
  cmutex_lock(&des->lock);
  graph_init();
  ret = graph_create_window(&des->win, (SDL_Rect)
			    {MAP_WIDTH, MAP_HEIGH, SCREEN_WIDTH, SCREEN_HEIGHT}, TILE_SIZE);
  des->obj = graph_create_decor(des->win.renderer);
  rect.x = 0;
  rect.y = 0;
  rect.w = 64;
  rect.h = 64;
  if(ret >= 0)
    {
      th = new(t_thread, net_routine, des);
      cmutex_wait(&des->lock);
      printf("UNLOCKED\n");
      graph_game_loop(&des->win, des);
      SDL_DestroyRenderer(des->win.renderer);
      SDL_DestroyWindow(des->win.window);
      delete(th);
    }
    else
    {
      fprintf(stderr,"Erreur de création de la fenêtre: %s\n", SDL_GetError());
    }
  free(des);
  SDL_Quit();
  return 0;
}
