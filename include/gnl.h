/*
** gnl.h for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Sat Jul  9 19:22:41 2016 Loïc GIGOMAS
** Last update Sat Jul  9 19:22:41 2016 Loïc GIGOMAS
*/

#ifndef GNL_H_
# define GNL_H_

typedef struct	s_gnl
{
  long		_buff_size;
  char		*_buff;
}		t_gnl;

int	get_next_line(t_gnl *g, int fd, char **ret);

#endif /* !GNL_H_ */
