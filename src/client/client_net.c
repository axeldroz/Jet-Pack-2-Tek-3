#include "client/client_net.h"
#include "tcpnetc.h"
#include "thread.h"

#include "client/select_loop.h"

void        *fct_stop(void *params)
{
  return ((void *)(((t_descr *)params)->run == 0 ? 1L : 0L));
}

void        *fct_write(void *params)
{
  t_descr     *descr;

  descr = (t_descr *)(params);
  return ((void *)(long)iov_send(descr));
}

void        *fct_read(void *params)
{
  int		r;
  char		*str;
  t_splited	*cmp;
  int		first;
  t_descr   *s;

  str = NULL;
  first = 1;
  s = params;
  while ((r = get_next_line(&s->gnl, (first ? s->cli->socket : -1), &str)) < 2)
    {
      if (r == 0 || r == 1)
	{
	  if ((cmp = new(t_splited, str)) == NULL)
	    return((void *)-1);
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

t_cth_ret net_routine(t_cth_params params)
{
    t_descr     *descr;
    t_func      f2;
    t_func      f1;
    t_func      f3;

    f1.fct = &fct_stop;
    f1.params = params;
    f2.fct = &fct_read;
    f2.params = params;
    f3.fct = &fct_write;
    f3.params = params;
    descr = (t_descr *)(params);
    write_iov(descr, "ID\nMAP\n");
    select_loop(descr->cli->socket, &f1, &f2, &f3);
    return (NULL);
}
