/*
** game_map.c for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jul  9 18:17:56 2016 Loïc GIGOMAS
** Last update Wed Jul 13 10:43:35 2016 Loïc GIGOMAS
*/

#ifdef _WIN32
# include <io.h>
#endif
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "game_map.h"
#include "foreach.h"
#include "gnl.h"

static int	push_line(t_game_map *m, char *line, t_map *known)
{
  size_t	i;
  void		*elem;

  for (i = 0; line[i]; ++i)
    {
      if ((elem = MGET(void *, known, (void *)((long)line[i]))) == NULL)
	return (-1);
      vector_push_back(m->cells, elem);
    }
  if (m->w == 0)
    m->w = i;
  else
    if (m->w != i)
      return (-1);
  if ((m->full_str = realloc(m->full_str, m->str_size + i + 1)) == NULL)
    return (-1);
  strncpy(&m->full_str[m->str_size], line, i);
  m->str_size += i;
  m->full_str[m->str_size] = 0;
  return (1);
}

int		map_from_file(t_game_map *m, char *file, t_map *known)
{
  int		fd;
  char		*line;
  int		ret;
  t_gnl		gnl;

  gnl = (t_gnl){0, NULL};
  if ((fd = OPEN(file, READONLY)) == -1)
    return (-1);
  for (line = NULL; (ret = get_next_line(&gnl, fd, &line)) < 2; ++m->h)
    if (ret == 0 || ret == 1)
      {
	if (push_line(m, line, known) == -1)
	  {
	    CLOSE(fd);
	    free(line);
	    free(gnl._buff);
	    return (-1);
	  }
	free(line);
      }
  CLOSE(fd);
  if (gnl._buff && ++m->h && push_line(m, gnl._buff, known) == -1)
    ret = -1;
  free(gnl._buff);
  return (ret);
}

int		map_from_split(t_game_map *m, t_splited *s, t_map *known)
{
  size_t	i;
  char		*l;
  void		*elem;

  if (s->words->size < 4 || (l = VGETP(char *, s->words, 0)) == NULL ||
      strcmp(l, "MAP") != 0)
    return (-1);
  if ((l = VGETP(char *, s->words, 1)) == NULL || (m->w = atoi(l)) <= 0 ||
      (l = VGETP(char *, s->words, 2)) == NULL || (m->h = atoi(l)) <= 0 ||
      (l = VGETP(char *, s->words, 3)) == NULL || (m->w * m->h) != strlen(l))
    return (-1);
  for (i = 0; l[i]; ++i)
    {
      if ((elem = MGET(void *, known, (void *)((long)l[i]))) == NULL)
	return (-1);
      vector_push_back(m->cells, elem);
    }
  return (0);
}

void		gma_del(void *ptr)
{
  t_game_map	*m;

  if (!ptr)
    return ;
  m = ptr;
  delete(m->cells);
  free(m->full_str);
}

t_game_map	*t_game_map_new(__attribute__((unused))t_game_map_init var)
{
  t_game_map	*m;

  if ((m = (t_game_map *)new(t_object, sizeof(t_game_map), &gma_del)) == NULL
      || (m->cells = new(t_vector)) == NULL)
    return (NULL);
  return (m);
}
