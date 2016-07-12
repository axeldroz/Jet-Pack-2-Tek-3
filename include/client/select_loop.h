/*
** select_loop.h for select_loop in /home/drozdz_b/rendu/jetpack2Tek3/include/client
** 
** Made by drozdz_b
** Login   <drozdz_b@epitech.net>
** 
** Started on  Tue Jul 12 21:30:31 2016 drozdz_b
** Last update Tue Jul 12 21:30:34 2016 drozdz_b
*/

#ifndef SELECT_LOOP_H_
#define SELECT_LOOP_H_

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef __linux__
typedef int SOCKET;
#endif

typedef struct s_func
{
    void (*fct)(void *param);
    void *param;
}               t_func;

void select_loop(SOCKET fd, t_func *fctstop, t_func *fctr, t_func *fctw);

#endif
