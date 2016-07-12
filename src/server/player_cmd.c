#include <stdlib.h>
#include <stdio.h>
#include "server.h"
#include "server/player.h"
#include "splited.h"

int	com_id(NSD t_splited *str, t_player *p, t_server *s)
{
  char	buff[16];

  sprintf(buff, "ID %d\n", p->fd);
  if (write_iov(s, p, buff) == -1)
    return (-1);
  printf("CMD : ID (replied : [ID %d\\n])\n", p->fd);
  if (!IS_READY(p) && (p->ready |= RCV_ID) && IS_READY(p))
    ++s->game.n_ready;
  return (0);
}

int	com_map(NSD t_splited *str, t_player *p, t_server *s)
{
  char	*buff;

  if ((buff = malloc(30 + s->game.map->str_size)) == NULL)
    return (-1);
  sprintf(buff, "MAP %lu %lu %s\n", s->game.map->w, s->game.map->h, s->game.map->full_str);
  if (write_iov(s, p, buff) == -1)
    {
      free(buff);
      return (-1);
    }
  printf("CMD : MAP (replied : [MAP %lu %lu %c...\\n])\n",
	 s->game.map->w, s->game.map->h, *s->game.map->full_str);
  free(buff);
  if (!IS_READY(p) && (p->ready |= RCV_MAP) && IS_READY(p))
    ++s->game.n_ready;
  return (0);
}

int	com_ready(NSD t_splited *str, t_player *p, t_server *s)
{
  printf("CMD : READY\n");
  if (!IS_READY(p) && (p->ready |= RCV_READY) && IS_READY(p))
    ++s->game.n_ready;
  return (0);
}

int	com_fire(t_splited *str, t_player *p, NSD t_server *s)
{
  char	*word;

  if (str->words->size < 2 || (word = VGETP(char *, str->words, 1)) == NULL)
    return (0);
  p->fire = atoi(word);
  if (p->fire < 0)
    p->fire = 0;
  else if (p->fire > 1)
    p->fire = 1;
  printf("CMD : FIRE %s (new state = %d)\n", word, p->fire);
  return (0);
}
