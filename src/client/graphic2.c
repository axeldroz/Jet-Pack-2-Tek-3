/*
** graphic2.c for graphic2 in /home/drozdz_b/Documents/testSDL2/test1
**
** Made by drozdz_b
** Login   <drozdz_b@epitech.net>
**
** Started on  Sat Jul 09 16:01:34 2016 drozdz_b
** Last update Wed Jul 13 12:47:33 2016 Loïc GIGOMAS
*/

#include "client/graphic.h"

t_vector	*graph_create_players_text(t_window *win, t_vector *textures)
{
  t_vector	*players;

  players = new(t_vector);
  graph_add_texture(players, win->renderer, "sprites/rocketmouse_run04@2x.png");
  return (players);
}

static int	charcomp(const void *a, const void *b)
{
  return (a - b);
}

t_map		*graph_create_decor(SDL_Renderer *renderer)
{
  t_map		*map;

  map = new(t_map, &charcomp);
  graph_add_texture_map(map, renderer, (long)'e', "sprites/object_grenade_red.png");
  graph_add_texture_map(map, renderer, (long)'c', "sprites/powerup_banana.png");
  graph_add_texture_map(map, renderer, (long)'p', "sprites/rocketmouse_run04@2x.png");
  map_add(map, (void*)((long)'_'), (void *)-1);
  return (map);
}

int		graph_add_texture_map(t_map *map, SDL_Renderer *renderer,
				      long key, const char *path)
{
  SDL_Texture*	texture;

  texture = IMG_LoadTexture(renderer, path);
  if (texture == NULL)
    {
      fprintf(stderr, "Fail IMG_LoadTexture() : %s\n", SDL_GetError());
      return (-1);
    }
  map_add(map, (void *)key, texture);
  return (0);
}

void		graph_display(SDL_Renderer *renderer, t_graph_item *item)
{
  SDL_Rect rect;

  rect.x = item->pos.x * item->size.x;
  rect.y = item->pos.y * item->size.y;
  rect.w = item->size.x;
  rect.h = item->size.y;
  SDL_RenderCopy(renderer, item->texture, NULL, &rect);
  SDL_RenderPresent(renderer);
}
