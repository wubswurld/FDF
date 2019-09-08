#include "ft_fdf.h"

// static void draw_line(t_fdf *sp)
// {
//     int delta[2];
//     int sign[2];
//     int error[2];

//     delta[0] = abs(sp->x1 - sp->x0);
//     delta[1] = abs(sp->y1 - sp->y0);
//     sign[0] = sp->x0 < sp->x1 ? 1 : -1;
//     sign[1] = sp->y0 < sp->y1 ? 1 : -1;
//     error[0] = delta[0] - delta[1];
//     while (sp->x0 != sp->x1 || sp->y0 != sp->y1)
//     {
//         mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, sp->x0 + sp->c_x, sp->y0 + sp->c_y, 255);
//         if ((error[1] = error[0] * 2) > -delta[1])
//         {
//             error[0] -= delta[1];
//             sp->x0 += sign[0];
//         }
//         if (error[1] < delta[0])
//         {
//             error[0] += delta[0];
//             sp->y0 += sign[1];
//         }
//     }
// }
