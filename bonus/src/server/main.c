/*
** main.c for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Tue Jul 12 19:38:01 2016 Loïc GIGOMAS
** Last update Wed Jul 13 16:42:47 2016 Loïc GIGOMAS
*/

#include <stdio.h>
#include <signal.h>
#include "tcpnets.h"
#include "server.h"
#include "server/player.h"
#include "get_opt.h"

static int	add_commands(t_server *s)
{
  if (map_add(s->commands, "ID", &com_id) != MAP_NOERR ||
      map_add(s->commands, "MAP", &com_map) != MAP_NOERR ||
      map_add(s->commands, "READY", &com_ready) != MAP_NOERR ||
      map_add(s->commands, "FIRE", &com_fire) != MAP_NOERR)
    {
      fprintf(stderr, "Error\n");
      return (-1);
    }
  return (0);
}

static int	char_cmp(const void *a, const void *b)
{
  return (a - b);
}

static int	get_map(t_server *s, char *file)
{
  t_map		*known;

  known = new(t_map, &char_cmp);
  map_add(known, (void *)((long)'_'), &cell_empty);
  map_add(known, (void *)((long)'e'), &cell_elec);
  map_add(known, (void *)((long)'c'), &cell_coin);
  map_add(known, (void *)((long)'j'), &cell_jump);
  if (map_from_file(s->game.origin, file, known) == -1 ||
      s->game.origin->cells->size == 0 || s->game.origin->full_str == NULL)
    {
      fprintf(stderr, "Invalid map \"%s\"\n", file);
      return (-1);
    }
  if ((s->game.map->full_str = strdup(s->game.origin->full_str)) == NULL)
    return (-1);
  s->game.map->str_size = s->game.origin->str_size;
  s->game.map->w = s->game.origin->w;
  s->game.map->h = s->game.origin->h;
  return (0);
}

static int	get_args(t_server **s, int ac, char **av)
{
  t_getopt	*opt;
  char		*map;
  int		port;
  float		gravity;

  if ((opt = new(t_getopt)) == NULL ||
      opt_register(opt, 'p', INT, MANDATORY) != OPT_NOERR ||
      opt_register(opt, 'g', FLOAT, MANDATORY) != OPT_NOERR ||
      opt_register(opt, 'm', PCHAR, MANDATORY) != OPT_NOERR)
    return (-1);
  if (opt_parse_params(opt, ac, av) != OPT_NOERR ||
      opt_getvar(opt, 'p', &port) != OPT_NOERR ||
      opt_getvar(opt, 'g', &gravity) != OPT_NOERR ||
      opt_getvar(opt, 'm', &map) != OPT_NOERR)
    {
      *s = (void *)-1;
      fprintf(stderr, "Invalid arguments\n");
      return (-1);
    }
  if ((*s = new(t_server, port, gravity)) == NULL)
    return (-1);
  return (get_map(*s, map));
}

int		main(int ac, char **av)
{
  t_server	*s;
  void		(*sig_fun)(int);

  sig_fun = ({
      void sig_fun(__attribute__((unused))int sig)
      {
	exit(0);
      }
      &sig_fun;
    });
  signal(SIGINT, sig_fun);
  signal(SIGQUIT, sig_fun);
  signal(SIGPIPE, SIG_IGN);
  if (get_args(&s, ac, av) == 0 && add_commands(s) == 0)
    {
      if (select_loop(s) == -1)
	{
	  fprintf(stderr, "Error\n");
	  return (84);
	}
      return (0);
    }
  if (!s)
    fprintf(stderr, "Error\n");
  return (84);
}
