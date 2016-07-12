/*
** tcpnets.h for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Thu Jul  7 18:13:53 2016 Loïc GIGOMAS
** Last update Fri Jul  8 11:04:04 2016 Loïc GIGOMAS
*/

#ifndef TCPNETS_H_
# define TCPNETS_H_

# ifdef __linux__
#  include <arpa/inet.h>
#  define INVALID_SOCKET -1
#  define SOCKET_ERROR -1
#  define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
# elif _WIN32
#  include <winsock2.h>
# endif

# include "new.h"

typedef struct	s_tcpnets_init
{
  int		port;
  int		max_queue;
}		t_tcpnets_init;

typedef struct	s_tcpnets
{
  t_object	__obj__;
  SOCKET	socket;
}		t_tcpnets;

t_tcpnets		*t_tcpnets_new(t_tcpnets_init var);

#endif /* !TCPNETS_H_ */
