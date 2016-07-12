#ifndef CLIENT_NET_H_
#define CLIENT_NET_H_

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "client/graphic.h"
#include "gnl.h"
#include "map.h"
#include "game_map.h"
#include "tcpnetc.h"
#include "thread.h"

typedef struct s_descr
{
    t_game_map  *map;
    t_map     *players;
    int          id;
    t_tcpnetc    *cli;
    t_gnl        gnl;
    fd_set readfd;
    fd_set writefd;
    int run;
}               t_descr;

t_cth_ret net_routine(t_cth_params var);

#endif
