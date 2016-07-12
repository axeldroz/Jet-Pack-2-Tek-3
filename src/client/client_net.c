#include "client/client_net.h"
#include "tcpnetc.h"
#include "thread.h"

#include "select_loop.h"

void        *fct_stop(void *)
{
    return ((void *)1)
}

void        *fct_write(void *)
{
    return ((void *)1)
}

void        *fct_read(void *)
{
    return ((void *)1)
}

t_cth_ret net_routine(t_cth_params params)
{
    t_descr     descr;
    t_func      f2;
    t_fun       f1;
    t_fun       f3;

    f1.fct = &fct_stop;
    f1.params = NULL;
    f2.fct = &fct_read;
    f2.params = params;
    f3.fct = &fct_write;
    f3.params = params;
    descr = (t_descr)(params);
    select_loop(params, f1, f2, f3);
    return (NULL);
}
