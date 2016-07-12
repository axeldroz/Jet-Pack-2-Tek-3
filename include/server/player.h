#ifndef PLAYER_H_
# define PLAYER_H_

# include <sys/uio.h>
# include <sys/time.h>

# include "new.h"
# include "entity.h"
# include "splited.h"
# include "pair.h"
# include "gnl.h"

# define RCV_ID		(1 << 0)
# define RCV_MAP	(1 << 1)
# define RCV_READY	(1 << 2)
# define RCV_ALL	(RCV_ID | RCV_MAP | RCV_READY)

# define GLBUFF		(1024)

# define IS_READY(p)	(p->ready == RCV_ALL)

typedef struct	s_server	t_server;

typedef struct	s_stats
{
  int		id;
  int		coins;
}		t_stats;

typedef struct	s_player_init
{
  int		fd;
  double	gravity;
  double	y;
  double	x;
}		t_player_init;

typedef struct	s_player
{
  t_object	__obj__;
  t_entity	*entity;
  int		fd;
  t_gnl		gnl;
  int		ready;
  int		fire;
  int		coins;
  int		iovcnt;
  struct iovec	io[16];
}		t_player;

t_player	*t_player_new(t_player_init var);

int	write_iov(t_server *s, t_player *p, char *msg);
int	iov_send(t_server *s, t_player *p);

int	send_states(t_server *s);
int	calc_states(t_server *s, struct timeval *lasttime);
int	send_to_all(t_server *s, char *str);
int	update_pos(t_server *s, t_player *p, double time);
int	check_colliders(t_server *s, t_player *p, char *b, size_t *o);

int	add_client(t_server *s);
int	remove_client(t_server *s, t_player *p);

int	com_id(t_splited *str, t_player *c, t_server *s);
int	com_map(t_splited *str, t_player *c, t_server *s);
int	com_ready(t_splited *str, t_player *c, t_server *s);
int	com_fire(t_splited *str, t_player *c, t_server *s);

typedef int	(*t_cell_f)(t_pair *, void **, t_pair *, size_t);

int	cell_empty(t_pair *p, void **cell, t_pair *b, size_t pos);
int	cell_elec(t_pair *p, void **cell, t_pair *b, size_t pos);
int	cell_coin(t_pair *p, void **cell, t_pair *b, size_t pos);

size_t	get_cell(t_server *s, t_player *p, int corner);

int	end_game(t_server *s);

# include "server.h"

#endif /* !PLAYER_H_ */
