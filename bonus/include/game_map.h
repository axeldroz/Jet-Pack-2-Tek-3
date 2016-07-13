/*
** game_map.h for jetpack2T3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Thu Jul  7 11:14:57 2016 Loïc GIGOMAS
** Last update Sat Jul  9 19:34:55 2016 Loïc GIGOMAS
*/

#ifndef GAME_MAP_H_
# define GAME_MAP_H_

# include "new.h"
# include "vector.h"
# include "map.h"
# include "splited.h"

#ifdef _WIN32
# define OPEN		_open
# define READONLY	_O_RDONLY
# define CLOSE		_close
#elif __linux__
# define OPEN		open
# define READONLY	O_RDONLY
# define CLOSE		close
#endif

typedef struct	s_game_map_init
{
}		t_game_map_init;

typedef struct	s_game_map
{
  t_object	__obj__;
  t_vector	*cells;
  char		*full_str;
  size_t	str_size;
  size_t	w;
  size_t	h;
}		t_game_map;

t_game_map	*t_game_map_new(t_game_map_init var);

int	map_from_file(t_game_map *m, char *file, t_map *known);
int	map_from_split(t_game_map *m, t_splited *s, t_map *known);

#endif /* !GAME_MAP_H_ */
