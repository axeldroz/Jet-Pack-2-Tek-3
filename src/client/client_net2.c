#include "client_net.h"

int		write_iov(t_descr *s, char *msg)
{
  size_t	len;
  char		*m;

  if (!msg || s->iovcnt >= 15)
    return (0);
  len = strlen(msg);
  if (len == 0)
    ++len;
  if ((m = malloc(len + (msg[len - 1] == '\n' ? 1 : 2))) == NULL)
    return (-1);
  m = strcpy(m, msg);
  if (m[len - 1] != '\n')
    {
      m = strcat(m, "\n");
      ++len;
    }
  s->io[s->iovcnt].iov_base = m;
  s->io[s->iovcnt].iov_len = len;
  ++s->iovcnt;
  FD_SET(s->cli->socket, &s->writefd);
  return (0);
}

int	iov_send(t_descr *s)
{
  int	i;

  if (writev(s->fd, s->io, s->iovcnt) == -1)
    return (-1);
  for (i = 0; i < s->iovcnt; ++i)
    free(s->io[i].iov_base);
  s->iovcnt = 0;
  FD_CLR(s->cli->socket, &s->writefd);
  return (0);
}

int	com_id(t_splited *str, t_descr *descr)
{
  if (str->words->size >= 2)
    descr->id = atoi(VGET(char *, str->word, 1));
  return (0);
}

int	com_map(t_splited *str, t_descr *descr)
{
  map_from_splited(descr->map, str, desc->obj);
  return (0);
}

int	com_player(t_splited *str, t_descr *descr)
{
  t_graph_item *player;  
  long id;
  
  id = atoi(VGET(char *, str->word, 1))
  player = MGET(t_graph_item *, descr->players, id);
  if (player == NULL)
  {
    player = graph_create_player(descr->win, MGET(SDL_Surface *, obj, 'p'),
      (descr->id == id) ? 1 : 0));
    map_add(descr->players, (void *)id, players);
  }
  player->pos.x = atof(VGET(char *, str->word, 2));
  player->pos.y = atof(VGET(char *, str->word, 3));
  
  return (0);
}

int	add_commands(t_server *s)
{
  if (map_add(s->commands, "ID", &com_id) != MAP_NOERR ||
      map_add(s->commands, "MAP", &com_map) != MAP_NOERR ||
      map_add(s->commands, "START", &com_ready) != MAP_NOERR ||
      map_add(s->commands, "PLAYER", &com_player) != MAP_NOERR)
    {
      fprintf(stderr, "Error\n");
      return (-1);
    }
  return (0);
}