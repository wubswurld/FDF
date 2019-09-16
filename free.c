#include "ft_fdf.h"

void free_fdf(t_fdf *sp)
{
    int a = 0;
    while (sp->tmo[a])
    {
        free(sp->tmo[a]);
        a++;
    }
}

void free_ret(t_fdf *sp)
{
    int z = 0;
    while (sp->ret[z])
    {
        free(sp->ret[z]);
        z++;
    }
}