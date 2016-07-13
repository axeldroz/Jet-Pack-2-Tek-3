/*
** map.h for jetpack2T3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Thu Jul  7 11:15:04 2016 Loïc GIGOMAS
** Last update Thu Jul  7 11:15:05 2016 Loïc GIGOMAS
*/

#ifndef MAP_H_
# define MAP_H_

/*
** Malloc/free, size_t
*/
# include <stdlib.h>

/*
** new/delete
*/
# include "new.h"

/*
** pair
*/
# include "pair.h"

/*
** Define de configuration
*/
# define MAP_MAX_DIFF	(8)

/*
** Defines de retours.
*/
# define MAP_ARGS	(-1)
# define MAP_FUNC	(-2)
# define MAP_NOMORE	(-3)
# define MAP_NOERR	(0)

/*
** Ce n'est pas une fonction car le type n'est pas récupérable autrement.
*/
# define MGET(type, map, key) ((type)(map_get(map, key)))

/*
** Utilisé pour le new (initialisation).
** La fonction de comparaison est obligatoire, même si la map
** est une unordered map. (nécéssaire pour check keys)
*/
typedef struct	s_map_init
{
  int		(*compar)(const void *a, const void *b);
  size_t	size;
  void		*defVal;
}		t_map_init;

typedef struct	s_map
{
  t_object	__obj__;
  size_t	size;
  t_pair	**array;
  size_t	alloc;
  int		(*compar)(const void *a, const void*b);
  void		*defVal;
}		t_map;

t_map	*t_map_new(t_map_init var);
void	map_del(void *ptr);
size_t	map_size(t_map *m);
int	map_add(t_map *m, void *key, void *value);
int	map_remove(t_map *m, void *key);
void	*map_get(t_map *m, void *key);

#endif /* !MAP_H_ */
