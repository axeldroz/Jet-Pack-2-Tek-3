/*
** cmd.h for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Wed Jul 13 16:49:32 2016 Loïc GIGOMAS
** Last update Wed Jul 13 16:49:33 2016 Loïc GIGOMAS
*/

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
