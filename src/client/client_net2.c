/*
** client_net2.c for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Wed Jul 13 17:11:37 2016 Loïc GIGOMAS
** Last update Wed Jul 13 17:11:50 2016 Loïc GIGOMAS
*/

#include <string.h>
#include "client/client_net.h"
#include "client/cmd.h"

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

  if (writev(s->cli->socket, s->io, s->iovcnt) == -1)
    return (-1);
  for (i = 0; i < s->iovcnt; ++i)
    free(s->io[i].iov_base);
  s->iovcnt = 0;
  FD_CLR(s->cli->socket, &s->writefd);
  return (0);
}

static int	com_unknown(t_splited *str, t_descr *descr)
{
  (void) str;
  (void) descr;
  return (0);
}

static int	comp_str(const void *a, const void *b)
{
  const char	*_a = a;
  const char	*_b = b;

  if (!a || !b)
    return (-1);
  return (strcmp(_a, _b));
}

int	add_commands(t_descr *s, int (*finish)(t_splited *, t_descr *))
{
  if ((s->commands = new(t_map, &comp_str)) == NULL ||
      map_add(s->commands, "ID", &com_id) != MAP_NOERR ||
      map_add(s->commands, "MAP", &com_map) != MAP_NOERR ||
      map_add(s->commands, "COIN", &com_coin) != MAP_NOERR ||
      map_add(s->commands, "START", &com_start) != MAP_NOERR ||
      map_add(s->commands, "PLAYER", &com_player) != MAP_NOERR ||
      map_add(s->commands, "FINISH", finish) != MAP_NOERR)
    {
      fprintf(stderr, "Error.\n");
      return (-1);
    }
  s->commands->defVal = &com_unknown;
  return (0);
}
