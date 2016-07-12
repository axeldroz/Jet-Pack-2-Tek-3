#include "server/player.h"

int	update_pos(t_server *s, t_player *p, double time)
{
  p->entity->speed_x = p->entity->accel_x;
  p->entity->speed_y -= p->entity->accel_y * 2.0 *
    (p->fire ? 1.0 : -1.0) / p->entity->weight * time;
  if (p->entity->speed_y <= -p->entity->speed_max)
    p->entity->speed_y = -p->entity->speed_max;
  if (p->entity->speed_y >= -p->entity->accel_y)
    p->entity->speed_y = -p->entity->accel_y;
  if (p->entity->y <= 0)
    {
      if (!p->fire)
	p->entity->speed_y = 0;
      p->entity->y = 0;
    }
  else if (p->entity->y >= s->game.map->h - 1)
    {
      if (p->fire)
	p->entity->speed_y = 0;
      p->entity->y = s->game.map->h - 1;
    }
  if (p->entity->y >= 0 && p->entity->y <= s->game.map->h - 1)
    p->entity->y += p->entity->speed_y * time;
  p->entity->x += p->entity->speed_x * time;
  if (p->entity->x >= s->game.map->w)
    return (GAME_FINISHED);
  return (GAME_RUNNING);
}
