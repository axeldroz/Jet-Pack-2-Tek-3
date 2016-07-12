/*
** player_phys.c for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Tue Jul 12 19:39:49 2016 Loïc GIGOMAS
** Last update Tue Jul 12 19:51:10 2016 Loïc GIGOMAS
*/

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
  if (p->entity->y >= 0 && p->entity->y <= s->game.map->h - 1)
    p->entity->y += p->entity->speed_y * time;
  if (p->entity->y <= 0)
    {
      p->entity->speed_y = p->entity->speed_y / 1.2;
      p->entity->y = 0;
    }
  else if (p->entity->y >= s->game.map->h - 1)
    {
      p->entity->speed_y = 0;
      p->entity->y = s->game.map->h - 1;
    }
  p->entity->x += p->entity->speed_x * time;
  if (p->entity->x >= s->game.map->w)
    return (GAME_FINISHED);
  return (GAME_RUNNING);
}

int	check_colliders(t_server *s, t_player *p, char *b, size_t *o)
{
  size_t	c;
  t_pair	*pa;
  t_pair	*buf;

  if ((pa = new(t_pair)) == NULL || (buf = new(t_pair)) == NULL)
    return (GAME_ERROR);
  pa->first = s;
  pa->second = p;
  buf->first = b;
  buf->second = o;
  if ((c = get_cell(s, p, 0)) < s->game.map->cells->size)
    VGETP(t_cell_f, s->game.map->cells, c)
      (pa, &s->game.map->cells->array[c], buf, c);
  if ((c = get_cell(s, p, 1)) < s->game.map->cells->size)
    VGETP(t_cell_f, s->game.map->cells, c)
      (pa, &s->game.map->cells->array[c], buf, c);
  if ((c = get_cell(s, p, 2)) < s->game.map->cells->size)
    VGETP(t_cell_f, s->game.map->cells, c)
      (pa, &s->game.map->cells->array[c], buf, c);
  if ((c = get_cell(s, p, 3)) < s->game.map->cells->size)
    VGETP(t_cell_f, s->game.map->cells, c)
      (pa, &s->game.map->cells->array[c], buf, c);
  delete(pa);
  delete(buf);
  return (GAME_RUNNING);
}

/*
** On centre en x, et on regarde a droite ou a gauche
*/
static int	get_cx(t_player *p, int corner)
{
  return (p->entity->x + (p->entity->width / 2.0) +
	  (corner == 0 || corner == 1 ?
	   -((p->entity->width / 2.0) * 0.99):
	   ((p->entity->width / 2.0) * 0.99)));
}

/*
** On centre en y, et on regarde en haut ou en bas
*/
static int	get_cy(t_player *p, int corner)
{
  return (p->entity->y + (p->entity->height / 2.0) +
	  (corner == 0 || corner == 3 ?
	   -((p->entity->height / 2.0) * 0.99):
	   ((p->entity->height / 2.0) * 0.99)));
}

/*
** Il faut convertir la position du joueur en position de map (Y inversé)
*/
size_t	get_cell(t_server *s, t_player *p, int c)
{
  return ((s->game.map->h - get_cy(p, c) - 1.0) * s->game.map->w + get_cx(p, c));
}
