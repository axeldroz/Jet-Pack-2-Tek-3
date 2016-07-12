#ifndef CLIENT_NET_H_
#define CLIENT_NET_H_

#include "graphic.h"

typedef struct s_descr
{
    t_game_map  *map;
    t_graph_item *player;
    t_vector     *other_players;  
    int          id;
}               t_descr;

#endif