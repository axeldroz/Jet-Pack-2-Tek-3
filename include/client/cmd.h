#ifndef CMD_H_
# define CMD_H_

# include "splited.h"
# include "client/client_net.h"

int	com_id(t_splited *str, t_descr *descr);
int	com_map(t_splited *str, t_descr *descr);
int	com_coin(t_splited *str, t_descr *descr);
int	com_start(t_splited *str, t_descr *descr);
int	com_player(t_splited *str, t_descr *descr);

#endif /* !CMD_H_ */
