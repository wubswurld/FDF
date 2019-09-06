#include "ft_fdf.h"
#include <stdio.h>
#include <sys/stat.h>
#include "libft/libft.h"

int check_valid(char *str)
{
    int x = 0;
    while (str[x])
    {
        if (!ft_isdigit(str[x]) && str[x] != '-' && str[x] != ' ' && str[x] != '\n')
            return (1);
        x++;
    }
    return (0);
}

void store_file(t_fdf *sp, char *hld)
{
    int y = 0;
    int count = 0;
    while (hld[y])
    {
        // if (hld[y] != ' ')
        sp->hold[count++] = hld[y];
        y++;
    }
    sp->hold[count] = '\0';
}

void read_file(char *str, t_fdf *sp)
{
    int fd;
    int x;
    struct stat *buf;
    char *hld;

    x = 0;
    buf = malloc(sizeof(struct stat));
    lstat(str, buf);
    sp->hold = (char *)malloc(sizeof(char) * (buf->st_size));
    hld = (char *)malloc(sizeof(char) * (buf->st_size));
    fd = open(str, O_RDONLY);
    while ((x = read(fd, hld, buf->st_size)) > 0)
    {
        // store_file(sp, hld);
        if (!(check_valid(hld)))
            sp->hold = ft_strdup(hld);
        else
        {
            ft_putstr("invalid file contents");
            exit(1);
        }
    }
    // free(buf);
    // free(hld);
}

void check_arg(char *str)
{
    int x;

    x = 0;
    if (ft_strlen(str) < 5)
    {
        ft_putstr("invalid file name");
        exit(1);
    }
    while (str[x])
        x++;
    if (ft_strcmp(str + x - 4, ".fdf") != 0)
    {
        ft_putstr("invalid file name");
        exit(1);
    }
}

int count_2d(char **str)
{
    int x = 0;
    while (str[x])
        x++;
    return (x);
}

void count_strings(char **ret)
{
    int a = 0;
    while (ret[a])
    {
        if (ret[a + 1])
        {
            if (ft_strlen(ret[a]) - ft_strlen(ret[a + 1]) != 0)
            {
                ft_putstr("done");
                exit(1);
            }
        }
        a++;
    }
}

void parse_fdf(t_fdf *sp)
{
    int x = 0;
    int count;
    char **ret;
    char **tmo;
    ret = ft_strsplit(sp->hold, '\n');
    sp->real = (int **)malloc(sizeof(int *) * (count_2d(ret)));
    sp->max_x = count_2d(ret);
    while (ret[x])
    {
        tmo = ft_strsplit(ret[x], ' ');
        sp->real[x] = (int *)malloc(sizeof(int) * (count_2d(tmo)));
        count = 0;
        while (tmo[count])
        {
            sp->real[x][count] = ft_atoi(tmo[count]);
            count++;
        }
        sp->max_y = count;
        x++;
    }
}

static void draw_line(t_fdf *sp)
{
    int delta[2];
    int sign[2];
    int error[2];

    delta[0] = abs(sp->x1 - sp->x0);
    delta[1] = abs(sp->y1 - sp->y0);
    sign[0] = sp->x0 < sp->x1 ? 1 : -1;
    sign[1] = sp->y0 < sp->y1 ? 1 : -1;
    error[0] = delta[0] - delta[1];
    while (sp->x0 != sp->x1 || sp->y0 != sp->y1)
    {
        mlx_pixel_put(sp->mlx->ptr, sp->mlx->window, sp->x0 + sp->c_x, sp->y0 + sp->c_y, 255);
        if ((error[1] = error[0] * 2) > -delta[1])
        {
            error[0] -= delta[1];
            sp->x0 += sign[0];
        }
        if (error[1] < delta[0])
        {
            error[0] += delta[0];
            sp->y0 += sign[1];
        }
    }
}

void rot_x(t_fdf *sp)
{
    int x;
    int y;
    int z;

    x = sp->x0;
    y = sp->y0;
    z = sp->z0;
    sp->y0 = ((y * cos(0.3)) + (z * sin(0.3)));
    sp->z0 = (((-1 * (y * sin(0.3))) + (z * cos(0.3))));
    x = sp->x1;
    y = sp->y1;
    z = sp->z1;
    sp->y1 = ((y * cos(0.3)) + (z * sin(0.3)));
    sp->z1 = (((-1 * (y * sin(0.3))) + (z * cos(0.3))));
}

void rot_y(t_fdf *sp)
{
    int x;
    int y;
    int z;

    x = sp->x0;
    y = sp->y0;
    z = sp->z0;
    sp->z0 = ((x * cos(0.4)) + (z * sin(0.4)));
    sp->z0 = (((-1 * (x * sin(0.4))) + (z * cos(0.4))));
    x = sp->x1;
    y = sp->y1;
    z = sp->z1;
    sp->x1 = ((x * cos(0.4) + (z * sin(0.4))));
    sp->z1 = ((-1 * (x * sin(0.4))) + (z * cos(0.4)));
}

void handle_x(t_fdf *sp, int x, int y)
{
    sp->x0 = x * 10;
    sp->x1 = (x + 1) * 10;
    sp->y0 = y * 10;
    sp->y1 = y * 10;
    sp->z0 = sp->real[x][y];
    sp->z1 = sp->real[x + 1][y];
    draw_line(sp);
}

void handle_y(t_fdf *sp, int x, int y)
{
    sp->x0 = x * 10;
    sp->x1 = x * 10;
    sp->y0 = y * 10;
    sp->y1 = (y + 1) * 10;
    sp->z0 = sp->real[x][y];
    sp->z1 = sp->real[x][y + 1];
    draw_line(sp);
}

int fdf_plot(t_fdf *sp)
{
    int x = 0;
    sp->c_x = 600;
    sp->c_y = 1200 / 3.5;
    while (x < sp->max_x)
    {
        int y = 0;
        while (y < sp->max_y)
        {
            if (x + 1 < (sp->max_x))
                handle_x(sp, x, y);
            if (y + 1 < (sp->max_y))
                handle_y(sp, x, y);
            y++;
        }
        x++;
    }
    return (0);
}

void fdf(t_fdf *sp)
{
    sp->mlx = (t_head *)malloc(sizeof(t_head));
    parse_fdf(sp);
    sp->mlx->ptr = mlx_init();
    sp->mlx->window = mlx_new_window(sp->mlx->ptr, 1200, 1200, "Wubs FDF");
    // mlx_hook(sp->mlx->window, int x_event, int x_mask, int (*funct)(), void *param);
    mlx_loop_hook(sp->mlx->ptr, fdf_plot, sp);
    mlx_loop(sp->mlx->ptr);
}

int main(int ac, char **av)
{
    t_fdf *sp;

    sp = (t_fdf *)malloc(sizeof(t_fdf));
    if (ac == 2)
    {
        check_arg(av[1]);
        read_file(av[1], sp);
        fdf(sp);
    }
    else
        ft_putstr("usage: ./ft_fdf <map>");
    return (0);
}
