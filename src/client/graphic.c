/*
** graphic.c for graphic in /home/drozdz_b/Documents/testSDL2/test1
**
** Made by drozdz_b
** Login   <drozdz_b@epitech.net>
**
** Started on  Sat Jul 09 10:10:09 2016 drozdz_b
** Last update Tue Jul 12 17:32:40 2016 drozdz_b
*/

#include "client/graphic.h"

int	graph_init()
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
      fprintf(stderr, "Fail SDL_Init() : %s\n",
	      SDL_GetError());
      return (-1);
    }
  if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
      fprintf(stderr,"Fail IMG_Init() : %s\n",SDL_GetError());
      SDL_Quit();
      return (-1);
    }
  return (0);
}

int	graph_create_window(t_window *win, SDL_Rect rect, int size_tile)
{
  win->size_screen.x = rect.w;
  win->size_screen.y = rect.h;
  win->size_map.x = rect.x;
  win->size_map.y = rect.y;
  win->size_tile = size_tile;
  win->window = SDL_CreateWindow("Put a sprite",SDL_WINDOWPOS_UNDEFINED,
				  SDL_WINDOWPOS_UNDEFINED,
				  win->size_screen.x,
				  win->size_screen.y,
				  SDL_WINDOW_SHOWN);
  if (win->window == NULL)
    {
      fprintf(stderr, "Fail SDL_CreateWindow() : %s", SDL_GetError());
      return (-1);
    }
  win->renderer = SDL_CreateRenderer(win->window, -1, SDL_RENDERER_ACCELERATED);
  if (win->renderer == NULL)
    {
      fprintf(stderr, "Fail SDL_CreateRenderer() : %s", SDL_GetError());
      return (-2);
    }
  SDL_SetRenderDrawColor(win->renderer, 255, 0, 0, 255);
  return (0);
}

t_graph_item	graph_create_player(t_window *win, SDL_Texture *texture, int zindex)
{
  t_graph_item	item;

  item.pos.x = 0;
  item.size.x = 64;
  item.size.y = item.size.x;
  item.pos.y = 1;
  item.view.x = ((float)win->size_screen.x) / item.size.x;
  item.view.y = ((float)win->size_screen.y) / item.size.y;
  item.texture = texture;
  item.zindex = zindex;
  return (item);
}

void	graph_item_set_pos(t_graph_item *item, float x, float y)
{
  item->pos.x = x;
  item->pos.y = y;
}

int		graph_add_texture(t_vector *vect, SDL_Renderer *renderer,
				  const char *path)
{
  SDL_Texture*	texture;

  texture = IMG_LoadTexture(renderer, path);
  if (texture == NULL)
    {
      fprintf(stderr, "Fail IMG_LoadTexture() : %s", SDL_GetError());
      return (-1);
    }
  vector_push_back(vect, texture);
  return (0);
}
