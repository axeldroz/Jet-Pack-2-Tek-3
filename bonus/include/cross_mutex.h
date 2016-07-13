/*
** cross_mutex.h for cross_mutex in /home/drozdz_b/Documents/cross_thread
**
** Made by drozdz_b
** Login   <drozdz_b@epitech.net>
**
** Started on  Thu Jul  7 14:40:46 2016 drozdz_b
** Last update Wed Jul 13 11:28:04 2016 Loïc GIGOMAS
*/

#ifndef CROSS_MUTEX_H_
#define CROSS_MUTEX_H_

#ifdef __linux__
#include <pthread.h>
#elif _WIN32
#include <windows.h>
#endif

#ifdef __linux__
typedef pthread_mutex_t t_cmutex;
#elif _WIN32
typedef HANDLE t_cmutex;
#endif

int	cmutex_init(t_cmutex *ptr_mutex);
int	cmutex_lock(t_cmutex *ptr_mutex);
int	cmutex_unlock(t_cmutex *ptr_mutex);
int	cmutex_wait(t_cmutex *ptr_mutex);

#endif
