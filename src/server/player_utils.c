#include "server/player.h"
#include "foreach.h"

int	send_to_all(t_server *s, char *str)
{
  FOREACH(t_pair *, p, s->clients)
    if (write_iov(s, p->second, str) == -1)
      return (-1);
  return (0);
}

int	send_states(t_server *s)
{
  (void) s;

  return (0);
}

int	calc_states(t_server *s, clock_t lasttime)
{
  (void) s;
  (void) lasttime;
  return (0);
}
