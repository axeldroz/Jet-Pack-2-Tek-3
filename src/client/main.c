#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "tcpnetc.h"
#include "thread.h"

int main(int ac, char **av)
{
  t_tcpnetc	*net;
  char		data[256] = {0};
  long		nb;

  if (ac != 3)
    {
      printf("%s: usage: %s <host> <port>\n", *av, *av);
      return (0);
    }
  if ((net = new(t_tcpnetc, av[1], atoi(av[2]))))
    {
      nb = recv(net->socket, data, 256, 0);
      printf("msg = %s\n", data);
      for (int i = 0; i < nb; ++i)
	data[i] = toupper(data[i]);
      send(net->socket, data, nb, MSG_NOSIGNAL);
    }
  else
    write(1, "Error\n", 6);
  delete(net);
  return (0);
}
