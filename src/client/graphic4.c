#include "client/graphic.h"

/*t_graph_item	graph_create_player(t_window *win, SDL_Texture *texture, int zindex)
{
  t_graph_item	item;

  item.pos.x = 0;
  item.size.x = 64;
  item.size.y = item.size.x;
  //item.pos.y = ((float)win->size_screen.y - item.size.y) / 2 / item.size.y;
  item.pos.y = 1;
  item.view.x = ((float)win->size_screen.x) / item.size.x;
  item.view.y = ((float)win->size_screen.y) / item.size.y;
  item.texture = texture;
  item.zindex = zindex;
  return (item);
}*/

void    display_texture(t_window *win, SDL_Texture *texture, float x, float y)
{
    SDL_Rect rect;

    rect.w = 64;
    rect.h = 64;
    rect.x = x * 64;
    rect.y = win->size_screen.y - y * 64 - 64;
    SDL_RenderCopy(win->renderer, texture, NULL, &rect);
}

t_vector2d		calc_scroll_map_h(t_graph_item *player, t_window *win)
{
  t_vector2d a;
    a.x = player->pos.y - player->view.y / 2;
    a.y = player->pos.y + player->view.y / 2;

  return (a);
}

t_vector2d		calc_scroll_map_w(t_graph_item *player, t_window *win)
{
  t_vector2d a;


    a.x = player->pos.x - player->view.x / 4;
    a.y = player->pos.x + player->view.x / 4 * 3;
  return (a);
}

void graph_display_map(t_window *win, t_game_map *map, t_graph_item *player)
{
    float  i;
    float  j;
    t_vector2d v1;
    t_vector2d v2;
    t_graph_item item;

    SDL_Texture* texture;

    v1 = calc_scroll_map_h(player, win);
    v2 = calc_scroll_map_w(player, win);
    i = v2.x;
    j = v1.x;
    while (j < v1.y)
    {
        while (i < v2.y)
        {
            texture = VGETP(SDL_Texture*, map->cells, (int)j * map->w + (int)i);
            //printf("texture %p, i = %lu, j = %lu case = %lu\n", texture, i, j, j* w + i);
            if (texture != (void *)-1 && texture != NULL)
            {
                display_texture(win, texture, i - v2.x, v1.y - j);
            }
            ++i;
        }
        i = 0;
        ++j;
    }
}
