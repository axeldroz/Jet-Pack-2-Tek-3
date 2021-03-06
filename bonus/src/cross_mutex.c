/*
** cross_mutex.c for cross_mutex in /home/drozdz_b/Documents/cross_thread
**
** Made by drozdz_b
** Login   <drozdz_b@epitech.net>
**
** Started on  Thu Jul  7 14:41:02 2016 drozdz_b
** Last update Wed Jul 13 12:12:02 2016 Loïc GIGOMAS
*/

#include "cross_mutex.h"

int	cmutex_init(t_cmutex *ptr_mutex)
{
#ifdef __linux__
  *ptr_mutex = (t_cmutex)PTHREAD_MUTEX_INITIALIZER;
  return (0);
#elif _WIN32
  *ptr_mutex = CreateMutex(NULL, FALSE, NULL);
  if (*ptr_mutex == NULL)
    return (1);
  return (0);
#endif
}

int	cmutex_lock(t_cmutex *ptr_mutex)
{
#ifdef __linux__
  return (pthread_mutex_lock(ptr_mutex));
#elif _WIN32
  WaitForSingleObject(ptr_mutex);
  return (0);
#endif
}

int	cmutex_unlock(t_cmutex *ptr_mutex)
{
#ifdef __linux__
  return (pthread_mutex_unlock(ptr_mutex));
#elif _WIN32
  if (Release(*ptr_mutex))
    return (0);
  return (1);
#endif
}

int	cmutex_wait(t_cmutex *ptr_mutex)
{
  if (cmutex_lock(ptr_mutex) != 0)
    return (1);
  return (cmutex_unlock(ptr_mutex));
}
