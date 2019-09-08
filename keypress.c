#include "ft_fdf.h"

int key_press(int keycode, t_fdf *sp)
{
    if (keycode == 126)
        sp->line->a += 0.2;
    if (keycode == 125)
        sp->line->a -= 0.2;
    if (keycode == 123)
        sp->line->b += 0.1;
    if (keycode == 124)
        sp->line->b -= 0.1;
    if (keycode == 0)
        sp->line->c_x -= 15;
    if (keycode == 13)
        sp->line->c_y += 15;
    if (keycode == 2)
        sp->line->c_x += 15;
    if (keycode == 1)
        sp->line->c_y -= 15;
    if (keycode == 53)
        exit(0);
    if (keycode == 24)
        sp->line->scale += 5;
    if (keycode == 27)
        sp->line->scale -= 5;
    return (0);
}

int close_prog(void *param)
{
    (void)param;
    exit(0);
}

void handleKeyPress(t_fdf *sp)
{
    mlx_hook(sp->mlx->window, 2, 0, key_press, sp);
    mlx_hook(sp->mlx->window, 17, 0, close_prog, sp);
}