/*
** client_net.c for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Wed Jul 13 17:15:19 2016 Loïc GIGOMAS
** Last update Wed Jul 13 22:50:11 2016 Loïc GIGOMAS
*/

#include "client/client_net.h"
#include "tcpnetc.h"
#include "thread.h"

#include "client/select_loop.h"

void		*fct_stop(void *params)
{
  return ((void *)(((t_descr *)params)->run == 0 ? 1L : 0L));
}

void		*fct_write(void *params)
{
  t_descr	*descr;

  descr = (t_descr *)(params);
  return ((void *)(long)iov_send(descr));
}

void		*fct_read(void *params)
{
  int		r;
  char		*str;
  t_splited	*cmp;
  int		first;
  t_descr	*s;

  str = NULL;
  first = 1;
  s = params;
  while ((r = get_next_line(&s->gnl, (first ? s->cli->socket : -1), &str)) < 2)
    {
      if (r == 0 || r == 1)
	{
	  if ((cmp = new(t_splited, str)) == NULL)
	    return ((void *)-1);
	  r = MGET(t_command, s->commands,
		   VGETP(char *, cmp->words, 0))(cmp, s);
	  free(str);
	  delete(cmp);
	  if (r == -1)
	    return ((void *)-1);
	}
      first = 0;
    }
  return ((void *)(r >= 3 ? -1L : 0L));
}

static int	com_finish(t_splited *str, t_descr *descr)
{
  int		id;

  if (str->words->size >= 2)
    {
      id = atoi(VGETP(char *, str->words, 1));
      if (id == descr->id)
	printf("You win !\n");
      else if (id != -1)
	printf("You loose !\n");
      else
	printf("Nobody win.\n");
    }
  descr->run = 0;
  return (0);
}

t_cth_ret	net_routine(t_cth_params params)
{
  t_func	f2;
  t_func	f1;
  t_func	f3;

  ((t_descr *)params)->id = -1;
  if (add_commands(params, &com_finish) == 0)
    {
      f1.fct = &fct_stop;
      f1.params = params;
      f2.fct = &fct_read;
      f2.params = params;
      f3.fct = &fct_write;
      f3.params = params;
      FD_ZERO(&((t_descr *)params)->readfd);
      FD_ZERO(&((t_descr *)params)->writefd);
      FD_SET(((t_descr *)params)->cli->socket, &((t_descr *)params)->readfd);
      write_iov(((t_descr *)params), "ID\nMAP\n");
      select_loop(((t_descr *)params), &f1, &f2, &f3);
    }
  if (((t_descr *)params)->run && (((t_descr *)params)->id == -1 ||
    ((t_descr *)params)->map->cells->size == 0))
    cmutex_unlock(&((t_descr *)params)->lock);
  ((t_descr *)params)->run = 0;
  return (NULL);
}
