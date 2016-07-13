/*
** graphic.h for graphic in /home/drozdz_b/Documents/testSDL2/test1
**
** Made by drozdz_b
** Login   <drozdz_b@epitech.net>
**
** Started on  Sat Jul 09 10:09:36 2016 drozdz_b
** Last update Wed Jul 13 23:28:49 2016 Loïc GIGOMAS
*/

#ifndef GRAPHIC_H_
#define GRAPHIC_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdio.h>

#include "vector.h"
#include "map.h"
#include "game_map.h"

#define SCREEN_WIDTH 1800
#define SCREEN_HEIGHT 900
#define TILE_SIZE 64

typedef struct s_descr	t_descr;

typedef struct	s_vect_int
{
  int		x;
  int		y;
}		t_vect_int;

typedef struct	s_vector2d
{
  float		x;
  float		y;
}		t_vector2d;

typedef struct	s_window
{
  SDL_Window	*window;
  SDL_Renderer	*renderer;
  t_vect_int	size_screen;
  t_vect_int	size_map;
  int		size_tile;
}		t_window;

typedef struct	s_graph_item
{
  SDL_Texture	*texture;
  t_vector2d	pos;
  t_vector2d	size;
  t_vector2d	view;
  int		coins;
  int		zindex;
}		t_graph_item;

typedef struct	s_cond
{
  float		i;
  float		i2;
  float		j;
  float		j2;
  float		w;
  float		h;
}		t_cond;

/*
** graphic.c
*/
int	graph_init();
int	graph_create_window(t_window *win, SDL_Rect rect, int size_tile);
void	graph_item_set_pos(t_graph_item *item, float x, float y);
int	graph_add_texture(t_vector *vect, SDL_Renderer *renderer,
				  const char *path);
t_graph_item	*graph_create_player(t_window *win, SDL_Texture *texture,
				     int zindex);

/*
** graphic2.c
*/
t_map	*graph_create_decor(SDL_Renderer *renderer);
int	graph_add_texture_map(t_map *map, SDL_Renderer *renderer,
			      long key, const char *path);
void	graph_display(SDL_Renderer *renderer, t_graph_item *item);
/*
** graphic3.c
*/
void	graph_game_loop(t_window *win, t_descr *descr);
void	graph_display_player(t_window *win, t_graph_item *item);

void	graph_display_map(t_descr *descr, t_game_map *map,
			  t_graph_item *player);

# include "client/client_net.h"

#endif
