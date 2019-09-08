#include "ft_fdf.h"

int count_2d(char **str)
{
    int x = 0;
    while (str[x])
        x++;
    return (x);
}

int fdf_plot(t_fdf *sp)
{
    int y = 0;
    mlx_clear_window(sp->mlx->ptr, sp->mlx->window);
    while (y < sp->line->max_y)
    {
        int x = 0;
        while (x < sp->line->max_x)
        {
            if (y + 1 < (sp->line->max_y))
                handle_y(sp, x, y);
            if (x + 1 < (sp->line->max_x))
                handle_x(sp, x, y);
            ++x;
        }
        ++y;
    }
    return (0);
}

int main(int ac, char **av)
{
    t_fdf *sp;

    sp = (t_fdf *)malloc(sizeof(t_fdf));
    sp->mlx = (t_head *)malloc(sizeof(t_head));
    sp->line = (t_lines *)malloc(sizeof(t_lines));
    sp->line->head = (t_algo *)malloc(sizeof(t_algo));
    if (ac == 2)
    {
        sp->line->a = 0.3;
        sp->line->b = 0.2;
        sp->line->c_x = 550;
        sp->line->c_y = 1200 / 3.5;
        check_arg(av[1]);
        read_file(av[1], sp);
        parse_fdf(sp);
        sp->mlx->ptr = mlx_init();
        sp->mlx->window = mlx_new_window(sp->mlx->ptr, 1200, 1200, "Wubs FDF");
        handleKeyPress(sp);
        mlx_loop_hook(sp->mlx->ptr, fdf_plot, sp);
        mlx_loop(sp->mlx->ptr);
    }
    else
        ft_putstr("usage: ./ft_fdf <map>");
    return (0);
}
