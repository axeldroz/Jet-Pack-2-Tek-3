/*
** thread.c for jetpack2Tek3 in /home/gigoma_l/rendu/jetpack2Tek3
**
** Made by Loïc GIGOMAS
** Login   <gigoma_l@epitech.net>
**
** Started on  Thu Jul  7 15:52:52 2016 Loïc GIGOMAS
** Last update Fri Jul  8 11:40:26 2016 Loïc GIGOMAS
*/

#include "thread.h"

void		thr_del(void *ptr)
{
  t_thread	*t;

  if (!ptr)
    return ;
  t = ptr;
#ifdef __linux__
  /* pthread_cancel(t->thread); */
  pthread_join(t->thread, t->ret);
#elif _WIN32
  WaitForSingleObject(t->thread.handle, INFINITE);
  GetExitCodeThread(t->thread.handle, t->ret);
  CloseHandle(t->thread.handle);
#endif
}

t_thread	*t_thread_new(t_thread_init var)
{
  t_thread	*t;

  if (!var.routine)
    return (NULL);
  if ((t = (t_thread *)new(t_object, sizeof(t_thread), &thr_del)) == NULL)
    return (NULL);
  t->ret = var.ret;
#ifdef __linux__
  if (pthread_create(&t->thread, NULL, var.routine, var.params) != 0)
    return (NULL);
#elif _WIN32
  t->thread.handle = CreateThread(NULL, 0,
				   (LPTHREAD_START_ROUTINE)var.routine,
				   var.params, 0, &(t->thread.thread_id));
  if (t->thread.handle == NULL)
    return (NULL);
#endif
  return (t);
}
