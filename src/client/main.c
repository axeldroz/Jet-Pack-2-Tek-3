/*
** main.c for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Wed Jul 13 17:12:02 2016 Loïc GIGOMAS
** Last update Wed Jul 13 17:12:17 2016 Loïc GIGOMAS
*/

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

static t_descr	*init_descr(int port, char *host)
{
  t_descr	*des;

  if (!(des = malloc(sizeof(*des))) || !(memset(des, 0, sizeof(*des)))
      || !(des->cli = new(t_tcpnetc, host, port))
      || (des->map = new(t_game_map)) == NULL
      || (des->players = new(t_map, &comp_id)) == NULL
      /*|| graph_init() == -1*/)
    return (NULL);
  if (graph_create_window(&des->win, (SDL_Rect){MAP_WIDTH, MAP_HEIGH,
	  SCREEN_WIDTH, SCREEN_HEIGHT}, TILE_SIZE) < 0)
    {
      fprintf(stderr, "Erreur création fenêtre: %s\n", SDL_GetError());
      free(des);
      return (NULL);
    }
  if ((des->obj = graph_create_decor(des->win.renderer)) == NULL)
    {
      free(des);
      return (NULL);
    }
  des->run = 1;
  cmutex_init(&des->lock);
  cmutex_lock(&des->lock);
  return (des);
}

int		main(int ac, char **av)
{
  t_descr	*des;
  t_getopt	*opt;
  int		port;
  char		*host;
  t_thread	*th;

  if ((opt = new(t_getopt)) == NULL
      || opt_register(opt, 'p', INT, MANDATORY) != OPT_NOERR
      || opt_register(opt, 'h', PCHAR, MANDATORY) != OPT_NOERR)
    return (84);
  if (opt_parse_params(opt, ac, av) != OPT_NOERR
      || opt_getvar(opt, 'p', &port) != OPT_NOERR
      || opt_getvar(opt, 'h', &host) != OPT_NOERR)
    return (84);
  if ((des = init_descr(port, host)) == NULL)
    return (84);
  th = new(t_thread, net_routine, des);
  cmutex_wait(&des->lock);
  graph_game_loop(&des->win, des);
  //SDL_DestroyRenderer(des->win.renderer);
  //SDL_DestroyWindow(des->win.window);
  //delete(th);
  //free(des);
  //SDL_Quit();
  return 0;
}
