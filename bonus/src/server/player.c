/*
** player.c for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Tue Jul 12 19:40:15 2016 Loïc GIGOMAS
** Last update Wed Jul 13 16:41:01 2016 Loïc GIGOMAS
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "server/player.h"

void		pla_del(void *ptr)
{
  int		i;
  t_player	*p;

  if (!ptr)
    return;
  p = ptr;
  close(p->fd);
  delete(p->entity);
  free(p->gnl._buff);
  for (i = 0; i < p->iovcnt; ++i)
    free(p->io[i].iov_base);
}

t_player	*t_player_new(t_player_init var)
{
  t_player	*p;

  if (!var.fd ||
      (p = (t_player *)new(t_object, sizeof(t_player), &pla_del)) == NULL ||
      (p->entity = new(t_entity, var.x, var.y, 5, var.gravity)) == NULL)
    return (NULL);
  p->fd = var.fd;
  return (p);
}

int		add_client(t_server *s)
{
  int		fd;
  t_player	*p;

  if ((fd = accept(s->net->socket, NULL, NULL)) != -1)
    {
      if (s->clients->size == 2)
	{
	  close(fd);
	  return (0);
	}
      if ((p = new(t_player, fd, s->game.gravity,
		   (float)(s->game.map->h / 2.0))) == NULL ||
	  map_add(s->clients, (void *)(&p->fd), p) != MAP_NOERR)
	{
	  return (-1);
	}
      FD_SET(fd, &s->readfds);
      p->entity->speed_y = 5.0;
      if (s->max_fd < fd)
	s->max_fd = fd;
      return (1);
    }
  return (-1);
}

int		write_iov(t_server *s, t_player *p, char *msg)
{
  size_t	len;
  char		*m;

  if (!p || !msg || p->iovcnt >= 15)
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
  p->io[p->iovcnt].iov_base = m;
  p->io[p->iovcnt].iov_len = len;
  ++p->iovcnt;
  FD_SET(p->fd, &s->writefds);
  return (0);
}

int	iov_send(t_server *s, t_player *p)
{
  int	i;

  if (writev(p->fd, p->io, p->iovcnt) == -1)
    return (-1);
  for (i = 0; i < p->iovcnt; ++i)
    free(p->io[i].iov_base);
  p->iovcnt = 0;
  FD_CLR(p->fd, &s->writefds);
  return (0);
}
